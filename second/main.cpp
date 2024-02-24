#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <iostream>
#include <unistd.h>
#include "socket_client.hpp"

using namespace std;

int positiveIntegerLen(int number);

bool checkIntegerMultiplicity(int divisible, int divisor);

int main() {   
    const string myIp = "127.0.0.1";
    const int myPort = 7654;
    SocketClient client(myIp, myPort);
    ClientError clientStatus = client.start();
    if (clientStatus == ClientError::noError) {
        cout << "Connection established!" << endl;
    }
    int sum;
    for(;;) {
        if (clientStatus != ClientError::noError) {
            cerr << "Error connecting!" << endl;
            cerr << "Trying to reconnect..." << endl;
            while (clientStatus != ClientError::noError) {
                clientStatus = client.start();
                sleep(1);
            }
            cout << "Connection established!" << endl;
        }
        clientStatus = client.receiveSum(sum);
        if(clientStatus == ClientError::noError) {
            if (positiveIntegerLen(sum) > 2 && checkIntegerMultiplicity(sum, 32)) {
                cout << "Received sum = " << sum << endl;
            } else {
                cout << "Error: data is not correct!" << endl;
            }
        }
    }
    return 0;
}

int positiveIntegerLen(int number) {
    int countDigits = 0;
    while (number > 0) {
        number /= 10;
        countDigits += 1;
    }
    return countDigits;
}

bool checkIntegerMultiplicity(int divisible, int divisor) {
    if (divisor == 0) {
        return false;
    }
    return (divisible % divisor == 0);
}
