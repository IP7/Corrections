OPT=-g -Wall -Wextra -std=c89 -pedantic
CC=gcc $(OPT)

.PHONY: clean cleanall

TARGETS=\
	catcirconflex \
	catncirconflex \
	catstars \
	is10k \
	ls10k

default: all
all: clean $(TARGETS)

clean:
	rm -f *~ *.o

cleanall: clean
	rm -rf $(TARGETS) a.out *.dSYM

%: %.c
	$(CC) $< -o $@
