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
  if ( Board.lignePionNoir==0 || Board.lignePionBlanc==8)
  {
    return 0;
  }
 
  else return 1;
}


/********************************************************************************/
void init_board (const struct board *bglobal)
{

	//d'abords on enlève tout sur le plateau/board

	for ( int i=0; i<9; i++)
	{

		for (int j=0; j<9; j++)
		{
			Board.grille[i][j].pion = -1;
			Board.grille[i][j].murDroite = 0;
			Board.grille[i][j].murBas = 0;
			Board.grille[i][j].origineMur = 0;
		}
	}

	//ensuite on rajoute les 2 pions a leur départ respectif
	Board.grille[0][4].pion = 0;
	Board.grille[8][4].pion = 1;


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
 autorise (qu'il ne se déplace pas de plus de 1 case
 ou qu'il n'aille pas en dehors du board

**********************************************************/
int is_move_valid(const struct board *bglobal, int colonne, int ligne)
{
	int isMoveValid;
	if (bglobal->joueur==1 && Board.grille[ligne][colonne].pion==0)
	{
		isMoveValid=0;
	}
	else if (bglobal->joueur==0 && Board.grille[ligne][colonne].pion==1)
	{
		isMoveValid=0;
	}

   

	//test pion noir
	if (bglobal->joueur==1)
	{
		//cas mouvement normal
		if ( (distance_between(colonne,bglobal->colonnePionNoir)==1 && distance_between(ligne,bglobal->lignePionNoir)==1) ==0 )
		{
			if(colonne==Board.colonnePionNoir)
			{
				if (ligne==Board.lignePionNoir+1 || ligne==Board.lignePionNoir-1)
					isMoveValid=1;
			}

			else if(ligne==Board.lignePionNoir)
			{
				if (colonne==Board.colonnePionNoir+1 || colonne==Board.colonnePionNoir-1)
					isMoveValid=1;
			}

			else
				isMoveValid=0;
		}
		//cas saut de pion
		if ( distance_between(colonne,bglobal->colonnePionNoir)==2 || distance_between(ligne,bglobal->lignePionNoir==2) )
		{
			if ( distance_between(colonne,bglobal->colonnePionNoir)==0 || distance_between(ligne,bglobal->lignePionNoir)==0) 
			{
				//cas mouvement en ligne
				if (distance_between(colonne,bglobal->colonnePionNoir)==2)
				{
					// cas vers la gauche
					if ( ((colonne-bglobal->colonnePionNoir)>0) &&  (Board.grille[ligne][(colonne + bglobal->colonnePionNoir)/2].pion==1 &&  (Board.grille[ligne][bglobal->colonnePionNoir].murDroite==0 )) )
						isMoveValid=1;
					//cas vers la droite
					else if ( ((colonne-bglobal->colonnePionNoir)<0) &&  (Board.grille[ligne][(colonne + bglobal->colonnePionNoir)/2].pion==1 &&  (Board.grille[ligne][(colonne + bglobal->colonnePionNoir)/2].murDroite==0 )) )
						isMoveValid=1;
					else
						isMoveValid=0;
				}
				//cas mouvement en colonne
				if  (abs(ligne-bglobal->lignePionNoir)==2)
				{
					// cas vers le haut
					if ( ((ligne-bglobal->lignePionNoir)<0) &&  (Board.grille[ligne+1][colonne].pion==1) &&  (Board.grille[ligne][colonne].murBas==0 ))
						isMoveValid=1;
					//cas vers le bas
					else if ( ((ligne-bglobal->lignePionNoir)>0) &&  (Board.grille[ligne-1][colonne].pion==1 &&  (Board.grille[ligne-1][colonne].murBas==0 )) )
						isMoveValid=1;
					else
						isMoveValid=0;
				}
			}
		}
	}

   //test pion blanc
	if (bglobal->joueur==0)
	{
		if ((distance_between(colonne,bglobal->colonnePionBlanc) && distance_between(ligne,bglobal->lignePionBlanc))==0 ) //test: ce n'est pas un mouvement en diag
		{
			if(colonne==Board.colonnePionBlanc)
			{
				if (ligne==Board.lignePionBlanc+1 || ligne==Board.lignePionBlanc-1)
					isMoveValid=1;
			}

			else if(ligne==Board.lignePionBlanc)
			{
				if (colonne==Board.colonnePionBlanc+1 || colonne==Board.colonnePionBlanc-1)
					isMoveValid=1;
			}
			else
				isMoveValid=0;
		}
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
void affiche_board(const struct board *bglobal)
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


