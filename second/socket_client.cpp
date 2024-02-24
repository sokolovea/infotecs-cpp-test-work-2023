#include <unistd.h>
#include <errno.h>
#include "socket_client.hpp"

SocketClient::SocketClient(std::string const &ip, const int port) {
    this->setPort(port);
    this->setIp(ip.c_str());
    this->address.sin_family = AF_INET;
}

SocketClient::~SocketClient() {
    close(this->getSocketDescriptor());
}

ClientError SocketClient::start() {
    int socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    this->setSocketDescriptor(socketDescriptor);
    socklen_t clientInfo_size = sizeof(address);
    int myConnect = connect(this->getSocketDescriptor(), (struct sockaddr*)&address, clientInfo_size);
    return (myConnect == -1) ? ClientError::connectError : ClientError::noError;
}

void SocketClient::setIp(const char* newIp) {
    inet_aton(newIp, &(this->address.sin_addr));
}

void SocketClient::setPort(int newPort) {
    this->address.sin_port = htons(newPort);
}

ClientError SocketClient::receiveSum(int &sum) const {
    int bytesRead = recv(this->getSocketDescriptor(), &sum, 4, MSG_NOSIGNAL);
    return (bytesRead > 0) ? ClientError::noError : ClientError::receiveError;
}

ClientError SocketClient::restart() {
    socklen_t clientInfo_size = sizeof(this->address);
    int myAccept = connect(this->getSocketDescriptor(), (struct sockaddr*)&address, clientInfo_size);
    return (myAccept == -1) ? ClientError::connectError : ClientError::noError;
}

