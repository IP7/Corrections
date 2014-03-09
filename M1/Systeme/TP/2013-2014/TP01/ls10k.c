/**
 * 000           d000    .d0000b.  000
 * 000          d0000   d00P  Y00b 000
 * 000            000   000    000 000
 * 000 .d0000b    000   000    000 000  000
 * 000 00K        000   000    000 000 .00P
 * 000 "Y0000b.   000   000    000 000000K
 * 000      X00   000   Y00b  d00P 000 "00b
 * 000  00000P' 0000000  "Y0000P"  000  000
 *
 * This file implements the code for exercices 2.2 and 2.3 of the first TP.
 *
 * Compile it with
 *  gcc -Wall -Wextra -std=c89 -pedantic ls10k.c -o ls10k
 *
 * Usage:
 *  ./ls10k [-r] <dirname>
 *
 * Known issues:
 *  - Doesn't work with large paths (more than ~1024 chars). A workaround
 *    might be to chdir before opendir/stat, but it hasn't been tested here.
 *  - When a symbolic link is encountered, the file it points to is used
 *    instead of the link itself. This is especially annoying when a symbolic
 *    link is used to make a recursive path. Due to the previous known issue,
 *    a recursive path won't stop the program nor fill all the available
 *    memory since it'll stop when the path become too large. Unfortunately,
 *    lstat is not part of the C89 standard.
 *
 * Author: Baptiste Fontaine - b@ptistefontaine.fr - student no <redacted>
 **/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/dir.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>

#ifndef _LS10K_C
#define _LS10K_C 1

/* Disable non-standard stat features on OSX >= 10.5 */
#undef _DARWIN_FEATURE_64_BIT_INODE

/* Error codes */
#define NULL_POINTER 1
#define IO_ERROR     2
#define MEMORY_ERROR 4
#define ARGS_ERROR   8
#define PATH_ERROR  16

#define NFREE(X) free(X); (X) = NULL;

void print_last_error(const char *prefix) {
    fprintf(stderr, "Error %d: %s - %s\n", errno, prefix, strerror(errno));
}

/**
 * Test if a file size is higher or equal to 10kb. If so, it prints
 * it path.
 * - fpath is the path to the file
 *
 * The function returns the status of the operation. 0 means that
 * everything is ok, another number means an error occured.
 **/
int
print_if_is_10k(const char *fpath) {
    int err = 0;
    struct stat *buf = NULL;

    if (fpath == NULL) {
        return NULL_POINTER;
    }

    buf = (struct stat*)malloc(sizeof(struct stat));

    if (buf == NULL) {
        print_last_error(fpath);
        return MEMORY_ERROR;
    }

    err = stat(fpath, buf);

    if ((err == 0) && (buf->st_size >= 10240)) {
        printf("%s\n", fpath);
    }

    NFREE(buf);

    return err;
}

/**
 * Prints files which size is higher or equal to 10kb in a directory.
 * - dpath is the path to the directory
 * - recursive determines if the function should recursively list files in
 *   subdirectories
 *
 * The function returns a status code, 0 means everything is ok,
 * another number means an error occured. Errors in subdirectories are
 * ignored, but some of these directories may be skipped.
 **/
