task1: task1.c
	gcc -pedantic -ansi -o task1 task1.c -lm
	
test: task1.c task1_test.c
	gcc -pedantic -ansi -o test task1.c task1_test.c -D TESTING -lm
