#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "task1.h"

void clear() {
	while (getchar() != '\n');
}

#ifndef TESTING

int main() {
	float v1, v2;
	float b;
	float alpha;
	float time;
	float alpha1, alpha2;
	float time1, time2;
	bool hurt = false;
	float v1AfterHurt = 0.0f;
	char h;
	
	printf("Enter Chapaev's speed in still water and the speed of the river ");
	printf("(in m/s, from 0 to 5, Chapaev's speed should be larger than the river speed): ");
	
	while (!scanf("%f %f", &v1, &v2) || v1 <= 0.0f || v1 > 5.0f || v2 > v1 || v2 < 0.0f) {
		clear();
		printf("Incorrect input. Please try again\n");
	}
	
	printf("Enter the river width (in m, from 10 to 2000): ");
	
	while (!scanf("%f", &b) || b < 10.0f || b > 2000.0f) {
		clear();
		printf("Incorrect input. Please try again\n");
	}
	
	printf("Did Chapaev get physically injured in the middle of the river? (y/n): ");
	(void)getchar();
	
	while(!(h = (char)getchar()) || (h != 'y' && h != 'n')) {
		clear();
		printf("Incorrect input. Please try again\n");
	}
	
	hurt = h == 'y';
	
	if (hurt) {
		printf("Enter Chapaev's speed after the injury (in m/s, has to be less than the initial speed and more than the speed of the river) ");
		
		while (!scanf("%f", &v1AfterHurt) || v1AfterHurt < 0.0f || v1AfterHurt > v1 || v1AfterHurt < v2) {
			clear();
			printf("Incorrect input. Please try again\n");
		}
	}
	
	if (!hurt) {
		alpha = calculateAngle(v1, v2);
		time = calculateTime(v1, alpha, b);
		printf("Chapaev should swim at an angle of %f degrees\n", alpha / 3.14 * 180.0);
		printf("Chapaev will swim across Ural in %f seconds\n", time);
	} 
	else {
		alpha1 = calculateAngle(v1, v2);
		alpha2 = calculateAngle(v1AfterHurt, v2);
		time1 = calculateTime(v1, alpha1, b / 2);
		time2 = calculateTime(v1AfterHurt, alpha2, b / 2);
		
		printf("First, Chapaev should swim at an angle of %f degrees, but after the injury - %f degrees\n", alpha1 / 3.14 * 180.0, alpha2 / 3.14 * 180.0);
		printf("Chapaev will swim across Ural in %f seconds\n", time1 + time2);
	}
	
	return 0;
}

#endif


float calculateAngle(float v1, float v2) {
	float alpha;
	
	alpha = (float)acos(v2 / v1);
	
	return alpha;
}

float calculateTime(float v1, float alpha, float b) {
	float v1_y = (float)sin(alpha) * v1;
	
	return b / v1_y;
}

