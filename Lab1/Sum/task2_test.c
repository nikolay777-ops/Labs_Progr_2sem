#include "task2.h"

#include <stdio.h>
#include <assert.h>

void testCalculateExpression() {
	double result;
	int r;
	
	result = calculateExpression(2, 2.5);
	r = (int)(result * 100000);
	assert(r == 1587);
}

int main() {
	testCalculateExpression();
	printf("Tests passed successfully\n");
	
	return 0;
}

