#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

void ex1(){
  char buffer[BUFSIZ+1];
  int fd[2];
  
  if(pipe(fd) == -1){
    perror("pipe");
    exit(EXIT_FAILURE);
  }
  
  switch(fork()){
  case -1:
    perror("fork");
    exit(EXIT_FAILURE);
    break;
  case 0:
    write(fd[1], "Salut Papa!\n", strlen("Salut Papa!\n"));
    read(fd[0], buffer, BUFSIZ);
    printf("%s", buffer);
    break;
  default:
    if(wait(NULL) == -1){
      exit(EXIT_FAILURE);
    }
    write(fd[1], "Salut Fiston!\n", strlen("Salut Fiston!\n"));
    read(fd[0], buffer, BUFSIZ);
    if(close(fd[1]) == -1){
      perror("close");
    }
    if(close(fd[0]) == -1){
      perror("close");
    }
    printf("%s", buffer);
  }
}

void ex2(){
  char buffer[BUFSIZ+1];
  int file;
  ssize_t i;
  int fd[2];

  if(pipe(fd) == -1){
    perror("pipe");
    exit(EXIT_FAILURE);
  }
  
  if((file = open("utilisateur.txt", 
		  O_RDWR | O_CREAT, S_IRUSR | S_IWUSR)) == -1){
    perror("open");
    exit(EXIT_FAILURE);    
  }  
  switch(fork()){
  case -1:
    perror("fork");
    exit(EXIT_FAILURE);
  case 0:
    if(close(fd[0]) == -1){
      perror("close");
      exit(EXIT_FAILURE);
    }

    if(dup2(fd[1], STDOUT_FILENO) == -1){
      perror("dup2");
      exit(EXIT_FAILURE);
    }
    if(dup2(fd[1], STDERR_FILENO) == -1){
      perror("dup2");
      exit(EXIT_FAILURE);
    } 

    if(execlp("w", "", NULL) == -1){
      perror("execlp");
      exit(EXIT_FAILURE);
    }   
 default:    
   if(close(fd[1]) == -1){
     perror("close");
     exit(EXIT_FAILURE);
   }
   if((i = read(fd[0], buffer, sizeof(buffer))) == -1){
     perror("read");
   }
   if(write(file, buffer, i) == -1){
     perror("write");
    }
    if(close(file) == -1){
      perror("close");
      exit(EXIT_FAILURE);
    }
    if(close(fd[0]) == -1){
      perror("close");
      exit(EXIT_FAILURE);
    }
  }  
}

void ex2_2(){
  char buffer[BUFSIZ+1];
  int fd[2];
  pid_t pid;
  
  if(pipe(fd) == -1){
    perror("pipe");
    exit(EXIT_FAILURE);
  }
  
  if((pid = fork()) == -1){
    perror("fork");
    exit(EXIT_FAILURE);
  }
  if(!pid){
    if(dup2(fd[1], STDOUT_FILENO) == -1){
      perror("dup2");
      exit(EXIT_FAILURE);
    }
    if(dup2(fd[1], STDERR_FILENO) == -1){
      perror("dup2");
      exit(EXIT_FAILURE);
    } 
    if(execlp("w", "", NULL)){
      perror("execlp");
      exit(EXIT_FAILURE);
    }
  } else{
    int i, nb_lines = 0;
    if(close(fd[1])){
      perror("close");
      exit(EXIT_FAILURE);
    }
    if(read(fd[0], buffer, sizeof(buffer)) == -1){
      perror("read");
      exit(EXIT_FAILURE);
    }
    for(i = 0; buffer[i] != '\0'; i++){
      if(buffer[i] == '\n'){
	nb_lines++;
      }
    }
    nb_lines -= 2; // -titre

    printf("nb_lines = %d\n", nb_lines);
    if(close(fd[0])){
      perror("close");
      exit(EXIT_FAILURE);
    }
  }  
}

