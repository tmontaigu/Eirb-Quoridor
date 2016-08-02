#include "./headers/interface.h"
#include "./headers/registry.h"
#include "./headers/structQuoridor.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>




struct position
{
	char ligne;
	char colonne;
	int imPlayer;
};

void rand_pawn(struct position MyPosition);
void rand_wall(void);


int randomdir(void)
{
	srand ( time(NULL) );
	int r;
	r=(rand()%(0-4));
	return r;
}



int randomAction(void)
{
	srand ( time(NULL) );
	int r;
	r=(rand()%(0-100));
	return r;
}


int randomWall(void)
{
	srand ( time(NULL) );
	int r;
	r=(rand()%(0-8));
	return r;
}




/*************************************************
   Noir = j1
 * 0=gauche, 2 = Droite , 1 = Bas , 3 = haut
    Blanc = j0
 *  0=gauche, 2 = Droite , 3 = Bas , 1 = haut
***************************************************/


void random__play(const struct board *b)
{
	struct position MyPosition;

	if(b->joueur==1)
	{
		MyPosition.colonne = (b->colonnePionNoir+'a');
		MyPosition.ligne = (b->lignePionNoir+'1');
		MyPosition.imPlayer=1;
	}
	if(b->joueur==0)
	{
		MyPosition.colonne = b->colonnePionBlanc+'a';
		MyPosition.ligne= b->lignePionBlanc+'1';
		MyPosition.imPlayer=0;
	}

	if(randomAction() > 35)
	{
		rand_pawn(MyPosition);
	}
	else 
		rand_wall();
}






void rand_pawn(struct position MyPosition)
{
	int randomDir;
	randomDir=randomdir();
	
	switch (randomDir)
	{
		case 0:
			move_pawn(bglobal, MyPosition.colonne-1, MyPosition.ligne);
		break;
		case 2:
			move_pawn(bglobal, MyPosition.colonne+1, MyPosition.ligne);
		break;
		case 3:
//			if (MyPosition.imPlayer=1)
			move_pawn(bglobal, MyPosition.colonne, MyPosition.ligne+1);
//			else if (MyPosition.imPlayer=0)
//				move_pawn(bglobal, MyPosition.colonne, MyPosition.ligne-1);
		break;
		case 1:
//			if (MyPosition.imPlayer=1)
				move_pawn(bglobal, MyPosition.colonne, MyPosition.ligne-1);
//			else if (MyPosition.imPlayer=0)
//				move_pawn(bglobal, MyPosition.colonne, MyPosition.ligne+1);
		break;
		}
}




void rand_wall(void)
{
	int imPlayer;
	int l,c,d;

	imPlayer = get_current_player(bglobal);

	if (remaining_bridges(bglobal, imPlayer))
	{
		l=randomWall();
		c=randomWall();
		d=randomdir()%2;
		place_wall(bglobal,c+'a', l+'1',d+'1');
	}
}
