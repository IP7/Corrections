#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define NB_PHILOSOPHE 10
#define NB_CONSOMMATEURS 5
#define NB_VOITURES 50
#define NB_CARS 3

pthread_mutex_t drapeau;
pthread_mutex_t pont;
int sens = 0;
int fifo[1000];
int id;
int compteur_cars = 0;
pthread_mutex_t baguette[NB_PHILOSOPHE];
pthread_mutex_t car_mutex[NB_CARS];

typedef struct voiture{
  int id_voiture;
  int sens_voiture;
}voiture;

void *philosopher(void *data){
  int num_philo= *((int *)data);
  int k = 0;
  int i;
  
  for(i = 0; i < 30; i++){
    for(k = 0; k < num_philo + 1; k++){
      sleep(1);
    }
    
    if(pthread_mutex_lock(&baguette[num_philo])){
      perror("pthread_mutex_lock");
      exit(EXIT_FAILURE);
    }      
    sleep(1);
    if(pthread_mutex_lock(&baguette[(num_philo+1)]) % NB_PHILOSOPHE){
      perror("pthread_mutex_lock");
      exit(EXIT_FAILURE);
    }
    printf("%d en train de manger\n", num_philo);
    for(k = 0; k < num_philo + 1; k++){
      sleep(1);
    } 
    if(pthread_mutex_unlock(&baguette[num_philo])){
      perror("pthread_mutex_unlock");
      exit(EXIT_FAILURE);
    }      
    sleep(1);
    if(pthread_mutex_unlock(&baguette[(num_philo+1)]) % NB_PHILOSOPHE){
      perror("pthread_mutex_unlock");
      exit(EXIT_FAILURE);
    }  
  }
  return NULL;
}
void ex1(){
  pthread_t philosophe[NB_PHILOSOPHE];
  int num_philosophe[NB_PHILOSOPHE];
  int i;  

  for(i = 0; i < NB_PHILOSOPHE; i++){
    if(pthread_mutex_init(&(baguette[i]), NULL)){
      perror("pthread_mutex_init");
      exit(EXIT_FAILURE);      
    }
  }
  
  for(i = 0; i < NB_PHILOSOPHE; i++){
    num_philosophe[i] = i;
    if(pthread_create(&(philosophe[i]), 
		      NULL, 
		      philosopher,
		      &(num_philosophe[i]))){
      perror("pthread_create");
      exit(EXIT_FAILURE);
    }
  }
  
  for(i = 0; i < NB_PHILOSOPHE; i++){
    if(pthread_join(philosophe[i], NULL)){
      perror("pthread_join");
    }
  }
}
void *f_product(void *res){
  int i;
  
  for(i = 0; i < 20; i++){    
    if(pthread_mutex_lock(&drapeau)){
      perror("pthread_mutex_lock");
      exit(EXIT_FAILURE);
    }

    printf("product sleep\n");
    sleep(rand() % 3);
    id++;

    if(pthread_mutex_unlock(&drapeau)){
      perror("pthread_mutex_unlock");
      exit(EXIT_FAILURE);
    }  
    sleep(1);
  }
  return NULL;
}
void *f_conso(void* res){
  int n = *((int *)res);
  int i;

  for(i = 0; i < 10; i++){
    if(pthread_mutex_lock(&drapeau)){
      perror("pthread_mutex_lock");
      exit(EXIT_FAILURE);
    }
    if(id < 1){
      if(pthread_mutex_unlock(&drapeau)){
	perror("pthread_mutex_lock");
	exit(EXIT_FAILURE);
      }
      sleep(n);
      continue;
    }
    printf("%d: p[%d] = %d\n", n, id, fifo[id]);    
    id--;
    if(pthread_mutex_unlock(&drapeau)){
      perror("pthread_mutex_lock");
      exit(EXIT_FAILURE);
    }
    sleep(n);
  }
  printf("%d: FIN\n", n);
  return NULL;
}
void ex2(){
  pthread_t producteur;
  pthread_t consommateur[NB_CONSOMMATEURS];
  int i;
  int nom[NB_CONSOMMATEURS];
  id = rand() % 1000;
  for(i = 0; i < 1000; i++){
    fifo[i] = rand() % 100;
  }
  
  if(pthread_mutex_init(&drapeau, NULL)){
    perror("pthread_mutex_init");
    exit(EXIT_FAILURE);      
  }
  
  if(pthread_create (&producteur, NULL, f_product, NULL)){
    perror("pthread_create");
    exit(EXIT_FAILURE);
  }
  
  for(i = 0; i < NB_CONSOMMATEURS; i++){
    nom[i] = i;
    if(pthread_create (&consommateur[i], NULL, f_conso, &(nom[i]))){
      perror("pthread_create");
      exit(EXIT_FAILURE);
    }
  }
  
  if(pthread_join(producteur, NULL)){
    perror("pthread_join");
    exit(EXIT_FAILURE);
  }
  
  for(i = 0; i < NB_CONSOMMATEURS; i++){
    if(pthread_join(consommateur[i], NULL)){
      perror("pthread_join");
      exit(EXIT_FAILURE);
    }
  }
}

