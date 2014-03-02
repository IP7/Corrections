#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
void ex1(int argc, char const *argv[]){
	int n = 0;
	int i = 0;
	int j = 0;
	char *numbers = NULL;

	if(argc < 3){
		fprintf(stderr, "Need one argument <integer>\n");		
		exit(EXIT_FAILURE);
	}

	n = strtol(argv[2], NULL, 10);
	
	if(errno == EINVAL){
		fprintf(stderr, "invalide argument\n");
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

void ex2(int argc, char const *argv[]){
	pid_t p1, p2; // les pid des deux fils

	printf("pere = %d\n", getpid());
	if((p1 = fork()) == -1){
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if(p1 == 0){
		printf("fils1 = %d\n", getpid());		
		sleep(10);

		printf("fils 1 fin\n");
		exit(EXIT_SUCCESS);
	}

	if((p2 = fork()) == -1){
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if(p2 == 0){
		printf("fils2 = %d\n", getpid());		
		sleep(10);

		printf("fils 2 fin\n");
		exit(EXIT_SUCCESS);
	}
	//sleep(10); //question 1 : Ctrl^C tue le père et ses deux fils 
	//kill(p1, 2);//q3
	//kill(p2, 2);//q3
	//kill(getpid(), 2); // question 2: ce kill ne tue que le pere
}



void signal_handler(int signal_id){
	if(signal_id == SIGSEGV){
		puts( "Lecture à l'adresse nulle interdite.\n");
		exit(EXIT_FAILURE);
	} else {
		puts("Ctrl^C intercepté\n");
	}
}

int main(int argc, char const *argv[])
{
	struct sigaction sa;

	if(argc < 2){
		fprintf(stderr, "Need one argument <exercice>\n");
		return 1;
	}	

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = signal_handler;
	sa.sa_flags = 0;
	sigemptyset(&(sa.sa_mask));
	if(sigaction(SIGSEGV, &sa, NULL) != 0){
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
	if(sigaction(SIGINT, &sa, NULL) != 0){
		perror("sigaction");
		exit(EXIT_FAILURE);
	}

	if(!strcmp(argv[1], "1")){
		ex1(argc, argv);
	} else if(!strcmp(argv[1], "2")){
		ex2(argc, argv);
	} else {
		fprintf(stderr, "Unknown exercice");
	}
	return 0;
}
