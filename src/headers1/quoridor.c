#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "quoridor.h"

/**********************************************************************
                  
                            Fonctions demandees

***********************************************************************/

/**********************************************************************
                        get_current_player
************************************************************************/
int get_current_player(struct board *b)
{ 
  return(b->actujoueur);
}

/***********************************************************************
                             get_position
***********************************************************************/
int get_position(struct board* b, char column, char line)
{
  int c=column-'a', l=line-'1';
  return(b->Board[c][l].pion);
}

/************************************************************************
                                is_passable
****************************************************************************/
int is_passable(struct board* b, char column, char line, char direction)
{
  int l=line-'1', c = column-'a';
  switch (direction)
    {
    case '2':
      if (b->Board[c][l].droite) return(0);
      break;
    case '1' :
      if (b->Board[c][l].bas) return(0);
      break;
    case '0':
      if (c>0)
	if (b->Board[c-1][l].droite) return(0);
      break;
    case '3':
	if (l>0)
	  if (b->Board[c][l-1].bas) return(0);
      break;
    }
  return(1);
}
/************************************************************************
                            move_pawn
************************************************************************/
//cette fonction n est pas definie precisement car pour le deplacement d un pion il suffit de donner la direction en argument.
void move_pawn(struct board* b, char column, char line)//ca sera mieux de definir le mouvement par une direction
{
  int c=column-'a', l=line-'1';
  char direction=get_direction(b,c,l);//le pion se deplace d une seule case au plus
  if ((direction != 'z') && jouer_pion(b,direction))
    {
    print_coups(column,line,'p',get_current_player(b));//'p'pour specifier que ce n est pas un mur
    (b->tour)++;
    b->actujoueur= 1-b->actujoueur;
    }
  else
    {
      jeu=fopen("fichier_coups.txt","w+");
      fprintf(jeu,"erreur\n");
      fclose(jeu);    
    }
}
/****************************get_direction*******************************/
//cette fonction pour corriger une aberation de l ennoce
char get_direction(struct board *b, int c, char l)
{
  int j=get_current_player(b);
  int x=c-(b->posiPion[j][0]), y=l-(b->posiPion[j][1]);
  if ((x==0) && (y==1)) return('3');//haut
  else if ((x==0) && (y==-1)) return('1');//bas
  else if ((x==1) && (y==0)) return('2');//droite
  else if ((x==-1) && (y==0)) return('0');//gauche
  else return('z');//si la case en argument n est pas voisine a celle du pion
}

/***************************jouer_coup***********************************/
//cette fonction est la meme que move_pawn + corrige l aberation d ajout du test du voisinage de case en argurement par rapport a la case du pion du joueur actuel
int jouer_pion(struct board *b, char direction)
{
  int joueur=get_current_player(b);
  int x,y;

  if (coup_valide(b,direction))
    {
      x=b->posiPion[joueur][0];
      y=b->posiPion[joueur][1];
   
      switch (direction)// les memes cas traites dans coup_valide(voir ci-dessous)
	{
	case '3'://haut
	  (b->Board[x][y]).pion=-1;
	  if ((x==b->posiPion[1-joueur][0]) && (y-1==b->posiPion[1-joueur][1])) y-=2;// pion adversaire bloque chemin avancer deux cases(le mur derriere est traite dans coup_valide)
	  else y--;		
	  b->Board[x][y].pion=joueur;
	  b->posiPion[joueur][1]=y;
	  break;
	case '1' ://bas 
	
	  b->Board[x][y].pion=-1;
	  if ((x==b->posiPion[1-joueur][0]) && (y+1==b->posiPion[1-joueur][1])) y+=2;	//avancer deur case, en sautant sur le pion adversaire
	  else y++;
	  b->Board[x][y].pion=joueur;
	  b->posiPion[joueur][1]=y;
	  break;
	case '0': //gauche
	
	  b->Board[x][y].pion=-1;
	  if ((x-1==b->posiPion[1-joueur][0]) && (y==b->posiPion[1-joueur][1])) x-=2;	//sauter au dessus
	  else x--;
	  b->Board[x][y].pion=joueur;
	  b->posiPion[joueur][0]=x;
	  break;
	case '2': //droite 
	
	  b->Board[x][y].pion=-1;
	  if ((x+1==b->posiPion[1-joueur][0]) && (y==b->posiPion[1-joueur][1])) x+=2;	//sauter au dessus
	  else x++;
	  b->Board[x][y].pion=joueur;
	  b->posiPion[joueur][0]=x;
	  break;
	}
      return(1);
    } 
  return(0);
}
/****************************coup valide***************************************/

