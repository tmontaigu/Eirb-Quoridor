

struct position
{
  char ligne;
  char colonne;
  int imPlayer;
};
/************************************************************************/

int gagnant(struct board *b);
void random_play(struct board *b);
int randomdir(void);
