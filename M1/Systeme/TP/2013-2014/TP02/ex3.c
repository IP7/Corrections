#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {

        int pid = 1,
            i   = 0;

        do {
                pid = fork();

                if (pid == -1) {
                        perror("fork");
                        return -1;
                }

                if (pid == 0) {
                        printf("I'm a child and my pid is %d.\n", getpid());
                }
        } while (pid != 0 && ++i < 13);

        if (pid != 0) {
                for (i = 0; i<13; i++) {
                        if (wait(NULL) == -1) {
                                perror("wait");
                                return -1;
                        }
                }
        }

        return 0;
}
