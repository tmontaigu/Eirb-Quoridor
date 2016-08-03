#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef __unix__
	#include <unistd.h>
	#define clear_console() system("clear");
#elif defined _WIN32
	#include <windows.h>
	#define sleep(x) Sleep(1000 * x)
	#define clear_console() system("cls");
#endif

#include "./headers/structQuoridor.h"

 int main(int argc, char **argv)
 {

	FILE *Coups;
	init_board(bglobal);//Initialisation du plateau
	clear_console();
    printf("Starting the game\n");
	display_board(bglobal);
	Coups=fopen("fichier_coups.txt", "w+");//initialisation du fichier de Coups
	fclose(Coups);

	int numberOfTurn = 0;
	
	while (gagnant(bglobal))
	{
		Board.action = 1;
		Board.joueur = black;

		while (Board.action==1)
		{
			random__play(bglobal); 
		}
				
		sleep(3);
		clear_console();
		printf("Noir Tour %d:\n",numberOfTurn);   
		display_board(bglobal);
		
		Board.joueur = white;
		Board.action = 1;


		while (Board.action==1)
		{
			random__play(bglobal);     
		}


		clear_console();

		printf("Blanc Tour %d:\n",numberOfTurn);
		display_board(bglobal);

		sleep(3);
		numberOfTurn++;
	}
	return 0;
}
