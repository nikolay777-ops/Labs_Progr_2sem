#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <float.h>

#include "main.h"

void testDegToRad(void) {
  assert(fabs(degToRad(0.0)) < DBL_EPSILON);
  assert(fabs(degToRad(150.0) - 2.61666667) < 0.000001);
}

void testFact(void) {
  assert(fact(3) == 6);
  assert(fact(4) == 24);
  assert(fact(5) == 120);
}

void testSinMaclaurin(void) {
  double x = 30.0;
  
  double sn1 = x - (x*x*x / 6) + (x*x*x*x*x / 120);
  double sn2 = sinMaclaurin(x, 3);
  assert(fabs(fabs(sn1) - fabs(sn2)) < 0.000001);
}

int main(void) {
  testDegToRad();
  testFact();
  testSinMaclaurin();
    
  puts("Tests passed successfully");
  
  return 0;
}
