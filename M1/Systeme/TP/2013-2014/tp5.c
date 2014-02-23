#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#define BUFFSIZE 4096
#define FIFO_PATH "/tmp/logger"


int main(int argc, char* argv[])
{
	int n = 0, fd;
	char buf[BUFFSIZE] = "";
	
	time_t rawtime;
	struct tm * timeinfo;
	char date_buffer [22] = "";
	char read_buffer[4074] = "";


	pid_t process_id = 0;
	pid_t sid = 0;
	
	process_id = fork();
	if (process_id < 0)
	{
		printf("fork\n");
		exit(1);
	}
	if (process_id > 0)
	{
		printf("process_id of child process %d \n", process_id);
		exit(0);
	}
	umask(0);
	sid = setsid();
	if(sid < 0)
	{
		exit(1);
	}	
	chdir("/");

	//close(STDIN_FILENO);
	//close(STDOUT_FILENO);
	//close(STDERR_FILENO);

	if(mkfifo(FIFO_PATH, S_IWUSR| S_IRUSR) < 0 && errno != EEXIST){
		perror("mkfifo");
		exit(EXIT_FAILURE);
	}
	

	while(1){
		if((fd = open (FIFO_PATH, O_RDONLY)) < 0){
			perror( "open");
			exit(EXIT_FAILURE);
		}	
		while((n = read(fd, read_buffer, 4074)) > 0){
			read_buffer[n-1] = 0;
			time (&rawtime);
			timeinfo = localtime (&rawtime);
			strftime (date_buffer,22,"%F %T",timeinfo);
			snprintf(buf, sizeof(buf), "%s (%s)\n", read_buffer, date_buffer);

			if(write(STDOUT_FILENO, buf, n+22) != n+22 ){
				perror("write");
				exit(EXIT_FAILURE);
			}
		}		
		if(n < 0){ 
			perror("read");
			exit(EXIT_FAILURE);
		}
		close(fd);
	}
	printf("sortie de la boucle \n");
	exit(EXIT_SUCCESS);
}