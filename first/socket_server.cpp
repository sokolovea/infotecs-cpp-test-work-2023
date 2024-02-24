#include <unistd.h>
#include <errno.h>
#include "socket_server.hpp"

SocketServer::SocketServer(std::string const &ip, int port) {
    this->setPort(port);
    this->setIp(ip.c_str());
    this->address.sin_family = AF_INET;
    this->setFileDescriptor(-1);
}

SocketServer::~SocketServer() {
    shutdown(this->getFileDescriptor(), SHUT_WR);
    close(this->getFileDescriptor());
    close(this->getSocketDescriptor());
}

ServerError SocketServer::startServer() {
    int socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    this->setSocketDescriptor(socketDescriptor );
    int option = 1;
    // Also disable port "catching"
    setsockopt(socketDescriptor, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
    int myBind = bind(socketDescriptor , (struct sockaddr*)&address, sizeof(address));
    if (myBind == -1) {
        return ServerError::bindError;
    }
    int myListen = listen(socketDescriptor, 16);
    if (myListen == -1) {
        return ServerError::listenError;
    }
    socklen_t clientInfo_size = sizeof(address);
    int myAccept = accept(socketDescriptor, (struct sockaddr*)&address, &clientInfo_size);
    this->setFileDescriptor(myAccept);
    return (myAccept == -1) ? ServerError::acceptError : ServerError::noError;
}

void SocketServer::setIp(const char* newIp) {
    inet_aton(newIp, &(this->address.sin_addr));
}

void SocketServer::setPort(const int newPort) {
    this->address.sin_port = htons(newPort);
}

int SocketServer::sendSum(int sum) const {
    return send(this->getFileDescriptor(), &sum, 4, MSG_NOSIGNAL);
}

ServerError SocketServer::restartServer() {
    close(this->getFileDescriptor());
    socklen_t clientInfo_size = sizeof(address);
    this->unblock();
    int myAccept = accept(this->getSocketDescriptor(), (struct sockaddr*)&address, &clientInfo_size);
    this->block();
    this->setFileDescriptor(myAccept);
    return (myAccept == -1) ? ServerError::acceptError : ServerError::noError;
}

void SocketServer::block() {
    // set the socket to blocking mode
    int flagues = fcntl(this->socketDescriptor, F_GETFL);
    fcntl(this->socketDescriptor, F_SETFL, flagues & (!O_NONBLOCK));
}

void SocketServer::unblock() {
    // set the socket to non-blocking mode
    int flagues = fcntl(this->socketDescriptor, F_GETFL);
    fcntl(this->socketDescriptor, F_SETFL, flagues | O_NONBLOCK);
}

