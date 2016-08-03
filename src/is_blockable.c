#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./headers/structQuoridor.h"
int is_reachable (struct board Board, char colonne, char ligne, int direction);
int is_winning ( struct board testBoard, int colonne, int ligne, int player);
void voisins(struct board testBoard, char colonne, char ligne,int player);

/*********************************************************************

 * Directions are either 0 (horizontal) or 1 (vertical).
 * TODO Actually test if the wall can block the pawn
 *********************************************************************/
int is_blockable(const struct board* b, char column, char line, char direction)
{
    struct board testBoard=*b;

	int Ligne = line - '1';
	int Colonne = column - 'a';
	int Direction = direction -'0';

    if (Direction==1){
		testBoard.grille[Ligne][Colonne].murDroite=1;
		testBoard.grille[Ligne][Colonne].origineMur=1;
		testBoard.grille[Ligne+1][Colonne].murDroite=1;
    }
    else if (Direction==0){
		testBoard.grille[Ligne][Colonne].murDroite=1;
		testBoard.grille[Ligne][Colonne].origineMur=1;
		testBoard.grille[Ligne+1][Colonne].murDroite=1;
    }
    
	return 0;
}



int is_winning ( struct board testBoard, int colonne, int ligne, int player)
{
	int winning;

	if (player == black)//noir donc doit arrriver en haut (ligne 0)
	{
		if (ligne==0)
	{
		winning=1;
	}
	else
		winning=0;
	}

	else if(player == white)
	{
	if (ligne==8)
		winning=1;
	else
		winning=0;
	}


    if (winning == 1)
    {
		return 0;
    }
    else
    {
		voisins( testBoard, colonne, ligne, player);
    }
}

/**********************************************************

 * 0=gauche, 2 = Droite , 1 = haut , 4 = bas

 *********************************************************/


void voisins(struct board testBoard, char colonne, char ligne,int player)
{
	int Ligne = ligne -'1';
	int Colonne = colonne - 'a';

	if (is_reachable(testBoard, colonne, ligne,0))
	{
		testBoard.grille[Ligne][Colonne-1].pion=player;
		is_winning(testBoard, colonne+1,ligne, player);
	}

	if (is_reachable(testBoard, colonne, ligne, 1))
	{
		testBoard.grille[ligne-1][colonne].pion=player;
		is_winning(testBoard, colonne, ligne-1, player);
	}
	if ( is_reachable(testBoard, colonne, ligne, 2) )
	{
		testBoard.grille[ligne][colonne+1].pion=player;
		is_winning(testBoard, colonne+1, ligne, player);
	}
	if ( is_reachable(testBoard, colonne, ligne,4) )
	{
		testBoard.grille[ligne+1][colonne].pion=player;
		is_winning(testBoard, colonne, ligne+1, player);
	}
}
