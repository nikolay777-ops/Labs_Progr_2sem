#ifndef MAIN_H
#define MAIN_H

void clear(void);
void printIntroduction(void);
char getABC(void);
double getEuroCost(void);
int getYear(void);
double getEngineVolume(void);
double getTransportingDistance(void);
double calculateTranportingCost(double dist);
double calculateCustomsClearance(double volume, int year);
double calculateVehicleCostBYN(double euro);

#endif
