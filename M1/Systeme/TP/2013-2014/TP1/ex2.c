#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>


#define PRINT_ERROR(error_name, error_msg)				\
  fprintf(stderr, "Error \e[0;31m%s\e[m:\n\e[0;33m%s\n\e[m", error_name, error_msg)

#define DIR_2POINT(str)(str[0] == '.' && str[1] == '.' && str[2] == '\0') 
#define DIR_POINT(str)(str[0] == '.' && str[1] == '\0') 
#define DIR_BASE(str)DIR_2POINT(str) || DIR_POINT(str) 
typedef int file;
void error();
void parcour_directory(char *directory_name);
void suppression(char *filename);
void take_file(char *filename);


void error(){
  switch(errno){
  case EACCES: 
    PRINT_ERROR("EACCES", "Search permission is denied for one of the directories in the\npath prefix of path.");
    return;
  case EBADF:  
    PRINT_ERROR("EBADF", "descriptor is bad.");
    return;
  case EBUSY:
    PRINT_ERROR("EBUSY", "The file named by the path argument cannot be unlinked because it is being used by the system or another process and the implementation considers this an error.");
    return;
  case EFAULT: 
    PRINT_ERROR("EFAULT", "Bad address.");
    return;
  case ELOOP: 
    PRINT_ERROR("ELOOP", "Too many symbolic links encountered while traversing the path.");
    return;
  case ENAMETOOLONG: 
    PRINT_ERROR ("ENAMETOOLON", "path is too long.");
    return;
  case ENOENT: 
    PRINT_ERROR("ENOENT", "A component of path does not exist, or path is an empty\nstring.");
    return;
  case ENOMEM:
    PRINT_ERROR("ENOMEM", "Out of memory (i.e., kernel memory.");
    return;
  case ENOTDIR: 
    PRINT_ERROR("ENOTDIR", "A component of the path prefix of path is not a directory.");
    return;
  case EPERM: 
    PRINT_ERROR("EPERM", "The file named by path is a directory, and either the calling process does not have appropriate privileges, or the implementation prohibits using unlink() on directories.");
    return;
  case EROFS:
    PRINT_ERROR("EROFS", "The directory entry to be unlinked is part of a read-only file system.");
    return;
  case ETXTBSY:
    PRINT_ERROR("ETXTBSY", "The entry to be unlinked is the last directory entry to a pure procedure (shared text) file that is being executed.");
  case EOVERFLOW: 
    PRINT_ERROR("EOVERFLOW", "path or fd refers to a file whose size, inode number, or\nnumber of blocks cannot be represented in, respectively, the\ntypes off_t, ino_t, or blkcnt_t.  This error can occur when,\nfor example, an application compiled on a 32-bit platform\nwithout -D_FILE_OFFSET_BITS=64 calls stat() on a file whose\nsize exceeds (1<<31)-1 bytes.");
    return;
  }
}
void parcour_directory(char *directory_name){
  DIR *dir= opendir(directory_name);
  struct dirent *d;
  char path[1024];
  
  errno = 0;
  while((d = readdir(dir)) != NULL)
    {
      if(DIR_BASE(d->d_name))
	{
	  continue;
	}
      snprintf(path, sizeof(path),"%s/%s", directory_name, d->d_name);
      take_file(path);
    }
  closedir(dir);
}
void suppression(char *filename){
  char c = ' ';
  while((c = getchar()) != '\0')
    {
      if(c == 'y' || c == 'Y')
	{
	  if(unlink(filename) == -1)
	    {
	      error();
	    }
	  break;
	}
      else if(c == 'n' || c == 'N')
	{
	  break;
	}
    }
}
void take_file(char *filename){
  struct stat buf;
  int len = 0;
  if(-1 == stat(filename, &buf)){
    error();
  }
  if(S_ISDIR(buf.st_mode))
    {
      parcour_directory(filename);
    }
  else if((len = (int)buf.st_size) > 10240)
    {
      printf("%s: size of file = %d, remove file(Y/n)?", filename, len);
      suppression(filename);
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
