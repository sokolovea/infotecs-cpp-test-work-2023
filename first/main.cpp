#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include "string_handler.hpp"
#include "socket_server.hpp"
#include "string_buffer.hpp"

using namespace std;

void printServerError(const ServerError serverStatus);

int inputAndAnalyze(StringBuffer &buffer);

int printAndSend(StringBuffer &buffer, SocketServer &server);

int main() {
    string myIp = "127.0.0.1";
    int myPort = 7654;
    SocketServer server(myIp, myPort);
    StringBuffer buffer;
    std::thread firstTread(inputAndAnalyze, std::ref(buffer));
    std::thread secondTread(printAndSend, std::ref(buffer), std::ref(server));
    firstTread.join();
    secondTread.join();
    return 0;
}

int inputAndAnalyze(StringBuffer &buffer) {
    string preparingString;
    for (;;) {
        getline(cin, preparingString);
        if (cin.eof()) {
            cout << "The EOF was found, shutdown server now." << endl;
            exit(0);
        }
        if (not StringHandler::isStringCorrect(preparingString)) {
            cout << "String check fail!" << endl;
        } else {
            StringHandler::sortStringInDesc(preparingString);
            StringHandler::replaceEvenNumbers(preparingString);
            buffer.PushString(preparingString);
        }
    }
    return 0;
}

int printAndSend(StringBuffer &buffer, SocketServer &server) {
    ServerError serverStatus = server.startServer();
    if (serverStatus == ServerError::noError) {
        cout << "Connection with the client is established!" << endl;
    } else {
        if (serverStatus != ServerError::acceptError) {
            printServerError(serverStatus);
        }
    }
    string preparingString;
    for (;;) {
        preparingString = buffer.PopString();
        cout << preparingString << endl;
        int sum = StringHandler::sumDigits(preparingString);
        int sendingStatus = server.sendSum(sum);
        if (sendingStatus == -1) {
            cerr << "Connection with the client is broken!" << endl;
            cerr << "Waiting for the connection." << endl;
            ServerError serverStatus = server.restartServer();
            if (serverStatus == ServerError::noError) {
                cout << "Connection with the client is established!" << endl;
            } else {
                if (serverStatus != ServerError::acceptError) {
                    printServerError(serverStatus);
                }
            }
        }
    }
    return 0;
}

void printServerError(ServerError serverStatus) {
    string errorMessage = "Error starting server:\n";
    switch (serverStatus) {
        case ServerError::bindError: errorMessage += "bind() error"; break;
        case ServerError::listenError: errorMessage += "listen() error"; break;
        case ServerError::acceptError: errorMessage += "accept() error"; break;
        default: break;
    }
    cerr << errorMessage << endl;
}
