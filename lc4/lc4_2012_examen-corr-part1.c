#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int nbQ;
  int minY;
  int minX;
  int cote;
  int pasY;
  int pasX;
} configuration;

typedef int coord[2];
typedef coord ligne[10];


/* question 1.6 */
#define rouge(x) x & 0xFF
#define vert(x) (x & 0xFF00) >> 8
#define bleu(x) (x & 0xFF0000) >> 16
#define estBlanc(x) x & 0xFFFFFF == 0xFFFFFF
#define estNoir(x) !(x & 0xFFFFFF)


int getConf(char *path, configuration *conf) {

  FILE *f;
  if (!(f = fopen(path, "r")))
  {
  	perror ("I/O error");
  	return -1;
  }

  int lus = fscanf(f, "%d %d %d %d %d %d",
                   &(conf->nbQ),
                   &(conf->minY),
                   &(conf->minX),
                   &(conf->cote),
                   &(conf->pasY),
                   &(conf->pasX));
  
  return lus == 6;
}


int main(int argc, char **argv) {
  configuration conf;
  
  if(!getConf("parQCM.cfg", &conf))
    return -1;
  
  printf("Lus: %d %d %d %d %d %d\n",
	 conf.nbQ,
	 conf.minY,
	 conf.minX,
	 conf.cote,
	 conf.pasY,
	 conf.pasX);
  ligne *l = malloc(sizeof(ligne)*conf.nbQ);
  
  int i, j;
  
  for(i = 0; i < conf.nbQ; i++) {
    printf("coordonees ligne n°%d :", i);
    for(j = 0; j < 10; j++) {
      l[i][j][0] = conf.minX + j*conf.pasX;
      l[i][j][1] = conf.minY + i*conf.pasY;
      printf(" (%d, %d)", l[i][j][0], l[i][j][1]);
    }
    printf("\n");
  }
  
  /* ... */

  free(l);
}
