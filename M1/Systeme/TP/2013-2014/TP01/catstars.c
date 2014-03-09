#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#define BUFFSIZE 64

int main(void) {

        char buffin[BUFFSIZE],
             buffout[BUFFSIZE*2];

        ssize_t got = 0,
                give = 0;

        int i = 0,
            j = 0;

        got = read(0, buffin, BUFFSIZE);

        while (got > 0) {
                give = got;

                for (i=0, j=0; i<got; i++, j++) {
                        if (buffin[i] == '^') {
                                buffout[j++] = '*';
                                buffout[j] = '*';
                                give++;
                                continue;
                        }
                        buffout[j] = buffin[i];
                }

                write(1, buffout, give);

                got = read(0, buffin, BUFFSIZE);
        }

        if (got < 0) {
                perror("read");
                return 1;
        }

        return 0;
}

