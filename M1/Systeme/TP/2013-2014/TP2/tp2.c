#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>

void ex1(){
  pid_t i = 0;
  if((i = fork()) == -1){
    perror("fork : wrong");
    exit(1);
  } 
  if(i == 0){
    printf("je suis le fils\n");
  } else {
    if(wait(NULL) == -1){
      perror("wait : wrong");
      exit(1);
    }
    printf("je suis le pere\n");
  }
}

void ex2(){
  pid_t i = 0;
  if((i = fork()) == -1){
    perror("fork : wrong");
  } 
  if(i == 0){
    for(i = 0 ; i < 10000; i++){
      printf("b\n");
    }
  } else {
    if(wait(NULL) == -1){
      perror("wait : wrong");
      exit(1);
    }
    for(i = 0 ; i < 10000; i++){
      printf("a\n");
    }
  }
}

void ex3(){
  int i = 0;
  for(i = 0; i < 13 ; i++){
    pid_t p = 0;
    if((p = fork()) == -1){
      perror("fork : wrong\n");
      exit(1);
    } 
    if(p == 0){
      printf("fils: %d\n", getpid()); 
      return ;
    } 
  }
}

/*
ex4 : 
2 puissance 3, un arbre parfait de profondeur 3
*/

void ex5(int n){
  int t[10000];
  pid_t p = 0;
  int l = 10000/n;
  int i = 0;
  int k = 0;

  if(n < 1){
    return ;
  }
  
  putchar('[');
  for(i = 0; i < 10000; i++){
    t[i] = rand() % 1000;
    if(t[i] == 42){
      printf("%d ", i); 
    }
  }
  putchar(']');
  putchar('\n');
  
  for(i = 0; i < n ; i++){
    if((p = fork()) == -1){
      printf("error\n");
      exit(1);
    } 
    if(p == 0){
      int j = 0;
      for(j = k; j < k+l; j++){
	if(t[j] == 42){
	  printf("(%d) %d\n", getpid(), j);
	}
      } 
      return ;
    }
    k += l;
  }
}


int main(int argc, char *argv[]){
  srand(time(NULL));
  ex5(10);
  return 0;
}
