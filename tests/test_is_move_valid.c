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
    
    bglobal = &myBoard;

    int valid = 666;
    valid = is_reachable(myBoard,4,0); assert(valid == 0);
    valid = is_reachable(myBoard,1,2); assert(valid == 0);
    valid = is_reachable(myBoard,0,1); assert(valid == 0);
    valid = is_reachable(myBoard,2,1); assert(valid == 0);
    
    printf("1/4 OK \n");
   /* 
    myBoard.grille[0][1].murBas = 0; // Can now go up
    reachable = is_reachable(myBoard,1,1,left); assert(reachable == 0);
    reachable = is_reachable(myBoard,1,1,down); assert(reachable == 0);
    reachable = is_reachable(myBoard,1,1,right); assert(reachable == 0);
    reachable = is_reachable(myBoard,1,1,up); assert(reachable == 1);

    printf("2/4 OK \n");

    myBoard.grille[1][1].murDroite = 0; // Can now also go right
    reachable = is_reachable(myBoard,1,1,left); assert(reachable == 0);
    reachable = is_reachable(myBoard,1,1,down); assert(reachable == 0);
    reachable = is_reachable(myBoard,1,1,right); assert(reachable == 1);
    reachable = is_reachable(myBoard,1,1,up); assert(reachable == 1);

    printf("3/4 OK \n");

    myBoard.grille[1][1].murBas = 0; // Can now also go down
    reachable = is_reachable(myBoard,1,1,left); assert(reachable == 0);
    reachable = is_reachable(myBoard,1,1,down); assert(reachable == 1);
    reachable = is_reachable(myBoard,1,1,right); assert(reachable == 1);
    reachable = is_reachable(myBoard,1,1,up); assert(reachable == 1);

    printf("4/4 OK \n");
    
    myBoard.grille[1][0].murDroite = 0; //can now alo go left
    reachable = is_reachable(myBoard,1,1,left); assert(reachable == 1);
    reachable = is_reachable(myBoard,1,1,down); assert(reachable == 1);
    reachable = is_reachable(myBoard,1,1,right); assert(reachable == 1);
    reachable = is_reachable(myBoard,1,1,up); assert(reachable == 1);
*/

    printf("All tests passed !\n");
}
