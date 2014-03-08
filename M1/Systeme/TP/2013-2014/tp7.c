//
//  tp7.c
//  tp7
//
//  Created by Salmon on 07/03/2014.
//  
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <limits.h>

void ex1(const int argc, char const *argv[]){
	char *err;
    int n = 0;
	int i = 0;
	int j = 0;
	char *numbers = NULL;
   
	if(argc < 3){
        fprintf(stderr, 
        "Pour l'exercice 1: besoin d'un argument supplementaire <entier>\n");
		exit(EXIT_FAILURE);
	}

    n = (int)strtol(argv[2], &err, 10);
    
    if (*err || n < 0) {
        fprintf(stderr, "Conversion de l'argument en entier raté\n");
        exit(EXIT_FAILURE);
    }
    
	if((numbers = malloc(sizeof(char) * n)) == NULL){
		perror("malloc");
		exit(EXIT_FAILURE);
	}
    
	memset(numbers, 0, n);
    
	for(i = 2; i < n; i++){
		sleep(1);
		numbers[i] = (numbers[i] == 0) ? 0 : 1;
		for(j = i*2; !numbers[i] && j < n; j+=i){
			numbers[j] = 1;
		}
	}
    
	printf("[");
	for(i = 2; i < n; i++){
		if(!numbers[i]){
			printf("%d ", i);
		}
	}
	printf("]\n");
	free(numbers);
}

void signal_handler(const int signal_id){
	if(signal_id == SIGSEGV){
		char *c = "Lecture à l'adresse nulle interdite.\n";
		write(STDERR_FILENO, c, strlen(c));
		exit(EXIT_FAILURE);
	} else {
		char *c = "Ctrl+C intercepté\n";
		write(STDERR_FILENO, c, strlen(c));
	}
}