//traiter cas avancer diagonnalement!!!
int coup_valide(struct board* b, char direction)
{
  int x, y;
int joueur=get_current_player(b);
    
  switch(direction)
    {//grille inversee pour les lignes
    case '3'://haut 
      x=b->posiPion[joueur][0];
      y=b->posiPion[joueur][1];
      if (y==0 || b->Board[x][y-1].bas==1) return 0;// monter en haut sur la 1re ligne ou sauter sur un mur (apres premier test y>0)!
      if ( (y>=1) && (x==b->posiPion[1-joueur][0]) && (y-1==b->posiPion[1-joueur][1]) ) //adversaire=1-joueur
	{  
	  if ( (y>1) && (b->Board[x][y-2].bas==1) ) return 0;//pion adversaire bloque mon chemin et ce dernier est aussi bloque pas un mur derriere
	  return 0; //cas(y==1): pion adversaire sur la 1re ligne.il  ne peut pas sauter!
	}
      return 1;
      break;
      // ce qui est commente apres c est seulement un ajout du traitement du cas "haut" et le reste non commente a de meme traitement que cas "haut!
    case '1'://bas, 
      x=b->posiPion[joueur][0];
      y=b->posiPion[joueur][1];
      if (y==8 || b->Board[x][y].bas==1) return 0;
      if ((y<=7) && (x==b->posiPion[1-joueur][0]) && (y+1==b->posiPion[1-joueur][1]))
	{ 
	  if ((y<7) && (b->Board[x][y+1].bas==1))	 return 0;
	  return 0;//(y==7)
	}
      return 1;	  
      break;
    case '0'://gauche
      x=b->posiPion[joueur][0];
      y=b->posiPion[joueur][1];
      if ((x==0) || b->Board[x-1][y].droite==1) return 0;
      if ((x>=1) && (x-1==b->posiPion[1-joueur][0]) && (y==b->posiPion[1-joueur][1]))
	{ 
	  if ((x>1) && (b->Board[x-2][y].droite==1)) return 0;
	  return 0;//(x==1)
	}
      return 1;	  
      break;
    case '2'://droite
      x=b->posiPion[joueur][0];
      y=b->posiPion[joueur][1];
      if ((x==8) || b->Board[x][y].droite==1) return 0;
      if ((x<=7) && (x+1==b->posiPion[1-joueur][0]) && (y==b->posiPion[1-joueur][1]))
	{ 
	  if ((x<7) && (b->Board[x+1][y].droite==1)) return 0; 
	  return 0;//(x==7)
	}
      return 1;	  
      break;
    }
  return 0;//eviter les BETISES!
    
}  

/*************************************************************************
                         remaining_bridges
***************************************************************************/
int remaining_bridges(struct board *b, int player)
{
  return(b->mur[player]);
}

