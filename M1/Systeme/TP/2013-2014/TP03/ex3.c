#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int print_usage(char *cmd) {
        printf("Usage:\n\t%s <test> <command> [<command>]\n", cmd);
        return 1;
}

int main(int argc, char **argv) {
        char *test;
        int child,
            status;

        if (argc < 3) {
                return print_usage(argv[0]);
        }

        test = argv[1];

        child = fork();
        if (child < 0) {
                perror("fork");
                return -1;
        }

        if (child == 0) {
                execlp(test, test, (char*)NULL);
                return 1;
        } else {
                if (wait(&status) == -1) {
                        perror("wait");
                        return -1;
                }
                if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
                        execlp(argv[2], argv[2], (char*)NULL);
                        perror("execlp[1]");
                } else {
                        if (argc > 3) {
                                execlp(argv[3], argv[3], (char*)NULL);
                                perror("execlp[2]");
                        }
                }
        }

        return 0;
}


