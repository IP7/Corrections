OPT=-g -Wall -Wextra -std=gnu99 -pedantic
CC=gcc $(OPT)

.PHONY: clean cleanall

TARGETS=\
		ex1 \
		please \
		please5 \
		si

DEFAULT: all

please: ex2
	mv $< $@

si: ex3
	mv $< $@

please5: ex2-3
	mv $< $@

all: clean $(TARGETS)

clean:
	rm -f *~ *.o

cleanall: clean
	rm -rf $(TARGETS) ex2 ex3 ex2-3 a.out *.dSYM

%: %.c
	$(CC) $< -o $@
