#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {

        int child   = fork(),
            *status = NULL;

        if (child == -1) {
                perror("fork");
                return -1;
        }

        if (child == 0) {
                /* child processus */
                write(1, "Je suis le fils\n", 16);
        } else {
                /* father processus */
                write(1, "Je suis le père\n", 16);
                if (waitpid(child, status, 0) == -1) {
                        perror("waitpid");
                        return -1;
                }
        }

        return 0;
}
