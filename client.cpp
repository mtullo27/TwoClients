#include <iostream>
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <time.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <vector>

using namespace std;

#define PORT	 1027


int main() { 
	int sockfd, count;
	clock_t start, end;
	socklen_t len;
	char buffer[1024];
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
	
	//Set timeout for 1 second
	struct timeval tv;
	tv.tv_sec = 1;
	tv.tv_usec = 0;
	if(setsockopt (sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv, sizeof(tv)) < 0) {
   		 perror("Error");
	}
	//Keep track of number of pings
        count = 0;
	//send 10 pings in a loop

	len = sizeof(servaddr);
	while(count<10){
	for(int i = 0; i<10; i++){
		//Get current time
	        start = time(0);

		//Send message to server
		sendto(sockfd, (const char *) buffer, strlen(buffer), MSG_CONFIRM, (const struct sockaddr *) &servaddr, len);
		//Recieve message form server
		int n;
	        n = recvfrom(sockfd, (char *)buffer, sizeof(buffer), MSG_WAITALL, (struct sockaddr *) &servaddr, &len);
		buffer[n] = '\0';
		//See how long has passed
		double total = (double)difftime(time(0), start);
		//Check if ping sent for longer than a second
		if(total >= 1.0){
		  cout << "Connection Time out on Ping Number " << count << endl;
		}
		else{
		  cout << "Ping Number " << count << "Round Trip Time " << end << " Seconds" << endl;
		}
		count++;
	}
	
	}
	return 0; 
} 
