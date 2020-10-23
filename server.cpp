#include <iostream>
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <time.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <bits/stdc++.h>

#define PORT	 1080

using namespace std;

int main() { 
	int sockfd, n;
	socklen_t len;
	clock_t clientX, clientY;
	double total = 0;
	char buffer[1024];
	char * ack;
	struct sockaddr_in servaddr, cliaddr; 
	
	// Create a UDP socket
	// Notice the use of SOCK_DGRAM for UDP packets
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	
	memset(&servaddr, 0, sizeof(servaddr)); 
	memset(&cliaddr, 0, sizeof(cliaddr)); 
	
	// Fill server information 
	servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_addr.s_addr = INADDR_ANY; // localhost
	servaddr.sin_port = htons(PORT); // port number
	
	// Bind the socket with the server address 
	bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr));
	
	// random generator
	srand(time(0));
	
	string message;
	
        while (1) {
		//Receive the client packet along with the address it is coming from
		n = recvfrom(sockfd, (char *)buffer, sizeof(buffer), 
			MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
		buffer[n] = '\0';
		//Check which arrived first
		if(buffer[7] == 'X')
			clientX = time(0);
		else
			clientY = time(0);
		total = (double)difftime(clientX, clientY);
		if(total < 0)
			message = "X was recieved before Y";
		else
			message = "Y was recieved before X";
		//the server responds
		for(int i = 0; i<message.length(); i++)
			ack[i] = message[i];
		ack[message.length()] = '\0';
		sendto(sockfd, (const char *)ack, strlen(buffer), 
			MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len);
		break;
	}

	return 0; 
} 
