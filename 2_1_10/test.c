#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <float.h>

#include "main.h"

void getABCTest(void) {
  assert(getABC() == 'c');
}

void getEuroCostTest(void) {
  assert(getEuroCost() - 40000.0 < DBL_EPSILON);
}

void getYearTest(void) {
  assert(getYear() == 2007);
}

void getEngineVolumeTest(void) {
  assert(getEngineVolume() - 6.0 < DBL_EPSILON);
}

void getTransportingDistanceTest(void) {
  assert(getTransportingDistance() - 6000.0 < DBL_EPSILON);
}

void calculateTranportingCostTest(void) {
  assert(calculateTranportingCost(500.0) - 250.0 < DBL_EPSILON);
  assert(calculateTranportingCost(600.0) - 300.0 < DBL_EPSILON);
}

void calculateCustomsClearanceTest(void) {
  assert(calculateCustomsClearance(2.0, 2019) - 1200.0 < DBL_EPSILON);
  assert(calculateCustomsClearance(3.0, 2012) - 1800.0 < DBL_EPSILON);
  assert(calculateCustomsClearance(2.0, 2008) - 1200.0 < DBL_EPSILON);
  assert(calculateCustomsClearance(5.0, 2000) - 10000.0 < DBL_EPSILON);
}

void calculateVehicleCostBYNTest(void) {
  assert((int)calculateVehicleCostBYN(10000.0) == 27298);
}

int main(void) {
  getABCTest();
  getEuroCostTest();
  getEngineVolumeTest();
  getTransportingDistanceTest();
  calculateTranportingCostTest();
  calculateCustomsClearanceTest();
  calculateVehicleCostBYNTest();
  
  printf("\n\n\n\n\n\n\nTests passed successfully!\n");
  
  return 0;
}
