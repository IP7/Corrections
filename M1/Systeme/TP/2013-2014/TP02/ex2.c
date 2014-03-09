#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {

        int child   = fork(),
            i       = 0,
            *status = NULL;

        if (child == -1) {
                perror("fork");
                return -1;
        }

        if (child == 0) {
                /* child processus */
                for (; i<10000; i++) {
                        write(1, "b\n", 2);
                }

        } else {
                /* father processus */
                for (; i<10000; i++) {
                        write(1, "a\n", 2);
                }

                if (waitpid(child, status, 0) == -1) {
                        perror("waitpid");
                        return -1;
                }
        }

        return 0;
}
