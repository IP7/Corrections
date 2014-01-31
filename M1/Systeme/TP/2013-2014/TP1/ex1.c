#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int main()
{
  //size_t count = 128;
  char c[128];
  char buffer[128];
  ssize_t i;
  int j = 0, k = 0, nb_chars = 0;
  
  while((i = read(0, c, 128)) > 0){
    if(!strcmp(c, "exit\n")){
      return 0;
    }

    nb_chars += i;
    
    buffer[0] = (k == 1 && c[0] == '*') ? '^' : c[0];
    
    for(j = 0; k < i; k++, j++){
      if((k < i-1) && (c[k] == c[k+1] && c[k] == '*')){
	buffer[j] = '^';
	k++;
      } else if(c[k] == '^'){
	buffer[j++] = '*';
	buffer[j] = '*';
      } else {
	buffer[j] = c[k];
      }
    }
    k = (c[255] == '*') ? 1 : 0;
    
    if(nb_chars > 80){
      write(1, "\n", 1);
      nb_chars = 0;
    }
    if(write(1, buffer, j) == -1){
      perror("write: wrong");
    }
    for(j = 0; j < 256; j++){
      c[j] = 0;
    }
  }
  return 0;
}