/*************************************************************************
                             is_blockable
***************************************************************************/
int is_blockable(struct board* b, char column, char line, char direction)
{
  int x=column-'a', y=line-'1';
  struct board tmpboard;//board temporaire
  memcpy(&tmpboard, b, sizeof(struct board));

  if((x<0) || (y<0) || (x>= 8) || (y>=8)) return 0;//dans board
  if((direction != '0') && (direction != '1')) return 0;//pas n importe quoi
  if(direction == '0')//bas
    {
      if((tmpboard.Board[x][y].bas==1) || (tmpboard.Board[x+1][y].bas==1)) 
	return 0;// y a deja un mur
      if (tmpboard.Board[x][y].basvalid == 0)
	return 0;//sinon
      if(x>0)//pas sur 1re colonne
	{
	  tmpboard.Board[x-1][y].basvalid=0;// mettre aussi originebas a 0
	}
      tmpboard.Board[x][y].basvalid=0;//initialiser les var mur
      tmpboard.Board[x+1][y].droitevalid=0;
      tmpboard.Board[x][y].bas=1;
      tmpboard.Board[x+1][y].bas=1;
      tmpboard.Board[x][y].basorigine=1;//marquer comme origine du mur
      //voir si les murs bloquent les chemins ..teste murchemin
      if (chemin_existe(&tmpboard, b->posiPion[BLANC][0], b->posiPion[BLANC][1], 0) && chemin_existe(&tmpboard,b->posiPion[NOIR][0], b->posiPion[NOIR][1], 8))
{     
	return (1);
}
      return (0);
    }
  //meme truc au dessus
  else if (direction='1')//droite 
    {
      if ((tmpboard.Board[x][y].droite==1) || (tmpboard.Board[x][y+1].droite==1)) return 0;
      if ((tmpboard.Board[x][y].droitevalid==0)) return 0;
      if (y>0)
	{
	  tmpboard.Board[x][y-1].droitevalid=0;// mur invalide ne peut pas etre case origine du mur
	}
      tmpboard.Board[x][y].droitevalid=0;
      tmpboard.Board[x][y].basvalid=0;
      tmpboard.Board[x][y].droite=0;
      tmpboard.Board[x][y+1].droite=0;
      tmpboard.Board[x][y].droiteorigine=1;//marquer origine du mur

      if (chemin_existe(&tmpboard, b->posiPion[BLANC][0], b->posiPion[BLANC][1], 0) && chemin_existe(&tmpboard, b->posiPion[NOIR][0], b->posiPion[NOIR][1], 8))
	return (1);
      
      return (0);	  
    }
}

/***************************** chemin_existe*********************************/
int chemin_existe(struct board *b, int x, int y, int ligneGagnante)
{
  	
  int memoire[C][L]={{0,0}};
  int i,j, res;
  if ((y==0) && (ligneGagnante==0)) return 1;
  if ((y==8) && (ligneGagnante==8)) return 1;

  if (ligneGagnante==0) res=chemin_existe_Rec(b, memoire, x, y, ligneGagnante);
  else res=chemin_existe_Rec(b, memoire, x, y, ligneGagnante);
  return res;
}
/******************************chemin_existe_rec **************************/

int chemin_existe_Rec(struct board *b, int memoire[C][L], int x, int y, int ligneGagnante)
{
  int s=0;
  memoire[x][y]=1;//pas la peine de mettre dans chaque if
  if ((y==0) && (ligneGagnante==0))
    {  
      return 1;
    }
  else if ((y==8) && (ligneGagnante==8))
    {
      return 1;
    }
  else{	
          
    if ((y>0) && (memoire[x][y-1]==0) && (b->Board[x][y-1].bas==0))// priorite au haut
      {
	s=chemin_existe_Rec(b,memoire,x,y-1,ligneGagnante);
	if (s>0) return(s);
      }
		
    if ((x<8) && (memoire[x+1][y]==0) && (b->Board[x][y].droite==0))//droite
      {
	s=chemin_existe_Rec(b,memoire,x+1,y,ligneGagnante);
	if (s>0) return(s);
      }
		
    if ((y<8) && (memoire[x][y+1]==0) && (b->Board[x][y].bas==0))//bas
      {
	s=chemin_existe_Rec(b,memoire,x,y+1,ligneGagnante);
	if (s>0) return(s);
      }
	
    if ((x>0) && (memoire[x-1][y]==0) && (b->Board[x-1][y].droite==0))//gauche
      {
	s=chemin_existe_Rec(b, memoire, x-1,y,ligneGagnante);
	if (s>0) return(s);
      }
  }

  return(0); 
}
/******************************************************************************
                                     place_wall
******************************************************************************/

