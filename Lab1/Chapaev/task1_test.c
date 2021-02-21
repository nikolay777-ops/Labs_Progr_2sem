#include "task1.h"

#include <stdio.h>
#include <math.h>
#include <assert.h>

void testCalculateAngle() {
	float alpha1;
	alpha1 = calculateAngle(5, 5);
	
	assert(alpha1 == 0);
}

void testCalculateTime() {
	float alpha = 30.0 / 180.0 * 3.14;
	float v1 = 5;
	float time;
	
	time = calculateTime(v1, alpha, 500);
	
	assert((int)time == 200);
}

int main() {
	testCalculateAngle();
	testCalculateTime();
	
	printf("Tests passed successfully\n");
	
	return 0;
}
