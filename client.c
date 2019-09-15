#include <stdio.h>
#include <unistd.h> //For read and write
#include <netdb.h> 
#include <arpa/inet.h> //For inet_addr
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 

#include "header.h"
#include "communication.h"

void communication(int sockfd) 
{ 
	char board[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
	int currChoice;
	int returnStatus; 
	char mark = 'O';
	int finished = 0;
	int winner = 0;

	while(finished == 0) { 

		if(winner == 1){
			finished = playFirst(board, mark, sockfd, &winner);
		} else {
			finished = playSecond(board, mark, sockfd, &winner);
		}
	}
} 

int main() 
{ 
	int sockfd, connfd; 
	struct sockaddr_in servaddr, cli; 

	// socket create and varification 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) { 
		printf("socket creation failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully created..\n"); 
	bzero(&servaddr, sizeof(servaddr)); 

	// assign IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	servaddr.sin_port = htons(PORT); 

	// connect the client socket to server socket 
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) { 
		printf("connection with the server failed...\n"); 
		exit(0); 
	} 
	else
		printf("connected to the server..\n"); 

	// function for chat 
	communication(sockfd); 

	// close the socket 
	close(sockfd); 
}