void *passage(void *data){
  voiture *v = (voiture *)data;
  int tours = 3;
  int k = 0; // pour eviter une 'famine' interminable
  
  while(tours-- > 0){
    while(sens != v->sens_voiture && k++ != 5){
      sleep(1);
    }
    k = 0;
    if(pthread_mutex_lock(&pont)){
      perror("pthread_mutex_lock");
      exit(EXIT_FAILURE);
    }
    sens = v->sens_voiture;
    printf("Passage de la voiture %d sens %s\n", v->id_voiture, (v->sens_voiture == 0) ? "Nord" : "Sud");
    sens = (v->sens_voiture+1) % 2;
    if(pthread_mutex_unlock(&pont)){
      perror("pthread_mutex_lock");
      exit(EXIT_FAILURE);
    }
    sleep(rand() % 5 + 2);
  }
  printf("%d : FIN\n", v->id_voiture);
  return NULL;  
}

void ex3(){
  pthread_t thread_voitures[NB_VOITURES];
  voiture proprietes_voitures[NB_VOITURES];
  int i;
  
  for(i = 0; i < NB_VOITURES; i++){
    proprietes_voitures[i].id_voiture = i;
    proprietes_voitures[i].sens_voiture = rand() % 2;

    if(pthread_create (&(thread_voitures[i]), NULL, passage, &(proprietes_voitures[i]))){
      perror("pthread_create");
      exit(EXIT_FAILURE);
    }
  }
  
  for(i = 0; i < NB_VOITURES; i++){
    if(pthread_join(thread_voitures[i], NULL)){
      perror("pthread_join");
      exit(EXIT_FAILURE);
    }
  }
}
void *car_roule(void *data){
  char *s = (char *)data;
  int id_car;
  switch(s[0]){
  case 'M': id_car = 0; break;
  case 'V': id_car = 1; break;
  case 'S': id_car = 2; break;
  }
  if(pthread_mutex_lock(&car_mutex[id_car])){
    perror("pthread_mutex_lock");
    exit(EXIT_FAILURE);
  }
  printf("Le car de %s est en route ...\n", s);
  sleep(rand() % 10 + 1);
  printf("Le car de %s est arrivé\n", s);
  if(pthread_mutex_unlock(&car_mutex[id_car])){
    perror("pthread_mutex_lock");
    exit(EXIT_FAILURE);
  }
  return NULL;
}

void *rer_attend(void *data){
  int i = 0;
  sleep(1);
  for(i = 0 ; i < NB_CARS; i++){
    if(pthread_mutex_lock(&car_mutex[i])){
      perror("pthread_mutex_lock");
      exit(EXIT_FAILURE);
    }
  }
  printf("tous les cars sont arrivés, le RER est en route !\n");
  for(i = 0 ; i < NB_CARS; i++){
    if(pthread_mutex_unlock(&car_mutex[i])){
      perror("pthread_mutex_lock");
      exit(EXIT_FAILURE);
    }
  }
  
  return NULL;
}

void ex4(){
  pthread_t car[NB_CARS];
  pthread_t rer;
  int i;
  
  for(i = 0; i < NB_CARS; i++){ 
    if(pthread_mutex_init(&(car_mutex[i]), NULL)){
      perror("pthread_mutex_init");
      exit(EXIT_FAILURE);      
    }
  }

  
  if(pthread_create (&(car[0]), NULL, car_roule, "Marolles")){
    perror("pthread_create");
    exit(EXIT_FAILURE);
  }
  if(pthread_create (&(car[1]), NULL, car_roule, "Villecresnes")){
    perror("pthread_create");
    exit(EXIT_FAILURE);
  }
  if(pthread_create (&(car[2]), NULL, car_roule, "Santeny")){
    perror("pthread_create");
    exit(EXIT_FAILURE);
  }
  if(pthread_create (&rer, NULL, rer_attend, NULL)){
    perror("pthread_create");
    exit(EXIT_FAILURE);
  }
  
  for(i = 0; i < NB_CARS; i++){
    if(pthread_join(car[i], NULL)){
      perror("pthread_join");
      exit(EXIT_FAILURE);
    }
  }
    if(pthread_join(rer, NULL)){
      perror("pthread_join");
      exit(EXIT_FAILURE);
    }  
}

int main(int argc, char *argv[]){  
  srand(time(NULL));
  if(argc < 2){
    fprintf(stderr, "need argument <exercice>\n");
    return 0;
  }
  
  if(!strcmp(argv[1], "1")){
    ex1();
  }
  else if(!strcmp(argv[1], "2")){
    ex2();
  }
  else if(!strcmp(argv[1], "3")){
    ex3();
  }
  else if(!strcmp(argv[1], "4")){
    ex4();
  }
  else {
    fprintf(stderr, "unknown exerice\n");    
  }
  return 0;
}
