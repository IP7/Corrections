#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int print_usage(char *cmd) {
        printf("Usage:\n\t%s [do] <command>\n", cmd);
        return 1;
}

int main(int argc, char **argv) {
        char *cmd;
        int firstarg = 1,
            child,
            status;

        if (argc == 1) {
                return print_usage(argv[0]);
        }

        if (strcmp(argv[1], "do") == 0) {
                firstarg++;
        }
        if (argc < firstarg+1) {
                return print_usage(argv[0]);
        }

        cmd = argv[firstarg];

        child = fork();
        if (child < 0) {
                perror("fork");
                return -1;
        }

        if (child == 0) {
                execvp(cmd, argv+(firstarg*sizeof(char)));
                perror("execl");
                return 1;
        } else {
                if (wait(&status) == -1) {
                        perror("wait");
                        return -1;
                }
                if (WIFSIGNALED(status)) {
                        printf("Killed by signal %d\n", WTERMSIG(status));
                } else if (WIFEXITED(status)) {
                        printf("Normal terminaison with result %d\n",
                                        WEXITSTATUS(status));
                } else {
                        puts("Weird :/");
                }
        }

        return 0;
}

