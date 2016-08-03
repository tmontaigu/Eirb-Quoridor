#include <stdio.h>
#include <assert.h>

#include "../src/headers/structQuoridor.h"

int main(int argc, char **argv) {

    //struct Case grille[3][3];
    /*
     * Configuration:
     *   .  .  .
     *      _  
     *   . |x| .
     *      _
     *   .  .  . 
     */ 
    struct board myBoard;
    printf("Begining tests of is_reachable...\n");

    myBoard.grille[0][1].murBas = 1;
    myBoard.grille[1][1].murDroite = 1;
    myBoard.grille[1][1].murBas = 1;
    myBoard.grille[1][0].murDroite = 1;

    myBoard.joueur = black;
    myBoard.colonnePionNoir = 1;
    myBoard.lignePionNoir = 1;
    
    for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			myBoard.grille[i][j].pion = none;
		}
	}
    
    bglobal = &myBoard;

    int valid = 666;
    valid = is_move_valid(bglobal,1,0); assert(valid == 0); //up
    valid = is_move_valid(bglobal,1,2); assert(valid == 0); //down
    valid = is_move_valid(bglobal,0,1); assert(valid == 0); //left
    valid = is_move_valid(bglobal,2,1); assert(valid == 0); //right
    
    printf("1/5 OK \n");
    
    myBoard.grille[0][1].murBas = 0; // Can now go up
    valid = is_move_valid(bglobal,1,0); assert(valid == 1);
    valid = is_move_valid(bglobal,1,2); assert(valid == 0);
    valid = is_move_valid(bglobal,0,1); assert(valid == 0);
    valid = is_move_valid(bglobal,2,1); assert(valid == 0);

    printf("2/5 OK \n");

    myBoard.grille[1][1].murDroite = 0; // Can now also go right
    valid = is_move_valid(bglobal,1,0); assert(valid == 1);
    valid = is_move_valid(bglobal,1,2); assert(valid == 0);
    valid = is_move_valid(bglobal,0,1); assert(valid == 0);
    valid = is_move_valid(bglobal,2,1); assert(valid == 1);

    printf("3/5 OK \n");

    myBoard.grille[1][1].murBas = 0; // Can now also go down
    valid = is_move_valid(bglobal,1,0); assert(valid == 1);
    valid = is_move_valid(bglobal,1,2); assert(valid == 1);
    valid = is_move_valid(bglobal,0,1); assert(valid == 0);
    valid = is_move_valid(bglobal,2,1); assert(valid == 1);

    printf("4/5 OK \n");

    myBoard.grille[1][0].murDroite = 0; //can now alo go left
    valid = is_move_valid(bglobal,1,0); assert(valid == 1);
    valid = is_move_valid(bglobal,1,2); assert(valid == 1);
    valid = is_move_valid(bglobal,0,1); assert(valid == 1);
    valid = is_move_valid(bglobal,2,1); assert(valid == 1);
    
    printf("5/5 OK \n");

    printf("All tests passed !\n");
}
