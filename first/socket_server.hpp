#pragma once
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

enum class ServerError {
    noError, bindError, listenError, acceptError
};

class SocketServer {
    public:
        SocketServer(std::string const &ip, int port);
        ServerError startServer();
        int sendSum(int sum) const;
        ServerError restartServer();
        ~SocketServer();
    private:
        struct sockaddr_in address;
        int socketDescriptor;
        int fileDescriptor;
        int getFileDescriptor() const {return this->fileDescriptor;}
        void setFileDescriptor(int fileDescriptor) {this->fileDescriptor = fileDescriptor;}
        int getSocketDescriptor() const {return this->socketDescriptor;}
        void setSocketDescriptor(int socketDescriptor) {this->socketDescriptor = socketDescriptor;}
        void setIp(const char* newIp);
        void setPort(int newPort);
        void block();
        void unblock();
        
};
