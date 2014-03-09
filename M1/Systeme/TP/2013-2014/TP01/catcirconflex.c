#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#define BUFFSIZE 64

int main(void) {

        char buffin[BUFFSIZE],
             buffout[BUFFSIZE];

        ssize_t got = 0,
                give = 0;

        int i = 0,
            j = 0;

        got = read(0, buffin, BUFFSIZE);

        while (got > 0) {
                give = got;

                for (i=0, j=0; i<got; i++, j++) {
                        if (i < got - 1 && buffin[i] == '*'
                                        && buffin[i+1] == '*') {
                                buffout[j] = '^';
                                i++;
                                give--;
                                continue;
                        }
                        buffout[j] = buffin[i];
                }

                got = read(0, buffin, BUFFSIZE);

                if (got > 0 && buffout[give-1] == '*' && buffin[0] == '*') {
                        give--;
                        buffin[0] = '^';
                }

                write(1, buffout, give);
        }

        if (got < 0) {
                perror("read");
                return 1;
        }

        return 0;
}

