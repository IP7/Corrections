#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#undef _DARWIN_FEATURE_64_BIT_INODE
#define TEN_K 10240

int main(int argc, char **argv) {

        int f;
        struct stat *buf;

        if (argc != 2) {
                printf("Usage:\n\t%s <filename>\n\n", argv[0]);
                return 1;
        }

        f = open(argv[1], O_RDONLY);

        buf = (struct stat*)malloc(sizeof(struct stat));

        if (fstat(f, buf) != 0) {
                perror("fstat");
                return 1;
        }

        if (close(f) != 0) {
                perror("close");
                return 1;
        }

        if (buf->st_size >= TEN_K) {
                printf("%s\n", argv[1]);
        }

        return 0;
}
