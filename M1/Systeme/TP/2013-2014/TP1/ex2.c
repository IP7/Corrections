#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>
#include "ex2.h"

void parcourir_rep(char *directory_name){
  DIR *dir;
  struct dirent *d;
  char path[1024];
  
  if((dir = opendir(directory_name)) == NULL){
    perror("opendir : wrong");
    exit(1);
  }
  while((d = readdir(dir)) != NULL)
    {
      if(DIR_BASE(d->d_name))
	{
	  continue;
	}
      if(snprintf(path, sizeof(path),"%s/%s", directory_name, d->d_name) < 0){
	perror("snprintf : wrong");
	exit(1);
      }
      take_file(path);
    }
  closedir(dir);
}

/*4)*/
void confirme_suppr(char *filename){
  char c;
  while((c = getchar()) != '\0'){
    if(c == 'y' || c == 'Y'){
      if(unlink(filename) == -1){
	perror("unlink : wrong");
	exit(1);
      }
      break;
    } else if(c == 'n' || c == 'N'){
      break;
    }
  }
}
void take_file(char *filename){
  struct stat buf;
  int len = 0;
  if(-1 == stat(filename, &buf)){
    perror("stat: wrong");
    exit(1);
  }
  if(S_ISDIR(buf.st_mode))
    {
      parcourir_rep(filename);
    }
  else if((len = (int)buf.st_size) > 10240)
    {
      printf("%s: size of file = %d, remove file(Y/n)?", filename, len);
      confirme_suppr(filename);
    }
}

int main(int argc, char *argv[])
{
  if(argc == 2){
    take_file(argv[1]);
  }
  else{
    fprintf(stderr, "Need a file in arguments\n");
  }
  return 0;
}
