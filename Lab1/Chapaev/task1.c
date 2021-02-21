#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "task1.h"

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
	
	printf("Введите скорость Чапаева в стоячей воде и скорость реки (в м/с, от 0 до 5, скорость Чапаева должна быть больше): ");
	
	while (!scanf("%f %f", &v1, &v2) || v1 <= 0.0f || v1 > 5.0f || v2 > v1 || v2 < 0.0f) {
		printf("Incorrect input. Please try again\n");
	}
	
	printf("Введите ширину реки (в м, от 10 до 2000): ");
	
	while (!scanf("%f", &b) || b < 10.0f || b > 2000.0f) {
		printf("Incorrect input. Please try again\n");
	}
	
	printf("Хотите ли вы ранить Чапаева в руку в середине реки? (y/n): ");
	(void)getchar();
	
	while(!(h = (char)getchar()) || (h != 'y' && h != 'n')) {
		printf("Incorrect input. Please try again\n");
	}
	
	hurt = h == 'y';
	
	if (hurt) {
		printf("Какая оказалась скорость Чапаева после ранения? (в м/с, должна быть меньше изначальной) ");
		
		while (!scanf("%f", &v1AfterHurt) || v1AfterHurt < 0.0f || v1AfterHurt > v1) {
			printf("Incorrect input. Please try again\n");
		}
	}
	
	if (!hurt) {
		alpha = calculateAngle(v1, v2);
		time = calculateTime(v1, alpha, b);
		printf("Чапаев должен плыть под углом %f градусов\n", alpha / 3.14 * 180.0);
		printf("Чапаев переплывёт Урал через %f секунд\n", time);
	} 
	else {
		alpha1 = calculateAngle(v1, v2);
		alpha2 = calculateAngle(v1AfterHurt, v2);
		time1 = calculateTime(v1, alpha1, b / 2);
		time2 = calculateTime(v1AfterHurt, alpha2, b / 2);
		
		printf("Чапаев должен плыть сначала под углом %f градусов, а после ранения %f градусов\n", alpha1 / 3.14 * 180.0, alpha2 / 3.14 * 180.0);
		printf("Чапаев переплывёт Урал через %f секунд\n", time1 + time2);
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

