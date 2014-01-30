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
