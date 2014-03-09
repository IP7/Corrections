OPT=-g -Wall -Wextra -std=gnu99 -pedantic
CC=gcc $(OPT)

.PHONY: clean cleanall

TARGETS=\
		ex1 \
		ex2 \
		ex3 \
		ex4 \
		ex5

default: all
all: clean $(TARGETS)

clean:
	rm -f *~ *.o

cleanall: clean
	rm -rf $(TARGETS) a.out *.dSYM

%: %.c
	$(CC) $< -o $@
