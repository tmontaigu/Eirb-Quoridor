#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "./headers/structQuoridor.h"



const struct board *bglobal = &Board;


void delay(unsigned int);

// Les fonctions move_pawn et place_wall devreaient faire ecrire dans le fichier coups
// Le changement de joueur est pas fait (c'est mal pour la fonction get_current_player)



FILE *Coups;


int ecrit (char colonne, char ligne, char direction, int currentPlayer)
{
    Coups=fopen("fichier_coups.txt","a");
    
    fprintf(Coups,"%c%c",colonne, ligne);
    int Direction;
    Direction=direction -'0';
    switch (Direction)
    {
        case 0:
            fprintf(Coups,"h ");
			break;
        case 1:
            fprintf(Coups,"v ");
			break;
        default:
	  if (currentPlayer==1)
	    {
	      fprintf(Coups,"  ");
	    }
            break;
    }

    if(currentPlayer==0)
		fprintf(Coups,"\n");

	fclose(Coups);
	return 0;
}


/*********************************************************************************/
int gagnant(const struct board *bglobal)
{
    if ( Board.lignePionNoir == 0)
    {
        printf("Pion Noir Gagne\n");
        return 0;
    }
    else if ( Board.lignePionBlanc == 8)
    { 
        printf("Pion Blanc Gagne\n");
        return 0;
    }

    else
        return 1;

}


/********************************************************************************/
void init_board (const struct board *bglobal)
{

	//d'abords on enlève tout sur le plateau/board

	for ( int i=0; i<9; i++)
	{
		for (int j=0; j<9; j++)
		{
			Board.grille[i][j].pion = none;
			Board.grille[i][j].murDroite = 0;
			Board.grille[i][j].murBas = 0;
			Board.grille[i][j].origineMur = 0;
		}
	}

	//ensuite on rajoute les 2 pions a leur départ respectif
	Board.grille[0][4].pion = white;
	Board.grille[8][4].pion = black;


	Board.lignePionBlanc=0;
	Board.colonnePionBlanc=4;

	Board.lignePionNoir=8;
	Board.colonnePionNoir=4;

	//On init le nb de murs de chaque joueurs

	Board.murBlancRestant=10;
	Board.murNoirRestant=10;

	Board.action=1;
}




/*********************************************************

 * Fonction qui verifie si le déplacement du pion est
 * autorise (qu'il ne se déplace pas de plus de 1 case
 * ou qu'il n'aille pas en dehors du board

 * TODO add the pssibility to jump over an enemy pawn
 * (see the game rules)

**********************************************************/
int is_move_valid(const struct board *bglobal, int colonne, int ligne)
{
	int isMoveValid = 0;
    //Opponent is already on the destination
	if (current_player_is(black) && pawn_at(ligne,colonne) == white)
        return 0;
	else if (current_player_is(white) && pawn_at(ligne,colonne) == black)
        return 0;
	
	int direction  =  invalid;
	if (current_player_is(black))
    {
        direction = determine_direction(bglobal->colonnePionNoir, bglobal->lignePionNoir, colonne, ligne);

        if (direction == invalid)
            isMoveValid = invalid;
        else
            isMoveValid = is_reachable(*bglobal, bglobal->colonnePionNoir, bglobal->lignePionNoir, direction);
	}

	if (current_player_is(white))
	{
        direction = determine_direction(bglobal->colonnePionBlanc, bglobal->lignePionBlanc, colonne, ligne);
        
        if (direction == invalid)
            isMoveValid = invalid;
        else
            isMoveValid = is_reachable(*bglobal, bglobal->colonnePionBlanc, bglobal->lignePionBlanc, direction);
	}
	
	//test si le pion va pas se deplacer hors de du board
	if ( colonne < 0 || colonne > 8)
	{
		isMoveValid=0;
	}

	if (ligne < 0 || ligne > 8 )
	{
		isMoveValid=0;
	}
	return isMoveValid;
}







/***********************************************************

 * Simple fonction qui affiche la le jeu dans un terminal

 **********************************************************/
void display_board(const struct board *bglobal)
{
	int i,j;

	printf("   ");
	for(i=0; i<= LIGNES-1; i++)
	{
		printf(" ");
		printf("%c ",'a'+i);
	}
	printf("\n");


	for(i=0; i<LIGNES; i++)
	{
		printf(" %d ",i+1);

		for(j=0; j<COLONNES; j++)
		{
			//affichage des pions
			printf(" ");

		if (Board.grille[i][j].pion==-1) 
			printf(".");
		else if (Board.grille[i][j].pion==0) 
			printf("O");
		else if (Board.grille[i][j].pion==1) 
			printf("X");
			//affichage des murs verticaux
		if (Board.grille[i][j].murDroite==0) 
			printf(" ");
		else if (Board.grille[i][j].murDroite==1) 
			printf("|");

		}

		printf("\n");
		
		//affichage des murs horizontaux
		for (j = 0; j < COLONNES; j++)
		{
			if (Board.grille[i][j].murBas==1) 
				printf(" _ ");
			else if (Board.grille[i][j].murBas==0) 
				printf("   "); //3 espaces pour que ça soit bien aligné
		}
			printf("\n");
	}
}

int distance_between(int a, int b) {
	return abs( a - b );
}

int current_player_is(int playerColor) {
	return current_player() == playerColor;
}

int current_player() {
    return bglobal->joueur;
}

int pawn_at(int line, int column) {
	return bglobal->grille[line][column].pion;
}

void get_position_of(const struct board *b, int player, int *column, int *row) {
    if (player == black) {
        *column = b->colonnePionNoir;
        *row = b->lignePionNoir;
    }
    else if (player == white) {
        *column = b->colonnePionBlanc;
        *row = b->lignePionBlanc;
    }
}

int determine_direction(int srcColumn, int srcLine, int dstColumn, int dstLine) {
    if ( srcColumn == dstColumn) { //Direction is either up or down 
        if ( dstLine - srcLine == 1 )
            return down;
        else if (dstLine - srcLine == -1 )
            return up;
        else 
            return invalid;
    }
    else if (srcLine == dstLine) { // Direction is either left or right 
        if (dstColumn - srcColumn  == 1)
            return right;
        else if (dstColumn - srcColumn == -1)
            return left;
        else
            return invalid;
    }
    else 
        return invalid;
}
