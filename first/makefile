first: main.o string_handler.o socket_server.o string_buffer.o
	g++ -pthread -o first main.o string_handler.o socket_server.o string_buffer.o
clean:
	rm -f first *.o
main.o: main.cpp
	g++ --std=c++11 -Wall -Wextra -Wpedantic -c -o main.o main.cpp
string_handler.o: string_handler.cpp
	g++ --std=c++11 -Wall -Wextra -Wpedantic -c -o string_handler.o string_handler.cpp
socket_server.o: socket_server.cpp
	g++ --std=c++11 -Wall -Wextra -Wpedantic -c -o socket_server.o socket_server.cpp
string_buffer.o: string_buffer.cpp
	g++ --std=c++11 -Wall -Wextra -Wpedantic -c -o string_buffer.o string_buffer.cpp
