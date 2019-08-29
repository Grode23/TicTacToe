#include <stdio.h>
#include <stdbool.h>

//Display the board
void display(char choices[9]){

    int currChoice = 0;

    for(int i = 0; i < 5; i++){
        for( int j = 0; j < 5; j++){
        
            if(i%2 == 0){
                if(j%2 == 0){
                    printf("%c", choices[currChoice]);    
                    currChoice++;
                }else{
                    printf("|");
                }
            }else{
                printf("-");
            }
        }

        printf("\n");
    }
}

//Next turn of any player
void nextTurn(char* choices, char mark){
    int num;
    printf("Where do you wish to play? (enter the number)\n");

    //Display the possible spaces for the next move
    char tempArray[9] = {'0', '1', '2', '3', '4', '5', '6', '7', '8'};
    display(tempArray);
    do{
        scanf("%d", &num);
    }while(num <0 || num > 8 || choices[num] != ' ');

    choices[num] = mark;
}

//Ask if they want to play another game of TicTacToe
bool playAgain(){
    
    char decision;

    do{
        printf("Do you want to play again? (y/n): ");
        scanf(" %c", &decision);
        
    }while(decision != 'n' && decision != 'N' && decision == 'y' && decision == 'Y');

    if(decision == 'y' || decision == 'Y'){
        return false;
    }

    return true;
}

//initialize every variable I need after a restart
void initialize(char* choices, char* mark){

	for(int i = 0; i <= sizeof(choices); i++){
		choices[i] = ' ';
	}

	//Since the one mark won, it has to play first in the next game
	//Although it won't since it's changing before every turn
	//So change mark here, so it will change again and the winner plays again
    if(*mark == 'O'){
        *mark = 'X';
    }else{
        *mark = 'O';
    }

}

//Check if the game is over
bool checkWin(char choices[9], char* mark){
   
	bool winning[8];
	winning[0] = choices[0] == choices[4] && choices[0] == choices[8] && choices[0] != ' '; 
	winning[1] = choices[2] == choices[4] && choices[2] == choices[6] && choices[2] != ' ';
	winning[2] = choices[0] == choices[3] && choices[0] == choices[6] && choices[0] != ' ';
	winning[3] = choices[1] == choices[4] && choices[1] == choices[7] && choices[1] != ' ';
	winning[4] = choices[2] == choices[5] && choices[2] == choices[8] && choices[2] != ' ';
	winning[5] = choices[0] == choices[1] && choices[0] == choices[2] && choices[0] != ' ';
	winning[6] = choices[3] == choices[4] && choices[3] == choices[5] && choices[3] != ' ';
	winning[7] = choices[6] == choices[7] && choices[6] == choices[8] && choices[6] != ' ';
	
	for(int i = 0; i < sizeof(winning); i++){
	
	    if(winning[i]){
	        printf("Player %c won!!!\n", choices[0]);
			initialize(choices, mark);
	        return playAgain();
	    }
	}
    return false;
}

int main(){
    
    char currGame[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}; 
    char mark = 'O';
    bool finished = false;
	
    while(finished == false){
        if(mark == 'O'){
            mark = 'X';
        }else{
            mark = 'O';
        }
        nextTurn(currGame, mark);
        display(currGame);
        finished = checkWin(currGame, &mark);
    }    

    return 0;
}