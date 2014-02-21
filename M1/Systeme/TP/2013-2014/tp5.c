//ex1 : man ls | grep -n "display \|list \|display$\|list$" 

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
	char buf[BUFFSIZE];
	
	time_t rawtime;
  struct tm * timeinfo;
  char buffer [80];

  time (&rawtime);
  
	/*pid_t process_id = 0;
	pid_t sid = 0;
	
	// Create child process
	process_id = fork();
	// Indication of fork() failure
	if (process_id < 0)
	{
		printf("fork failed!\n");
		// Return failure in exit status
		exit(1);
	}
	// PARENT PROCESS. Need to kill it.
	if (process_id > 0)
	{
		printf("process_id of child process %d \n", process_id);
		// return success in exit status
		exit(0);
	}
	//unmask the file mode
	umask(0);
	//set new session
	sid = setsid();
	if(sid < 0)
	{
	// Return failure
		exit(1);
	}	
	// Change the current working directory to root.
	chdir("/");
	// Close stdin. stdout and stderr
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	*/
	if(mkfifo(FIFO_PATH, S_IRUSR) < 0 && errno != EEXIST){
		perror("fifoerror");
		exit(EXIT_FAILURE);
	}
	printf("opening %s ...\n ", FIFO_PATH);
	if((fd = open (FIFO_PATH, O_RDONLY)) < 0){
		perror( "open error ");
		exit(EXIT_FAILURE);
	}
	printf( " entering main loop ... \n");
	while(1){
		while((n = read(fd, buf, BUFFSIZE)) > 0){
			if(write(STDOUT_FILENO, buf, n) != n ){
				perror("write error");
				exit(EXIT_FAILURE);
			}
			timeinfo = localtime (&rawtime);
			strftime (buffer,80,"Now it's %I:%M%p.",timeinfo);
			puts(buffer);
		}		
		if(n < 0){ 
			perror("read error");
			exit(EXIT_FAILURE);
		}
	}
	exit(EXIT_SUCCESS);
	return (0);
}