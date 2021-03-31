main: main.o
	gcc -o main main.o

main.o: main.c main.h
	gcc -c -o main.o main.c -pedantic -ansi -Wall
	
test: test.c main.c
	gcc -o test test.c main.c -ansi -Wall -Dmain=kdofkdsofko