//Exercice 1, question 1
void ex2_1(const int argc, const char *argv[]){
    int fd;
    struct stat finfo;
    char *projection;
    
    if(argc < 4){
        fprintf(stderr, 
        "l'exercice 2 (question 1) a besoin d'un argument <fichier>\n");
        exit(EXIT_FAILURE);
    }
    
    if((fd = open(argv[3], O_RDONLY)) < 0){
        perror("open");
        exit(EXIT_FAILURE);
    }
    if(fstat(fd, &finfo)< 0){
        perror("fstat");
        if(close(fd)){
        	perror("close");
        }
        exit(EXIT_FAILURE);
    }
    // Note: les protections du mmap doivent respecter les permissions du 
    // descripteur
    if((projection = mmap(NULL, finfo.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) 
    	== MAP_FAILED){ 
        perror("mmap");
        if(close(fd)){
        	perror("close");
        }
        exit(EXIT_FAILURE);
    }
    
    if(close(fd)){ 
    	perror("close");
	    if(munmap((void *)projection, finfo.st_size)){ 
	    	perror("munmap");
    	}
    	exit(EXIT_FAILURE);
    }

    if(write(STDOUT_FILENO, projection, finfo.st_size) < 0){
    	perror("write");
	    if(munmap((void *)projection, finfo.st_size)){
	    	perror("munmap");
    	}
    	exit(EXIT_FAILURE);
    }

    if(munmap((void *)projection, finfo.st_size)){ // on libere la memoire
    	perror("munmap");
    	exit(EXIT_FAILURE);
    }
}


void ex2_2(const int argc, const char *argv[]){
	int fd1, fd2;
	char *projection1, *projection2;
	struct stat finfo1, finfo2;

	if (argc != 5){
		fprintf(stderr, 
				"Pour la question 2 de l'exercice 2," 
				"il faut deux noms de fichiers en parametre\n");
		exit(EXIT_FAILURE);
	}

	if ((fd1 = open (argv[3], O_RDONLY)) < 0){
		perror("open (fichier 1)");
		exit(EXIT_FAILURE);
	}

	if ((fd2 = open (argv[4], O_RDWR | O_CREAT | O_TRUNC)) < 0){
		perror("open (fichier 2)");
		if(close(fd1)){
			perror("close (fichier 1)");
		}
		exit(EXIT_FAILURE);
	}

	if (fstat (fd1,&finfo1) < 0){
		perror("fstat (fichier 1)");
		if(close(fd1)){
			perror("close (fichier 1)");
		}
		if(close(fd2)){
			perror("close (fichier 2)");
		}	
		exit(EXIT_FAILURE);
	}

	if(ftruncate(fd2, finfo1.st_size)){
		perror("ftruncate");
		if(close(fd1)){
			perror("close (fichier 1)");
		}
		if(close(fd2)){
			perror("close (fichier 2)");
		}	
		exit(EXIT_FAILURE);
	}

	if (fstat (fd2,&finfo2) < 0){
		perror("fstat (fichier 1)");
		if(close(fd1)){
			perror("close (fichier 1)");
		}
		if(close(fd2)){
			perror("close (fichier 2)");
		}	
		exit(EXIT_FAILURE);
	}

	
	if ((projection1 = mmap(0, finfo1.st_size, PROT_READ, MAP_SHARED, fd1, 0)) 
		== MAP_FAILED){
		perror("mmap (fichier 1)");
		if(close(fd1)){
			perror("close (fichier 1)");
		}
		if(close(fd2)){
			perror("close (fichier 2)");
		}	
		exit(EXIT_FAILURE);
	}

	if ((projection2 = mmap(0, 
							finfo2.st_size, 
							PROT_READ | PROT_WRITE,
							MAP_SHARED, 
							fd2, 
							0)) 
		== MAP_FAILED){
		
		perror("mmap (fichier 2)");
		if(munmap((void *)projection1, finfo2.st_size)){ //on libere la memoire
    		perror("munmap (fichier 1)");
    	}
		if(close(fd1)){
			perror("close (fichier 1)");
		}
		if(close(fd2)){
			perror("close (fichier 2)");
		}	
		exit(EXIT_FAILURE);		
	}

	memcpy (projection2, projection1, finfo1.st_size);

	if(munmap((void *)projection1, finfo1.st_size)){ // on libere la memoire
    	perror("munmap (fichier 1)");
    }
	
	if(munmap((void *)projection2, finfo2.st_size)){ // on libere la memoire
    	perror("munmap (fichier 2)");
    }

    if(close(fd1)){
    	perror("close (fichier 1)");
    }
	if(close(fd2)){
		perror("close (fichier 2)");
	}    
}

void ex3_1(){
	int fd;
	struct stat finfo;
	char *projection;
	pid_t p;
	//volatile int *i = 0;

	// si le fichier n'existe pas on le crée, sinon on vire tout ce qu'il y a dedans
	if((fd = open("synchro", 
				  O_CREAT | O_TRUNC | O_RDWR, 
				  S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH )) < 0){
		perror("open");
		exit(EXIT_FAILURE);
	}

	if(write(fd, "0000\0", 5) < 0){
		perror("write");
		exit(EXIT_FAILURE);
	}

    if(fstat(fd, &finfo)< 0){
        perror("fstat");
        if(close(fd)){
        	perror("close");
        }
        exit(EXIT_FAILURE);
    }
    // Note: les protections du mmap doivent respecter les permissions du 
    // descripteur
    if((projection = mmap(NULL, finfo.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) 
    	== MAP_FAILED){ 
        perror("mmap");
        if(close(fd)){
        	perror("close");
        }
        exit(EXIT_FAILURE);
    }

	if((p = fork()) < 0){
		perror("fork");
		exit(EXIT_FAILURE);
	}

	//child fork
	if(p == 0){		
		char c[5];

		sleep(=&à);
		
		//on recopie le pid dans un buffer;
		c[4] = 0;
		snprintf(c, sizeof(c), "%d", getpid());
		memcpy(projection, c, finfo.st_size);	
		exit(EXIT_SUCCESS);		
	}
	//dady
	if(wait(NULL) == -1){
		perror("wait");
	    if(close(fd)){ 
	    	perror("close");
		}
		if(munmap((void *)projection, finfo.st_size)){ 
		   	perror("munmap");
	    }
		exit(EXIT_FAILURE);
	}

	if(write(STDOUT_FILENO, projection, finfo.st_size)){
		perror("write");
	}

    if(close(fd)){ 
    	perror("close");
	    if(munmap((void *)projection, finfo.st_size)){ 
	    	perror("munmap");
    	}
    	exit(EXIT_FAILURE);
    }

    if(munmap((void *)projection, finfo.st_size)){ // on libere la memoire
    	perror("munmap");
    	exit(EXIT_FAILURE);
    }

}

void ex3_2(){
	volatile int *addr;
	addr = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
	if(addr == MAP_FAILED){
		perror("mmap");
		exit(EXIT_FAILURE);
	}

	switch(fork()){
		case -1: perror("fork"); exit(EXIT_FAILURE);
		case 0: 
				sleep(10);
				*addr = getpid(); 
				exit(EXIT_SUCCESS);
		default:
				if(wait(NULL) == -1){
					perror("wait");
					exit(EXIT_FAILURE);
				}
				printf("%d\n", *addr);
	}
	if(munmap((void *)addr, sizeof(int))){ // on libere la memoire
    	perror("munmap (fichier 2)");
    }
}

int main(const int argc, const char * argv[]){
    struct sigaction sa;
    
	if(argc < 2){
		fprintf(stderr, "Need one argument <exercice>\n");
		return 1;
	}
    
	memset(&sa, 0, sizeof(sa));
    sa.sa_handler = signal_handler;
	sa.sa_flags = SA_RESETHAND;
	sigemptyset(&(sa.sa_mask));
	if(sigaction(SIGSEGV, &sa, NULL)){
			perror("sigaction");
		exit(EXIT_FAILURE);
	}
	if(sigaction(SIGINT, &sa, NULL)){
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
    
	if(!strcmp(argv[1], "1")){
		ex1(argc, argv);
	} else if(!strcmp(argv[1], "2")){
		if(argc < 3){
			fprintf(stderr, "Donnez une question a faire <int>\n");
		} else if(!strcmp(argv[2], "1")){
			ex2_1(argc, argv);
		} else if(!strcmp(argv[2], "2")){
			ex2_2(argc, argv);
		} else {
			fprintf(stderr, "La question donnée, "
							"pour l'exerice 2, n'existe pas\n");
		}
	} else if(!strcmp(argv[1], "3")){
		if(argc < 3){
			fprintf(stderr, "Donnez une question a faire <int>\n");
		} else if(!strcmp(argv[2], "1")){
			ex3_1();
		} else if(!strcmp(argv[2], "2")){
			ex3_2();
		} else {
			fprintf(stderr, "La question donnée, "
							"pour l'exerice 3, n'existe pas\n");
		}
	}  else {
		fprintf(stderr, "Exercice inconnu\n");
	}
    return 0;
}
