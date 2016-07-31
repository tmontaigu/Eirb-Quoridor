#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "./headers/structQuoridor.h"













 int main(int argc, char **argv)
 {

   FILE *Coups;
   init_board(bglobal);//Initialisation du plateau
   affiche_board(bglobal);
   Coups=fopen("fichier_coups.txt", "w+");//initialisation du fichier de Coups
   fclose(Coups);


 while (gagnant(bglobal))
{
  Board.action=1;
  Board.joueur=1;

  while (Board.action==1)
    {
 
      random__play(bglobal);
      
    }
   for (int i=0;i<5000; i++){for (int j=0; j < 50000; j++){}}  //boucle pour bloquer le precessus

  system("clear");
  printf("Noir :");   
  affiche_board(bglobal);

  Board.joueur=0 ;
  Board.action=1;
  
  while (Board.action==1)
    {
  
      random__play(bglobal);   
      
    }

  system("clear");
  printf("Blanc :");
  affiche_board(bglobal);

  for (int i=0;i<5000; i++){for (int j=0; j < 50000; j++){}}
  
  
}
 
 
 return 0;
}
