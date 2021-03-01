main: main.c main.h
	gcc -o main main.c -ansi -pedantic

test: main.c main.h test.c
	gcc -o test test.c main.c -ansi -pedantic -D TESTING -lm
