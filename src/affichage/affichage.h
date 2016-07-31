#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<curses.h>
FILE *debug;

typedef struct cas Case;
struct cas
{
  int x;
  int dir;// 0 pour horizontal 1 pour vertical
  int y;
};

struct elmt
{
  Case C1;
  Case C2;
 };
typedef struct elmt case_mur; 

struct element
{
  int pion;//1 ou 2
  int M;//0 ou 1
};
typedef struct element Element;

