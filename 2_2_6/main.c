#include <stdio.h>
#include <math.h>

#include "main.h"

#define MAX_FACT 20

void clear(void) {
	while (getchar() != '\n');
}

float degToRad(float deg) {
  return deg / 180.0 * 3.14;
}

long fact(long a) {
  if (a == 0 || a == 1) { return a; }
  
  return fact(a - 1) * a;
}

double sinMaclaurin(double angleRad, int n) {
  int i;
  double value = 0.0;
  
  for (i = 1; i <= n; i++) {
    value += pow(-1.0, i - 1) * pow(angleRad, 2 * i - 1) / fact(2 * i - 1);
  }
  
  return value;
}

#ifndef TESTING

int main(void) {
  double degrees;
  double error;
  double normalSin, sinMacl;
  int i;
  
  printf("Enter the angle in degrees: ");
  
  while (!scanf("%lf", &degrees)) {
    clear();
    printf("Incorrect input. Please try again: ");
  }
  
  printf("Enter the allowable error (has to be less than 1: ");
  
  while (!scanf("%lf", &error) && error >= 1.0) {
    clear();
    printf("Incorrect input. Please try again: ");
  }
  
  normalSin = sin(degToRad(degrees));
  
  for (i = 1; i <= MAX_FACT; i++) {
    sinMacl = sinMaclaurin(degToRad(degrees), i);
    
    if (fabs(sinMacl - normalSin) < error) {
      printf("Sine calculated by the normal function: %f\n", normalSin);
      printf("Sine calculated with the help of series expansion to %d: %f\n", i, sinMacl);
      return 0;
    }
  }
  
  fprintf(stderr, "Cannot calculate sinus: too big number for series expansion\n");
  return 1;
}

#endif
