#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#define BUFFSIZE 64

int main(void) {

        char buffin[BUFFSIZE],
             /* The +1 is here to handle the case where there are no
                replacements in the current buffer (i.e. the output is of
                the same size than the input), but we have to insert a newline
                char. */
             buffout[BUFFSIZE+1];

        ssize_t got = 0,
                give = 0;

        int i = 0,
            j = 0,
            lastnewline = 0;

        got = read(0, buffin, BUFFSIZE);

        while (got > 0) {
                give = got;

                for (i=0, j=0; i<got; i++, j++) {
                        buffout[j] = buffin[i];

                        if (buffin[i] == '\n') {
                                lastnewline = 0;
                                continue;
                        }

                        if (i < got - 1 && buffin[i] == '*'
                                        && buffin[i+1] == '*') {
                                buffout[j] = '^';
                                i++;
                                give--;
                        }

                        lastnewline++;

                        if (lastnewline >= 79) {
                                j++;
                                give++;
                                buffout[j] = '\n';
                                lastnewline = 0;
                        }
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

