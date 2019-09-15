#include <stdio.h>
#include <unistd.h> //For read and write
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <arpa/inet.h>

#include "game.h"

int isEmpty(char* board, int size){

	int counter = 0;

	for(int i = 0; i < size; i++){
		if(board[i] == ' '){
			counter++;
		}
	}

	if(counter == size){
		return 1;
	}

	return 0;
}



int playFirst(char* board, char mark, int sockfd, int* winner, int size){

	int finished = 0;

	//Display board
	display(board);
	
	//Send the new int (choice)
	int currChoice = nextTurn(board, mark);
	int convertedChoice = htonl(currChoice);
	write(sockfd, &convertedChoice, sizeof(convertedChoice));
	
	finished = checkWin(board, mark, winner);
	
	if(finished == 1){
		return 1;
	}

	if(isEmpty(board, sizeof(board))){
		return 0;
	}

	//αν εγινε initialize τοτε τελος
	printf("Waiting the opponent to make their move...\n");
	
	//Read the opponent's choice
	int returnStatus = read(sockfd, &currChoice, sizeof(currChoice));
	if (returnStatus > 0) {
   		fprintf(stdout, "Received int = %d\n", ntohl(currChoice));
			
		if(mark == 'X'){
			board[htonl(currChoice)] = 'O';
		} else {
			board[htonl(currChoice)] = 'X';
		}

	}
	else {
	   printf("Damn, an error...\n");
	}
	
	//Show message if it's a win/lose
	finished = checkWin(board, mark, winner);

	if(finished == 1){
		return 1;
	}

	return 0;

	

}

int playSecond(char* board, char mark, int sockfd, int* winner, int size){

	int finished = 0;
	int currChoice;

	//Read the new int
	int returnStatus = read(sockfd, &currChoice, sizeof(currChoice));
	if (returnStatus > 0) {
   		fprintf(stdout, "Received int = %d\n", ntohl(currChoice));
		
		if(mark == 'X'){
			board[htonl(currChoice)] = 'O';
		} else {
			board[htonl(currChoice)] = 'X';
		}
	}
	else {
	   printf("Damn, an error...\n");
	}
	
	//Display the board
	display(board);
	
	finished == checkWin(board, mark, winner);
	
	//Win/lose message
	if (finished == 1){
		return 1;
	}

	printf("os edo\n");

	if(isEmpty(board, sizeof(board))){
		return 0;
	}
printf("os edo\n");

	//Send the new int (choice)
	currChoice = nextTurn(board, mark);
	
	int convertedChoice = htonl(currChoice);
	write(sockfd, &convertedChoice, sizeof(convertedChoice));
	finished == checkWin(board, mark, winner);
	printf("os edo\n");
	//Win/lose message
	if (finished == 1){
		return 1;
	}
printf("os edo\n");
	if(isEmpty(board, sizeof(board))){
		return 0;
	}
	
	printf("Waiting the opponent to make their move...\n");

	return 0;


}