#pragma once
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>


enum class ClientError {
    noError, connectError, receiveError
};

class SocketClient {
    public:
        SocketClient(std::string const &ip, const int port);
        ClientError start();
        ClientError receiveSum(int &sum) const;
        ClientError restart();
        ~SocketClient();
    private:
        struct sockaddr_in address;
        int socketDescriptor;
        int getSocketDescriptor() const {return this->socketDescriptor;}
        void setSocketDescriptor(int socketDescriptor) {this->socketDescriptor = socketDescriptor;}
        void setIp(const char* newIp);
        void setPort(int newPort);
        
};
