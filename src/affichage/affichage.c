/*
Pour compiler:
cc -std=c99 -Wall -o affichage affichage.c -lncurses
*/

#include "affichage.h"
void board(WINDOW *win, int lines, int cols, int tile_width, int tile_height, int y1, int x1, int y2, int x2, Element  plateau[9][9])
{
  wclear(win);
  int endy, endx, i,k,j;
  endy =  lines * tile_height;
  endx =  cols  * tile_width;

  /************************* affichage tableau "vide" ***************************************************************/
 
 //affiche le cadre exterieur
  for(j = 0; j <= endy+4; j += 1+lines*tile_height)
    for(i = 0; i <= endx; ++i)
      mvwaddch(win, j, i, ACS_HLINE);
  for(i = 0; i <= endx; i += lines*tile_width)
    for(j = 0; j <= endy; ++j)
      mvwaddch(win, j, i, ACS_VLINE);
  mvwaddch(win, 0, 0, ACS_ULCORNER);
  mvwaddch(win, endy+1,0, ACS_LLCORNER);
  mvwaddch(win, 0, endx, ACS_URCORNER);
  mvwaddch(win, endy+1, endx, ACS_LRCORNER);
  //affiche les lignes horizontales et les coins 
  for(j = 1; j <= endy; j += tile_height)
    for (k=0;k<9;k++)	
      for(i = 1; i <= tile_width-3; ++i)
	{
	  mvwaddch(win, j, i+k*tile_width, ACS_HLINE);
	  mvwaddch(win, j+tile_height-2, i+k*tile_width, ACS_HLINE);
	  mvwaddch(win,j ,1+ k*tile_width, ACS_ULCORNER);
	  mvwaddch(win, j,tile_width-3+ k*tile_width, ACS_URCORNER);
	  mvwaddch(win,j+tile_height-2 ,1+ k*tile_width, ACS_LLCORNER);
	  mvwaddch(win,j+tile_height-2 ,tile_width-3+ k*tile_width, ACS_LRCORNER);
	}
  //affiche les lignes verticales
  for(i = 1; i <= endx; i += tile_width)
    for (k=0;k<9;k++)		
      for(j = 2; j <= tile_height-2; ++j)
	{
	  mvwaddch(win, j+k* tile_height, i, ACS_VLINE);
	  mvwaddch(win, j+k* tile_height, i+tile_width-4, ACS_VLINE);
	}
  //affiche les reperes sur les cotes
  for (int n=1; n<10; n++)
    {
      mvprintw(2+5*(n-1),endx+2,"%d",n);
    }		       
  for(char c='a'; c<'j';c++)
    {
      mvprintw(endy+2,3+(c-'a')*10,"%c",c);
    }

  /***************************** affichage pions et murs **********************************************/
  x1=x1*10+3 ;
  y1=y1*5+2;
  x2=x2*10+3 ;
  y2=y2*5+2;
  
  //affiche pion1
  for(int s=0;s<2;s++)
    for(int q=-1;q<4;q++)
      	mvwaddch(win,y1+s ,x1+q, ACS_CKBOARD);
  //affiche pion2
  for(int s=0;s<2;s++)
    for(int q=-1;q<4;q++)
      mvwaddch(win,y2+s ,x1+q, ACS_DIAMOND);
 
  //affiche murs
  for (int i=0;i<9;i++)
    for (int k=0;k<9;k++)
      {
	if (plateau[i][k].M==1)
	  {
	    debug= fopen("debug.txt","a");
	    fprintf(debug, "on affiche un mur vertical \n ");
	    fclose(debug);	    
	    
	    for (int j=0;j<9;j++)
	      mvwaddch(win,k*5+1+j,i*10+9, ACS_CKBOARD) ; 
	  }
	if (plateau[i][k].M==0)
	  {
	    debug= fopen("debug.txt","a");
	    fprintf(debug, "on affiche un mur horizontal \n ");
	    fclose(debug);	    
	    for(int v=0;v<17;v++)
	      mvwaddch(win,k*5+5,i*10+1+v, ACS_CKBOARD) ; 
	  }
      }
    wrefresh(win);
}

/********************* traduit une ligne en entree et ecrit les murs dans plateau *************************************/

