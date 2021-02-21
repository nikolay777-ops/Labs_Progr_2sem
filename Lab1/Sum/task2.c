#include <stdio.h>

#include "task2.h"

#ifndef TESTING

int main() {
	int n;
	double f, prod;
	
	printf("Enter a natural n and a float f: ");
	
	while (!scanf("%d %lf", &n, &f) || n <= 0) {
		printf("Incorrect input. Please try again");
	}
	
	prod = calculateExpression((unsigned int)n, f);
	printf("The result: %f\n", prod);
	
	return 0;
}

#endif

double calculateSum(unsigned int i, double f) {
	double sum = 0.0;
	unsigned int k;
	
	for (k = 0; k <= i; k++) {
		sum += (k + f);	
	}
	
	return sum;
}

double calculateExpression(unsigned int n, double f) {
	unsigned int i;
	double prod = 1.0;
	
	for (i = 1; i <= n; i++) {
		double denominator = calculateSum(i, f);
		
		/*
		 * floating point representations are inexact, so we're using comparison to DBL_EPSILON here
		 * */
		if (denominator - 0.0 < DBL_EPSILON) {
			fprintf(stderr, "The expression cannot be calculated properly: division by zero\n");
			denominator = 0.000000001;
		}
		
		prod *= (1.0 / denominator);
	}
	
	return prod;
}