int
ls10k(char *dpath, short recursive) {

    struct dirent *entry = NULL;
    struct stat *statbuf = NULL;
    DIR  *rep = NULL;
    char *fpath = NULL;

    int err      = 0,
        dpathlen = 0,
        is_dir   = 0;

    if (dpath == NULL) {
        return NULL_POINTER;
    }

    rep = opendir(dpath);

    if (rep == NULL) {
        print_last_error(dpath);
        return IO_ERROR; /* This could be a MEMORY_ERROR too */
    }

    /* 256 for the filename, strlen(dpath) for the dir path, 2 for the '/'
       and '\0' */
    fpath = (char*)malloc(sizeof(char)*(256+strlen(dpath)+2));

    if (fpath == NULL) {
        print_last_error(dpath);
        closedir(rep);
        return MEMORY_ERROR;
    }

    strcpy(fpath, dpath);
    dpathlen = strlen(dpath);

    if (fpath[dpathlen-1] != '/') {
        /* Avoid things like "foo//bar" */
        fpath[dpathlen++] = '/';
    }

    statbuf = (struct stat*)malloc(sizeof(struct stat));

    if (statbuf == NULL) {
        print_last_error(fpath);
        NFREE(fpath);
        return MEMORY_ERROR;
    }

    while ((entry = readdir(rep)) != NULL) {
        if (   (strcmp(entry->d_name, ".") == 0)
            || (strcmp(entry->d_name, "..") == 0)) {
            continue;
        }

        strcpy(fpath+sizeof(char)*dpathlen, entry->d_name);

        if (stat(fpath, statbuf) != 0) {
            print_last_error(fpath);
            err |= IO_ERROR;
            if (errno == ELOOP) {
                break;
            }
            continue;
        }

        if (S_ISREG(statbuf->st_mode)) {
            err |= print_if_is_10k(fpath);
        }

        if (recursive) {

            /* We use a variable here to free memory *before* the
               recursive call. */
            is_dir = (S_ISDIR(statbuf->st_mode));

            if (is_dir) {
                is_dir = 0;
                ls10k(fpath, 1);
            }
        }
    };

    if (closedir(rep) != 0) {
        print_last_error(dpath);
    }

    NFREE(statbuf);
    NFREE(fpath);
    return err;
}

/**
 * Return an absolute path from a relative one. If the given path
 * is already absolute or is empty, or if there was a memory allocation
 * error, the function returns NULL.
 * The returned path is not garanteed to be free of "." or "..", e.g.:
 *      ../foo -> /path/to/cwd/../foo
 **/
char *
absolute_path(const char *path, int *status) {
    char *pwd     = NULL,
         *abspath = NULL;
    int pwdlen  = 0,
        abslen  = 0,
        rel_len = strlen(path),
        /* number of chars to strip from the relative path before
           concatenation. This is used to strip things like "." or "./". */
        strip   = 0;

    /* We assume that absolute paths start with '/'. This won't
       work on MS Windows. */
    if ((path == NULL) || (rel_len == 0) || (path[0] == '/')) {
        return NULL;
    }

    pwd = getcwd(NULL, 0);

    if (pwd == NULL) {
        print_last_error("(pwd)");
        *status = MEMORY_ERROR;
        return NULL;
    }

    if (path[0] == '.') {
        if (rel_len == 1) {
            strip = 1;
        } else if (path[1] == '/') {
            strip = 2;
        }
    }

    pwdlen = strlen(pwd);
    abslen = pwdlen + 2 + rel_len - strip;

    abspath = realloc(pwd, sizeof(char)*abslen);

    if (abspath == NULL) {
        print_last_error(pwd);
        *status = MEMORY_ERROR;
        NFREE(pwd);
        return NULL;
    }

    abspath[pwdlen] = '/';
    strcpy(abspath+(sizeof(char)*(pwdlen+1)), path+(sizeof(char)*strip));

    *status = 0;
    return abspath;
}

/**
 * Print basic usage and exit.
 **/
int print_usage_and_exit(char **argv) {
    printf("Usage:\n\t%s [-r] <dirname>\n\n", argv[0]);
    return ARGS_ERROR;
}

int main(int argc, char **argv) {
    int recursive = 0,
        is_abs    = 0,
        status    = 0;
    char *abspath = NULL;

    if ((argc != 2) && (argc != 3)) {
        return print_usage_and_exit(argv);
    }

    if (argc == 3) {
        if (strcmp(argv[1], "-r") != 0) {
            return print_usage_and_exit(argv);
        }
        recursive = 1;
    }

    abspath = absolute_path(argv[1 + recursive], &status);

    if (status != 0) {
        if (abspath != NULL) {
            NFREE(abspath);
        }
        return status;
    }

    if (abspath == NULL) {
        is_abs = 1;
        abspath = argv[1 + recursive];
    }

    status = ls10k(abspath, recursive);

    if (!is_abs) {
        NFREE(abspath);
    }
    return status;
}

#endif /* _LS10K_C */