void ex2_3(){
  int fd[2];
  pid_t pid;
  
  if(pipe(fd) == -1){
    perror("pipe");
      exit(EXIT_FAILURE);    
  }
  if((pid = fork()) == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }
  if(pid == 0){
    if (close(fd[0]) == -1){
      perror("close");
      exit(EXIT_FAILURE);
    }
    if (fd[1] != STDOUT_FILENO) {  
      if (dup2(fd[1], STDOUT_FILENO) == -1){
	perror("dup2");
	exit(EXIT_FAILURE);
      }
      if (close(fd[1]) == -1){
	perror("close");
	exit(EXIT_FAILURE);
      }
      
    }
    if(execlp("w", "", NULL) == -1){ 
      perror("execlp");
      exit(EXIT_FAILURE);
    }
  }
  
  if((pid = fork()) == -1){
    perror("fork");
    exit(EXIT_FAILURE);
  }
  if(pid == 0){
    if (close(fd[1]) == -1){
      perror("close");
      exit(EXIT_FAILURE);
    }
    if (dup2(fd[0], STDIN_FILENO) == -1){
      perror("dup2");
      exit(EXIT_FAILURE);
    }
    if (close(fd[0]) == -1){
      perror("close");
      exit(EXIT_FAILURE);
    }
    if(execlp("wc", "", "-l", (char *) NULL) == -1){
      perror("execlp wc");
      exit(EXIT_FAILURE);
    }
  }
  
  if (close(fd[0]) == -1){
    perror("close");
    exit(EXIT_FAILURE);
  }
  if (close(fd[1]) == -1){
    perror("close");
    exit(EXIT_FAILURE);
  }
  if (wait(NULL) == -1){
    perror("wait");
    exit(EXIT_FAILURE);
  }
  if (wait(NULL) == -1){
    perror("wait");
    exit(EXIT_FAILURE);
  }
  exit(EXIT_SUCCESS);
}

void ex3(int argc, char *argv[]){
  if(argc < 4){
    fprintf(stderr,"need arguments <regex> <file_1> [... <file_n>]\n");
    return ;
  }
  int i;
  int fd[2];
  pid_t pid;
  
  if(pipe(fd) == -1){
    perror("pipe");
    exit(EXIT_FAILURE);    
  }
  
  for(i = 3; i < argc; i++){
    if((pid = fork()) == -1) {
      perror("fork");
      exit(EXIT_FAILURE);
    }
    if(pid == 0){
      printf("%s\n", argv[i]);
      if (close(fd[0]) == -1){
	perror("close 1");
	exit(EXIT_FAILURE);
      }
      if (fd[1] != STDOUT_FILENO) {              /* Defensive check */
	if (dup2(fd[1], STDOUT_FILENO) == -1){
	  perror("dup2");
	  exit(EXIT_FAILURE);
	}
	if (close(fd[1]) == -1){
	  perror("close");
	  exit(EXIT_FAILURE);
	}
	
      }
      if(execlp("grep", "", "-e", argv[2], argv[i],NULL) == -1){ 
	perror("execlp");
	exit(EXIT_FAILURE);
      }
      exit(EXIT_SUCCESS);
    }
  }
    
  if((pid = fork()) == -1){
    perror("fork");
    exit(EXIT_FAILURE);
  }
  if(pid == 0){
    if (close(fd[1]) == -1){
      perror("close");
      exit(EXIT_FAILURE);
    }
    if (dup2(fd[0], STDIN_FILENO) == -1){
      perror("dup2");
      exit(EXIT_FAILURE);
    }
    if (close(fd[0]) == -1){
      perror("close");
      exit(EXIT_FAILURE);
      }
    
    if(execlp("wc", "", "-l", (char *) NULL) == -1){
      perror("execlp");
      exit(EXIT_FAILURE);
    }
  }
  
  if (close(fd[0]) == -1){
    perror("close");
    exit(EXIT_FAILURE);
    }
  if (close(fd[1]) == -1){
    perror("close");
    exit(EXIT_FAILURE);
    }
  if (wait(NULL) == -1){
    perror("wait");
    exit(EXIT_FAILURE);
  }
  if (wait(NULL) == -1){
    perror("wait");
    exit(EXIT_FAILURE);
  }
  
  exit(EXIT_SUCCESS);
  
}

int main(int argc, char *argv[]){
  if(argc < 2){
    fprintf(stderr, "need argument <exercice>\n"
	    "exercice:\n\t"
	    "1\n\t"
	    "2\n\t"
	    "22(ex 2 part 2)\n\t"
	    "23(ex 2 part 3)\n\t"
	    "3\n");    
    return 0;
  }
  
  if(!strcmp("1", argv[1])){
    ex1();
  } else if(!strcmp("2", argv[1])){
    ex2();
  } else if(!strcmp("22", argv[1])){
    ex2_2();
  } else if(!strcmp("23", argv[1])){
    ex2_3();
  } else if(!strcmp("3", argv[1])){
    ex3(argc, argv);
  } else{
    fprintf(stderr, "unknown exercice\n");
  }
  return 0;
}

