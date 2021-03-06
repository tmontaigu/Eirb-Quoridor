#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "./headers/structQuoridor.h"



/********************************************************

* Retourne le joueur qui doit jouer son coups

 *********************************************************/
unsigned int get_current_player(const struct board * bgblobal)
{
	unsigned int current_player=bglobal->joueur;
	return current_player;
}

/*********************************************************************

 * Fonction qui indique si il ya  un mur en partant de la case donnée
 * et dans la direction donnée


* Direction  towards smaller cols (0), smaller lines (1), larger cols (2) or larger lines (3).
* 0=gauche, 2 = Droite ,3 = haut , 1 = bas

* remplacer int par char
*********************************************************************/
int is_reachable (const struct board Board, char colonne, char ligne, int direction)
{
	int presenceMur=0;		
    
	switch (direction)
	{
		case right:
		  if (Board.grille[ligne][colonne].murDroite==1) presenceMur=1;
		break;

		case down :
		  if (Board.grille[ligne][colonne].murBas==1) presenceMur=1;
		break;

		case left:
		  if (Board.grille[ligne][colonne-1].murDroite==1) presenceMur=1;
		break;

		case up:
			if(Board.grille[ligne-1][colonne].murBas==1) presenceMur=1;
		break;
	}
	return (1 - presenceMur);
}








/************************************************************

 * Fonction qui bouge le pion a la position donnee
 * Si le mouvement est valide
 ***********************************************************/
void move_pawn(const struct board *b, char colonne, char ligne)
{
	int Colonne = colonne-'a';
	int Ligne = ligne - '1'; 
	int validMove;
	int moveDone;



	validMove=is_move_valid(b, Colonne, Ligne);

	if (validMove==1)
	{
		if (current_player_is(white))
		{
			Board.grille[Board.lignePionBlanc][Board.colonnePionBlanc].pion = none;
			Board.grille[Ligne][Colonne].pion = white;
			Board.lignePionBlanc=Ligne;
			Board.colonnePionBlanc=Colonne;
			moveDone=1;
		}
		else if (current_player_is(black))
		{
			Board.grille[Board.lignePionNoir][Board.colonnePionNoir].pion = none ;
			Board.grille[Ligne][Colonne].pion = black;
			Board.lignePionNoir=Ligne;
			Board.colonnePionNoir=Colonne;
			moveDone=1;
		}
	}
	else
	{
		moveDone=0;
	}
	if (moveDone==1)
	{
		ecrit(colonne,ligne,'9',Board.joueur);
		Board.action=0;
	}
}



/**************************************************************************

 * Indique si il y a un pion ou non sur la case demandée
 * -1 = aucun pion
 *  0 = pion blanc
 *  1 = pion noir

 **************************************************************************/
int get_position(const struct board *bglobal, int ligne, int colonne)
{
	int yaQuoi=-1;

	switch (Board.grille[ligne][colonne].pion)
    {
		case -1:
			yaQuoi = -1;
		break;
		case 0:
			yaQuoi = 0;
		break;
		case 1:
			yaQuoi = 1;
		break;
    }
	return yaQuoi;
}




/************************************************************

 * Retourne le nombre de murs restants pour le joueur actuel

*************************************************************/
unsigned int remaining_bridges(const struct board* bglobal, unsigned int player)
{
	unsigned int nbWalls;

	if (player==1)
	{
		nbWalls=bglobal->murNoirRestant;
	}

	else if ( player == 0)
	{
		nbWalls=bglobal->murBlancRestant;
	}
	return nbWalls;
}



/********************************************************

 * Fonction qui place un mur
 * Direction : 0 = horizontal, 1 = vertical
 * Faudrait qu'elle appelle is_blockable

 *******************************************************/
void place_wall(const struct board *b, char colonne, char ligne, char direction)
{
	int Ligne = ligne - '1';
	int Colonne = colonne - 'a';
	int Direction = direction -'0';
	int currentPlayer = b->joueur;
	int remainingWalls;
	int wallPlaced=0;


    remainingWalls= remaining_bridges(bglobal, currentPlayer);

	if (remainingWalls>=1)
	{
		if (Direction==1)
		{
			Board.grille[Ligne][Colonne].murDroite=1;
			Board.grille[Ligne][Colonne].origineMur=1;
			Board.grille[Ligne+1][Colonne].murDroite=1;
			printf("Je place un mur vertical\n");
			wallPlaced=1;
		}
		else if ( Direction == 0)
		{
			Board.grille[Ligne][Colonne].murBas=1;
			Board.grille[Ligne][Colonne].origineMur=1;
			Board.grille[Ligne][Colonne+1].murBas=1;
			printf("je place une mur horizontal\n");
			wallPlaced=1;
		}

		if (currentPlayer==0)
		{
			Board.murBlancRestant--;
		}
		else if ( currentPlayer==1)
		{
			Board.murNoirRestant--;
		}
	}
	if (wallPlaced==1)
    {
		ecrit(colonne, ligne, direction, currentPlayer);
		Board.action=0;
    }

}
