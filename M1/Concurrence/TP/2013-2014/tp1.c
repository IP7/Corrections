#include <stdio.h>
#include <pthread.h>
#define TRUE 1
#define FALSE 0
#define BOOL_STR(var) ((var == 1) ? "true" : "false")
volatile int drapeau = 1; 
volatile int variable = 0;

volatile int x1 = TRUE;
volatile int x2 = TRUE;

static void *enumere (void *p_data){
  int i;
  for(i = 1; i <= 100; i++){
    printf("%d\n", i);
  }
  
  return NULL;
}

void *incr (void *p_data){
  int i;
  for(i = 0; i < 100000; i++){
    drapeau++;
  }
  printf("var = %d\n", drapeau);
  return NULL;
}

void ex1 (void){
  pthread_t ta;
  pthread_t tb;

  if(pthread_create (&ta, NULL, enumere, NULL)){
    perror("pthread_create");
  }
  if(pthread_create (&tb, NULL, enumere, NULL)){
    perror("pthread_create");
  }
  if(pthread_join(ta, NULL)){
    perror("pthread_join");
  }
  if(pthread_join(tb, NULL)){
    perror("pthread_join");
  }
}

//pas de mutex
void ex2(){
  pthread_t ta;
  pthread_t tb;
  
  if(pthread_create (&ta, NULL, incr, NULL)){
    perror("pthread_create");
  }
  if(pthread_create (&tb, NULL, incr, NULL)){
    perror("pthread_create");
  }
  if(pthread_join(ta, NULL)){
    perror("pthread_join");
  }
  if(pthread_join(tb, NULL)){
    perror("pthread_join");
  } 
}

void *f_product(void *res){
  int i;
  for(i = 0; i < 20; i++){
    while(drapeau);
    variable++;
    drapeau = TRUE;
  }
}

void *f_conso(void* res){
  int n = *((int *)res);
  int i;
  
  for(i = 0; i < 10; i++){
    if(drapeau == TRUE){
      drapeau = FALSE;
      printf("%d: drapeau = %s, variable = %d\n", 
	     n, BOOL_STR(drapeau), variable);
    }
    sleep(1);
  }
  printf("%d: FIN\n", n);
}

void ex3(){
  pthread_t producteur;
  pthread_t consommateur[10];
  int i;
  int nom[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  int get_error;

  if(pthread_create (&producteur, NULL, f_product, NULL)){
    perror("pthread_create");
  }
  for(i = 0; i < 10; i++){
    if(pthread_create (&consommateur[i], NULL, f_conso, &(nom[i]))){
      perror("pthread_create");
    }
  }
  
  if(pthread_join(producteur, NULL)){
    perror("pthread_join");
  }
  for(i = 0; i < 10; i++){
    if(pthread_join(consommateur[i], NULL)){
      perror("pthread_join");
    }
  }
}

void *f_th1(){
  int i;
  for(i = 0; i < 10; i++){
    while(!x1); /* on attend que x1 passe a vrai*/
    x1 = FALSE;
    while(!x2);
    x2 = FALSE;
    puts("FALSE");
  }
}

void *f_th2(){
  int i;
  for(i = 0; i < 10; i++){
    while(x1); /* on attend que x1 passe a vrai*/
    x1 = TRUE;
    while(x2);
    x2 = TRUE;
    puts("TRUE");
  }  
}

void ex4(){
  pthread_t ta;
  pthread_t tb;
  
  if(pthread_create (&ta, NULL, f_th1, NULL)){
    perror("pthread_create");
  }
  if(pthread_create (&tb, NULL, f_th2, NULL)){
    perror("pthread_create");
  }
  if(pthread_join(ta, NULL)){
    perror("pthread_join");
  }
  if(pthread_join(tb, NULL)){
    perror("pthread_join");
  } 
}

int main(int argc, char *argv[]){
  if(argc != 2){
    puts("need argument <exercice>");
    return 0;
  }
  
  if(!strcmp(argv[1], "1")){
    ex1();
  } else if(!strcmp(argv[1], "2")){
    ex2();
  } else if(!strcmp(argv[1], "3")){
    ex3();
  } else if(!strcmp(argv[1], "4")){
    ex4();
  } else{
    puts("unknow exercice");
  }
  return 0;
}
