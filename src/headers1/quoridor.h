#define NOIR 1
#define BLANC 0
#define C 9
#define L 9
#define ALLMUR 10
#define INFINI 1000



/****************************
infos sur la case
**************************/
struct Case{
  int bas, droite;//1 si mur a droite ou en bas de la case ,sinon 0
  int basvalid, droitevalid; //1 si mur peut etre pose bas ou a droite de la case, o sinon
  int pion;// -1 si vide, 0 si blanc , 1 si noir.
  int basorigine, droiteorigine; // 1 si cette case  est origine du mur, 0 sinon
};
/***********************************
infos sur la grille
********************************/
// vu que la representation des coups commence par indiquer la colonne,notre tableau struct Case board est la transposee du board reel 
struct board{
struct Case Board[C][L];
int actujoueur;//0 si blanc, 1 noir
int posiPion[2][2];//posiPion[0]:(x,y) du pion BLANC,posiPion[1]:(x,y) du pion NOIR, avec (x,y):cordonnees dans le plan cartesien
int ancPosiPion[2][2];//ancienne position des deux pions
int mur[2];//mur[0]:nombre des mur restants pour joueur BLANC, mur[1]:nombre des murs restants pour le joueur NOIR.
int tour;
};

/*********************************
variable globales
**********************************/
struct board *board;
int voisinX, voisinY;
FILE *jeu;

/************************************************
fonctions demandees
**************************************************/
int get_current_player(struct board * b);
int get_position(struct board* b, char column, char line);
int is_passable(struct board* b, char column, char line, char direction);
void move_pawn(struct board* b, char column, char line);
int remaining_bridges(struct board* b, int player);
int is_blockable(struct board* b, char column, char line, char direction);
void place_wall(struct board *b, char column, char line, char direction);

/************************************************
fonction auxiliaires
***************************************************/
char get_direction(struct board*b, int c, char l);
int jouer_pion(struct board *b, char direction);
int coup_valide(struct board* b, char direction);
int chemin_existe(struct board *b, int x, int y, int ligneGagnante);
int chemin_existe_Rec(struct board *b, int memoire[C][L], int x, int y, int ligneGagnante);
void init_board (struct board* b);
void print_coups (char colonne, char ligne, char direction, int currentPlayer);
void scan_board(struct board *b);
/***********************************************************/


