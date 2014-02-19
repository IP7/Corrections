#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NB_CONSOMMATEURS 20
#define SIZE_TAB 100
#define OVER (-1)

int tab[SIZE_TAB];
pthread_mutex_t lock;
int readpos, writepos;
pthread_cond_t non_vide;
pthread_cond_t non_plein;

//appeler par le producteur pour ajouter une valeur a la pile tab
void add(int data)
{
  if(pthread_mutex_lock(&lock)){
    perror("pthread_mutex_lock");
    exit(EXIT_FAILURE);
  }
  while ((writepos + 1) % SIZE_TAB == readpos) {
    if(pthread_cond_wait(&non_plein, &lock)){
      perror("pthread_cond_wait");
      exit(EXIT_FAILURE);
    }
  }
  tab[writepos] = data;
  writepos++;
  if (writepos >= SIZE_TAB){
    writepos = 0;
  }
  if(pthread_cond_signal(&non_vide)){
    perror("pthread_cond_signal");
    exit(EXIT_FAILURE);
  }
  if(pthread_mutex_unlock(&lock)){
    perror("pthread_mutex_unlock");
    exit(EXIT_FAILURE);
  }
}

//apeller par les conso pour enlever une valeur
int get()
{
  int value;
  if(pthread_mutex_lock(&lock)){
    perror("pthread_mutex_lock");
    exit(EXIT_FAILURE);
  }
  while (writepos == readpos) {
    if(pthread_cond_wait(&non_vide, &lock)){
      perror("pthread_cond_wait");
      exit(EXIT_FAILURE);
    }
  }
  value = tab[readpos];
  readpos++;
  if (readpos >= SIZE_TAB){
    readpos = 0;
  }
  if(pthread_cond_signal(&non_plein)){    
    perror("pthread_cond_signal");
    exit(EXIT_FAILURE);
  }
  if(pthread_mutex_unlock(&lock)){
    perror("pthread_cond_wait");
    exit(EXIT_FAILURE);
  }
  return value;
}

void * producter(void * value)
{
  int i;
  for (i = 0; i < SIZE_TAB; i++) {
    add(i);
  }
  for (i = 0; i < NB_CONSOMMATEURS; i++) {
    add(OVER);
  }    
  printf("producteur fini\n");
  return NULL;
}

void * consommateur(void * value)
{
  int id_conso = *((int *) value);
  int i;
  while((i = get()) != OVER){
    printf("(%d) i = %d\n", id_conso, i);
  }
  printf("consommateur %d fini\n", id_conso);
  return NULL;
}

int ex1(void)
{
  pthread_t th_prod, th_conso[NB_CONSOMMATEURS];
  int num_conso[NB_CONSOMMATEURS];
  int i = 0;
  void * retval;
  
  pthread_mutex_init(&lock, NULL);
  pthread_cond_init(&non_vide, NULL);
  pthread_cond_init(&non_plein, NULL);
  readpos = 0;
  writepos = 0;
  
  /* creation des threads*/
  pthread_create( &th_prod, NULL, producter, 0 );
  for(i = 0; i < NB_CONSOMMATEURS; i++){
    num_conso[i] = i;
    if(pthread_create( &th_conso[i], NULL, consommateur, &(num_conso[i]))){
      perror("pthread_create");
      exit(EXIT_FAILURE);
    }
  }
  /* attendre la terminaison des threads*/
  pthread_join(th_prod, &retval);
  for(i = 0; i < NB_CONSOMMATEURS; i++){
    pthread_join(th_conso[i], &retval);
  }
  return 0;
}


int main(int argc, char *argv[]){
  if(argc < 2){
    fprintf(stderr, "need argument: <exercice>\n");
    return EXIT_FAILURE;
  }
  
  if(!strcmp(argv[1], "1")){
    ex1();
  } else {
    fprintf(stderr, "exercice doesn't exist\n");
  }
  
  return EXIT_SUCCESS;
}
