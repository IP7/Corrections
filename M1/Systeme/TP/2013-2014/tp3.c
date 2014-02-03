/*
  Note du correcteur : je n'ai pas fais la question 2.3
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

void test_exec(char *cmd, char *args[]){
  if(execve(cmd, args, NULL) == -1){  
    perror("execve");
    exit(1);
  }
}

void ex1(int argc, char *argv[]){
  char **exo_arg;
  int i = 2;
  pid_t p;

  exo_arg = malloc(sizeof(char *) * (argc - 1));
  exo_arg[0] = argv[0];
  for(; i < argc; i++){
    exo_arg[i-1] = argv[i];
  }
  if((p = fork()) == -1){
    perror("fork");
    exit(1);
  } else if (p == 0){
    test_exec("/bin/ls", exo_arg);
  } else {
    if(wait(NULL) == -1){
      perror("wait");
      exit(1);
    }
  }
  free(exo_arg);
}

void ex2(int argc, char *argv[]){
  char **exo_arg;
  int i = 2;
  pid_t p;
  char *cmd;
  if(argc < 3){
    puts("need argument <bin/<cmd>>");
    return ;
  }
  exo_arg = malloc(sizeof(char *) * (argc - 2));
  cmd = malloc(strlen("/bin/") + strlen(argv[2]));
  strcpy(cmd, "/bin/");
  strcat(cmd, argv[2]);
  exo_arg = malloc(sizeof(char *) * (argc));
  exo_arg[0] = cmd;
  for(i = 2; i < argc; i++){
    exo_arg[i-2] = argv[i];
  }
  exo_arg[i] = NULL;
  if((p = fork()) == -1){
    perror("fork");
    exit(1);
  } else if (p == 0){
    test_exec(cmd, exo_arg);
  } else {
    int etat;
    if(wait(&etat) == -1){
      perror("wait");
      exit(1);
    }
    printf("Stat at the end of program = %d\n", etat);
  }
  free(cmd);
}

/*
  il faut mettre le chemin complet de la commande pour qu'elle fonctionne
*/
void ex3(int argc, char *argv[]){  
  char *result[1];
  if(argc < 4){
    puts("need argument (false|true) </bin/cmd> [</bin/cmd>]");
    return ;
  }
  
  result[0] = argv[3];
  result[1] = NULL;
  
  if(!strcmp(argv[2], "true")){
    test_exec(argv[3], result);
  } else if(!strcmp(argv[2], "false")){
    if(argc == 5 ){
      result[0] = argv[4];
      test_exec(argv[4], result);
    }
  } else {
    puts("test non reconnu");
  }
}

int main(int argc, char *argv[]){
  
  if(argc < 2){
    puts("need argument <1,2,3,... (exercice)>");
    return 0;
  }
  if(!strcmp(argv[1], "1")){
    ex1(argc, argv);
  } else if(!strcmp(argv[1], "2")){
    ex2(argc, argv);
  } else if(!strcmp(argv[1], "3")){
    ex3(argc, argv);
  } else {
    puts("exercice doesn't exist");
  }
  return 0;
}
