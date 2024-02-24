second: main.o socket_client.o
	g++ -o second main.o socket_client.o
clean:
	rm -f second *.o
main.o: main.cpp
	g++ --std=c++11 -Wall -Wextra -Wpedantic -c -o main.o main.cpp
socket_client.o: socket_client.cpp
	g++ --std=c++11 -Wall -Wextra -Wpedantic -c -o socket_client.o socket_client.cpp