case_mur traduit(char *chaine,Element plateau[9][9])
{
  case_mur C;
  //si on a deux cases
  if (chaine[2]==' ' && ( chaine[5]==' ' || chaine[5]=='\n'))
    {
      debug= fopen("debug.txt","a");
      fprintf(debug, "case _ case \n");
      fclose(debug);	    
      C.C1.dir=-1;
      C.C2.dir=-1;
      C.C1.x=(chaine[0]- 96-1) ;
      C.C1.y= (chaine[1]-'0'-1);
      C.C2.x=(chaine[3]- 96-1) ;
      C.C2.y= (chaine[4]-'0'-1);
    }
  //si on a deux murs
  if (chaine[2]!=' ' && ( chaine[6]!=' ' && chaine[6]!='\n'))
    {
      debug= fopen("debug.txt","a");
      fprintf(debug, "deux murs \n ");
      fclose(debug);	    
      C.C1.x=(chaine[0]- 96-1) ;
      C.C1.y= (chaine[1]-'0'-1);
      C.C2.x=(chaine[4]- 96-1) ;
      C.C2.y= (chaine[5]-'0'-1);
      if (chaine[2]=='h')
	{
	  C.C1.dir=0;
	  plateau[C.C1.x][C.C1.y].M=0;
	}
      else
	{
	  plateau[C.C1.x][C.C1.y].M=1;
	  C.C1.dir=1;
	}
      if (chaine[6]=='h')
	{
	  C.C2.dir=0;
	  plateau[C.C2.x][C.C2.y].M=0;
	}
      else
	{
	  plateau[C.C2.x][C.C2.y].M=1;
	  C.C2.dir=1;
	}
    }
  // cas case _ mur
  if (chaine[2]==' ' && (chaine[5]!=' ' && chaine[5]!='\n'))
   {
     debug= fopen("debug.txt","a");
     fprintf(debug, "case _ mur \n");
     fclose(debug);	    
     C.C1.dir=-1;
     C.C1.x=(chaine[0]- 96-1) ;
     C.C1.y= (chaine[1]-'0'-1);
     C.C2.x=(chaine[3]- 96-1) ;
     C.C2.y= (chaine[4]-'0'-1);
     //on traduit la direction
     if (chaine[5]=='h')
       {
	 C.C2.dir=0;
	 plateau[C.C2.x][C.C2.y].M=0;
       }
      else
	{
	  plateau[C.C2.x][C.C2.y].M=1;
	  C.C2.dir=1;
	}
   }
  //cas  mur_case
  if (chaine[3]==' ' && chaine[6]=='\n' )
    {
      debug= fopen("debug.txt","a");
      fprintf(debug, "  mur_case \n");
      fclose(debug);	    
      C.C2.dir=-1;
      C.C1.x=(chaine[0]- 96-1) ;
      C.C1.y= (chaine[1]-'0'-1);
      C.C2.x=(chaine[4]- 96-1) ;
      C.C2.y= (chaine[5]-'0'-1);
      //on traduit la direction
      if (chaine[2]=='h')
	{
	  C.C1.dir=0;
	 plateau[C.C1.x][C.C1.y].M=0;
	}
      else
	{
	  plateau[C.C1.x][C.C1.y].M=1;
	  C.C1.dir=1;
	}
    }
  return C; 
} 


//trouve les pions sur le plateau
case_mur trouve_pions(  Element plateau[9][9])
{
  case_mur C;
  for (int i=0;i<9;i++)
    for(int j=0;j<9;j++)
      {
	if (plateau[i][j].pion==1 )
	  {
	    C.C1.x=i;
	    C.C1.y=j;
	  }	  
	if (plateau[i][j].pion==2)
	  {
	    C.C2.x=i ;
	    C.C2.y=j;
	  }	  
      }
  return C;	    
}


int main()
{
  debug= fopen("debug.txt","w+");
  fclose(debug);
  char chaine[50];
  FILE *descriptif;
  descriptif= fopen("fichier_coups.txt","r");
  //initialisation plateau 
  Element plateau[9][9];
  for (int i=0;i<9;i++)
    for (int j=0;j<9;j++)
      {
	plateau[i][j].M=-1;
	plateau[i][j].pion=-1;
     }
  plateau[4][0].pion=1;
  plateau[4][8].pion=2;

  while(  fgets(chaine, sizeof(chaine),descriptif)!=NULL) {
   
   debug= fopen("debug.txt","a");
   fprintf(debug, "chaine : %s",chaine);
   fclose(debug);
   
   case_mur C;
   C=traduit(chaine,plateau);
   debug= fopen("debug.txt","a");
   fprintf(debug, "traduction:pion1 x: %d y  %d direction: %d  pion2 x:  %d y: %d direction: %d \n ",  C.C1.x, C.C1.y,C.C1.dir, C.C2.x, C.C2.y, C.C2.dir);
   fclose(debug);
   
   //si on deplace les pions , on les remplace sur le plateau	    
   if (C.C1.dir==-1)
     {
       case_mur anciens_pions=trouve_pions(plateau);
       plateau[anciens_pions.C1.x][anciens_pions.C1.y].pion=-1;
       plateau[C.C1.x][C.C1.y].pion=1;
     }
   if (C.C2.dir==-1)
     {
       case_mur anciens_pions=trouve_pions(plateau);
       plateau[anciens_pions.C2.x][anciens_pions.C2.y].pion=-1;
       plateau[C.C2.x][C.C2.y].pion=2;
     }
      
   C=trouve_pions(plateau);
   debug= fopen("debug.txt","a");
   fprintf(debug, "pions trouvés:pion1 x: %d y  %d pion2 x:  %d y: %d \n ",  C.C1.x, C.C1.y, C.C2.x, C.C2.y);
   fclose(debug);	    
   
   initscr();
   board(stdscr, 9, 9,10,5,C.C1.y,C.C1.x,C.C2.y,C.C2.x,plateau);
   refresh();
   getch();
   endwin();
  }
    fclose(descriptif);      
  return 0;
}









