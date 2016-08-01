#include <stdio.h>
#include <stdlib.h>

#define LIGNES 9
#define COLONNES 9




struct Case
{

 int pion; // -1 si vide, 0 si blanc , 1 si noir.
 int murDroite; // indique si il y a présence d'un mur a droite (gauche cf en bas)
 int murBas;//0 si non, 1 si oui
 int origineMur;// Pour savoir si cette case est l'origine d'un mur
};


struct board
{
  struct Case grille[LIGNES][COLONNES];
  int joueur; //0 si blanc, 1 noir
  int murBlancRestant;
  int murNoirRestant;

  int lignePionBlanc;
  int colonnePionBlanc;

  int lignePionNoir;
  int colonnePionNoir;

  int action;
};

 struct board Board;

extern const struct board *bglobal;

//--------------------------------------------------------------------------------------//


void move_pawn(const struct board *b, char colonne, char ligne);
unsigned int get_current_player(const struct board * bgblobal);
void affiche_board(const struct board *bglobal);
void init_board ( const struct board *bglobal);
int is_move_valid(const struct board *bglobal, int colonne, int ligne);
void random__play(const struct board *bglobal);
int gagnant(const struct board *bglobal);
int ecrit (char colonne, char ligne, char direction, int currentPlayer);
unsigned int remaining_bridges(const struct board* bglobal, unsigned int player);
int distance_between(int a, int b);

