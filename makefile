CC = gcc
CFLAGS = -Wall -std=c99 -ggdb
LDLIBS = -lm

crossword_solver.exe:	main.c solve.c format.c crossword.h
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
