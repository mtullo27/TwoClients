all: server client

p1: server.cpp 
	g++ -g server.cpp -o server

p2: client
	g++ -g client.cpp - client
clean:
	rm -rf server client
