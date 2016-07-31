#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "random_bot.h"
#include "quoridor.h"


int randomdir(void)
{
  srand ( time(NULL) );
  int r;
  r=(rand()%(0-1));
  return r;
}


/*************************************************
   Noir = j1
 * 0=gauche, 2 = Droite , 1 = Bas , 3 = haut
    Blanc = j0
 *  0=gauche, 2 = Droite , 3 = Bas , 1 = haut
***************************************************/

void random_play(struct board *b)
{
    FILE *rstrat;
        rstrat=fopen("random.txt", "w+");
        fprintf(rstrat,"test");

  struct position MyPosition;
  int randomDir;
    if(b->actujoueur==1)
    {
         MyPosition.colonne = (b->posiPion[NOIR][0]+'a');
         MyPosition.ligne = (b->posiPion[NOIR][1]+'1');
        MyPosition.imPlayer=1;
    }
  if(get_current_player(b)==0)
    {
        MyPosition.colonne = b->posiPion[BLANC][0]+'a';
        MyPosition.ligne= b->posiPion[BLANC][1]+'1';
        MyPosition.imPlayer=0;
    }

    fprintf(rstrat,"My Position : Ligne %c, Colonnes %c\n",MyPosition.ligne, MyPosition.colonne);
    fprintf(rstrat, "PLayer :%d\n",b->actujoueur);
    randomDir=randomdir();
    fprintf(rstrat,"Dir=%d\n",randomDir);

    switch (randomDir)
    {
        case 0:
            move_pawn(b, MyPosition.colonne-1, MyPosition.ligne);
            printf("mvt a gauche\n");
            break;
        case 2:
            move_pawn(b, MyPosition.colonne+1, MyPosition.ligne);
            printf("mvt à droite\n");
            fprintf(rstrat,"Colonne : %c, Ligne ; %c",MyPosition.colonne+1, MyPosition.ligne);
            break;
        case 3:
            if (MyPosition.imPlayer=1){
                move_pawn(b, MyPosition.colonne, MyPosition.ligne+1);
                printf("mvt en bas\n");}
            else if (MyPosition.imPlayer=0)
                move_pawn(b, MyPosition.colonne, MyPosition.ligne-1);
            break;
        case 1:
            if (MyPosition.imPlayer=1){
                move_pawn(b, MyPosition.colonne, MyPosition.ligne-1);
                printf("mvt en haut\n");}
            else if (MyPosition.imPlayer=0)
                move_pawn(b, MyPosition.colonne, MyPosition.ligne+1);
            break;
    }


    fclose(rstrat);
}

int gagnant(struct board *b)//cas critique (-1)
{
 if (b->posiPion[BLANC][1]==0) 
 	return(BLANC);
 
 else if (b->posiPion[NOIR][1]==8) 
 	return(NOIR);
 else 
 	return(-1);
 
}


