#include "./headers/interface.h"
#include "./headers/registry.h"
#include "./headers/structQuoridor.h"
#include <stdio.h>


void play (const struct board *b) {

    int myColumn = 0;
    int myRow = 0;
    char c;
    int chosenDirection;


    get_position_of(b,b->joueur, &myColumn, &myRow);
    
    printf("You are on : [%d][%c]\n", myRow+1, myColumn + 'a');
    printf("Choose a direction: \n");
    printf("0) Left  \n1) Down \n2) Right\n3) Up\n");
    chosenDirection = getchar() - '0'; 
   
    myColumn += 'a';
    myRow += '1';
    switch(chosenDirection) {
        case left:
            printf("Going to the left\n");
            move_pawn(b,myColumn-1, myRow);
            break;
        case down:
            printf("Going down\n");
            move_pawn(b, myColumn, myRow+1);
            break;
        case right:
            printf("Going to the right\n");
            move_pawn(b, myColumn+1, myRow);
            break;
        case up:
            printf("Going up\n");
            move_pawn(b, myColumn, myRow-1);
            break;
    }
}
