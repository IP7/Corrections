#ifndef EX2_H
#define EX2_H
#define DIR_BASE(str) (!strcmp("..", str) || !strcmp(".", str))
void parcourir_rep(char *directory_name);
void confirme_suppr(char *filename);
void take_file(char *filename);
#endif