void place_wall(struct board *b, char column, char line, char direction)
{
  int x=column-'a', y=line-'1';
  int joueur=get_current_player(b);
 //jeu=fopen("fichier_coups.txt","w+");

if(is_blockable(b,column,line,direction) && remaining_bridges(b,joueur) )
   {
      if (direction == '0')
	{
	  if (x>0)
	    {
	      b->Board[x-1][y].basvalid=0; // deja initialise dans murvalid pas grave
	    }
	  b->Board[x][y].droitevalid=0;
	  b->Board[x][y].basvalid=0;
	  b->Board[x][y].bas=1;
	  b->Board[x+1][y].bas=1;
	  b->Board[x][y].basorigine=1; 
	  b->mur[joueur] -= 1;
	}
      else if(direction=='1')
	{
	  if (y>0) 
	    {
	      b->Board[x][y-1].droitevalid=0;
	    }				
	  b->Board[x][y].droitevalid=0;
	  b->Board[x][y].basvalid=0;
	  b->Board[x][y].droite=1;
	  b->Board[x][y+1].droite=1;
	  b->Board[x][y].droiteorigine=1;
	  b->mur[joueur] -=1;
	}
    b->actujoueur=1-b->actujoueur;
    b->tour++;
   //  print_coups(column,line,direction,joueur);
   }
   //else
    //fprintf(jeu, "erreur\n");
 // fclose(jeu);    
}


/***************************** print_coups ***********************************/
void print_coups (char colonne, char ligne, char direction, int currentPlayer)
{
    jeu=fopen("fichier_coups.txt","w+");
    fprintf(jeu,"P%d",currentPlayer);
    fprintf(jeu," ");
    fprintf(jeu,"%c%c",ligne, colonne);

    switch (direction)
        {
        case '0':
            fprintf(jeu,"h");
            break;
        case '1':
            fprintf(jeu,"v");
            break;
        default:
            break;
        }
    fprintf(jeu,"\n");
 fclose(jeu);

}



/******************************************************************************************
                                    scan_board
****************************************************************************************/
void scan_board(struct board *b)
{
  int i,j;

  printf("\n");
  printf("   ");
  for (i=0; i<C; i++) 
    {
      printf("%c ",i+'a');
    }
  printf("\n");
  for (j=0; j<C; j++)
    {
      printf("%2d ",j);
      for (i=0; i<C; i++) 
	{
	  if (b->Board[i][j].pion==-1) printf(".");
	  else if (b->Board[i][j].pion==0) printf("O");	
	  else if (b->Board[i][j].pion==1) printf("X");	
	  if (i<8)
	    {
	      if (b->Board[i][j].droite==0) printf(" ");
	      else if (b->Board[i][j].droite==1) printf("|");
	    }
	}
      printf("\n   ");
      if (j<7) 
	{
	  for (i=0; i<8; i++) 
	    {
			 
			
	      if (b->Board[i][j].basorigine==1)
		{
		  printf("--");
		}
	      else if (b->Board[i][j].basorigine==1)
		{
		  if (b->Board[i][j].bas==1) printf("-|");
		  else printf(" |");
		}
	      else 
		{
		  if (b->Board[i][j].bas==0) printf("  ");
		  else if (b->Board[i][j].bas==1) printf("- ");
		}
	    }
	}
      printf("\n");
    }
  printf("Murs BLANC (O): %d    Murs NOIRS (X): %d\n",b->mur[BLANC], b->mur[NOIR]);
}











