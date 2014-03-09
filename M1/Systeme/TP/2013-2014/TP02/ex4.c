#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/* 8 processus */
int main(void) {

        fork();
        fork();
        fork();
        sleep(10);
        exit(0);

        return 0;
}
