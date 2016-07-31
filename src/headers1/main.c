#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "quoridor.h"
#include "random_bot.h"


void init_board (struct board* b);

/***************************************************************************
                         initialiser board
************************************************************************/
void init_board (struct board* b)
{
  int i,j;
  for (i=0; i<C; i++)
    for (j=0; j<L; j++)
      {
	b->Board[i][j].pion=-1;
	b->Board[i][j].bas=0;
	b->Board[i][j].droite=0;
	b->Board[i][j].basvalid=1;
	b->Board[i][j].droitevalid=1;
	b->Board[i][j].droiteorigine=0;
	b->Board[i][j].basorigine=0;
      }
  b->mur[BLANC]=ALLMUR;
  b->mur[NOIR]=ALLMUR;
  b->Board[4][0].pion=NOIR;
  b->Board[4][8].pion=BLANC;
  b->posiPion[BLANC][0]=4;
  b->posiPion[BLANC][1]=8;  
  b->posiPion[NOIR][0]=4;
  b->posiPion[NOIR][1]=0;
  b->ancPosiPion[BLANC][0]=4;
  b->ancPosiPion[BLANC][1]=8;
  b->ancPosiPion[NOIR][0]=4;
  b->ancPosiPion[NOIR][1]=0;
  b->tour=0;
}



int main(){

FILE *jeu;
board = malloc(sizeof(struct board));
init_board(board);
printf("entrer la couleur du premier joueur\n");
scanf("%d", &(board->actujoueur));

scan_board(board);

jeu=fopen("fichier_coups.txt", "w+");//initialisation du fichier de Coups
fclose(jeu);
 

  while (gagnant(board)==-1)
    {
 
      random_play(board);
      
    }
   for (int i=0;i<5000; i++){for (int j=0; j < 50000; j++){}}  //boucle pour bloquer le precessus

  system("clear");
  scan_board(board);


  
free(board);

return 0;
}


