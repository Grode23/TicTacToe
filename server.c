#include <stdio.h>
#include <unistd.h> //For read and write
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <arpa/inet.h>


#include "header.h"
#include "game.h"


// Function designed for chat between client and server. 
void communication(int sockfd) 
{ 
	char board[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
	int currChoice;
	int returnStatus; 
	char mark = 'X';

	// infinite loop for responing 
	for (;;) { 

		//Display board
		display(board);

		//Send the new int (choice)
		currChoice = nextTurn(board, mark);

		int convertedChoice = htonl(currChoice);
		write(sockfd, &convertedChoice, sizeof(convertedChoice));

		printf("Waiting the opponent to make their move...\n");

		//Read the opponent's choice

		int returnStatus = read(sockfd, &currChoice, sizeof(currChoice));
		if (returnStatus > 0) {
	   		fprintf(stdout, "Received int = %d\n", ntohl(currChoice));
			board[htonl(currChoice)] = 'O';
		}
		else {
		   printf("Damn, an error...\n");
		}

		//Show message if it's a win/lose
		//checkWin();

	
	} 

} 

// Driver function 
int main() 
{ 
	int sockfd, connfd, len; 
	struct sockaddr_in servaddr, cli; 

	// socket create and verification 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) { 
		printf("socket creation failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully created..\n"); 
	
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int)) < 0)
	    herror("setsockopt(SO_REUSEADDR) failed");

	bzero(&servaddr, sizeof(servaddr)); 

	// assign IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	servaddr.sin_port = htons(PORT); 

	// Binding newly created socket to given IP and verification 
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
		printf("socket bind failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully binded..\n"); 

	// Now server is ready to listen and verification 
	if ((listen(sockfd, 5)) != 0) { 
		printf("Listen failed...\n"); 
		exit(0); 
	} 
	else
		printf("Server listening..\n"); 
	len = sizeof(cli); 

	// Accept the data packet from client and verification 
	connfd = accept(sockfd, (SA*)&cli, &len); 
	if (connfd < 0) { 
		printf("server acccept failed...\n"); 
		exit(0); 
	} 
	else
		printf("server acccept the client...\n"); 

	// Function for chatting between client and server 
	communication(connfd); 

	// After chatting close the socket 
	close(sockfd); 

	return 0;
} 
