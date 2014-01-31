#include <stdio.h>
#include <unistd.h>
#include <errno.h>
int error()
{
  switch(errno)
    {
    case EAGAIN: write(2, "egain\n", sizeof("egain\n"));
      return (1);
    case EBADF: write(2, "ebadf\n", sizeof("ebadf\n"));
      return (1);
    case EFAULT: write(2, "efault\n", sizeof("efault\n"));
      return (1);
    case EINTR: write(2, "eintr\n", sizeof("eintr\n"));
      return (1);
    case EINVAL: write(2, "einval\n", sizeof("einval\n"));
      return (1);
    case EIO: write(2, "eio\n", sizeof("eio\n"));
      return (1);
    case EISDIR: write(2, "eisdir\n", sizeof("eisdir\n"));
      return (1);
    case EDESTADDRREQ: write(2, "EDESTADDRREQ\n", sizeof("EDESTADDRREQ"));
      return (1);
    case EDQUOT: write(2, "edquot\n", sizeof("edquot\n"));
      return (1);
    case EFBIG: write(2, "efbig\n", sizeof("efbif\n"));
      return (1);
    case ENOSPC: write(2, "enospc\n", sizeof("enospc\n"));
      return (1);
    case EPIPE: write(2, "epipe\n", sizeof("epipe\n"));
      return (1);
    }
  return 0;
}
int main()
{
  size_t count = 128;
  char c[128];
  char buffer[128];
  ssize_t i;
  int j = 0, k = 0, nb_chars = 0;
  
  while((i = read(0, c, count)) > 0){
    if(c[0] == 'e' && c[1] == 'x' && c[2] == 'i' && c[3] == 't'){
      return 0;
    }
    nb_chars += i;
    
    for(j = 0; j < 256; j++){
      buffer[j] = 0;
    }
    
    buffer[0] = (k == 1 && c[0] == '*') ? '^' : c[0];
    for(j = 0; k < i; k++, j++){
      if((k < i-1) && (c[k] == c[k+1] && c[k] == '*')){
	buffer[j] = '^';
      } else if(c[k] == '^'){
	buffer[j++] = '*';
	buffer[j] = '*';
      } else {
	buffer[j] = c[k];
      }
    }
    k = (c[9] == '*') ? 1 : 0;
    
    if(nb_chars > 80){
      write(1, "\n", 1);
      nb_chars = 0;
    }
    write(1, buffer, j);
    for(j = 0; j < 256; j++){
      c[j] = 0;
    }
  }
  return 0;
}
