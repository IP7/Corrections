#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define LEN 10000

int main(int argc, char **argv) {

        int t[LEN],
            i, j, len,
            parts,
            part_len,

            father = 1,
            child;

        srandom(getpid());

        for (i=0; i<LEN; i++) {
                t[i] = random() % 1000;
        }

        if (argc > 1) {
                parts = atoi(argv[1]);
        } else {
                parts = 2;
        }

        part_len = LEN / parts;

        for (i=0; i<parts; i++) {
                if (!father) { continue; }

                child = fork();

                if (child == -1) {
                        perror("fork");
                        return -1;
                }

                father = (child != 0);

                if (father) { continue; }

                len = (i + 1) * part_len;
                if (len > LEN - 1) {
                        len = LEN - 1;
                }

                for (j=i*part_len; j<len; j++) {
                        if (t[j] == 42) {
                                printf("I'm the child #%d and I found 42 "
                                       "in t[%d]\n", getpid(), j);
                        }
                }
        }

        if (father) {
                for (i=0; i<parts; i++) {
                        if (wait(NULL) == -1) {
                                perror("wait");
                        }
                }
        }

        return 0;
}
