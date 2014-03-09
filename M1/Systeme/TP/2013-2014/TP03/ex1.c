#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
        int child;

        child = fork();
        if (child == -1) {
                perror("fork");
                return -1;
        }

        if (child == 0) {
                execl("/bin/ls", "ls", "-l", (char*)NULL);
                perror("execl");

        } else {
                if (wait(NULL) == -1) {
                        perror("wait");
                }
        }

        return 0;
}
