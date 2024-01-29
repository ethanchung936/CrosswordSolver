# CrosswordSolver
This is a program that takes a crossword template and a set of words and returns a file containing solutions to the template based on the given words.
This is achieved by using a recursive backtracking algorithm. Created for CMPUT 201 Fall 2022

This is a C program and can be run on Linux or on Windows using MinGW.

On Linux simply run the make command to compile:
```
make
```

For Windows use: 
```
gcc -std=c99 main.c solve.c format.c crossword.h -o crossword_solver
```

Before running the program ensure that you have a text file containing a list of words and a text file containing a crossword template.
The first line of the crossword template must be the square dimension of the template, the rest must contain 0 for a blank square,
a letter for a square filled with that letter, or * for a blocked square. These characters must be seperated by spaces like below.
```
6
a 0 0 0 0 *
0 * 0 * * *
0 0 0 0 0 *
0 * * * 0 *
0 * 0 0 0 0
0 * * * 0 *
```


Then, to run the program do:
```
./crossword_solver.exe dictionary.txt crossword.txt 10 15
```
- dictionary.txt can be replaced by any text file containing a list of words.
- crossword.txt can be replaced by any text file with a crossword template.
- The first number is the maximum number of solutions to be output.
- The second number is the number of words from the word list that are to be used in finding solutions.

Example files have been included for ease of use.
