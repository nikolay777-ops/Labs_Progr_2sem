#include <stdio.h>
#include <stdbool.h>

#include "main.h"

#define CURRENT_YEAR 2021
#define EUR_TO_BYN_RATE 2.7298

void clear(void) {
	while (getchar() != '\n');
}

void printIntroduction(void) {
  printf("Welcome to the Gross Transport Inc. helper.\n");
  printf("Version: 1.16.1.\n");
  printf("Production: Gross Transport Inc. data science team.\n\n\n");
}

char getABC(void) {
  char c;

  while (!scanf("%c", &c) || (c != 'a' && c != 'b' && c != 'c')) {
		clear();
		printf("Incorrect input. Please try again: ");
	}

  clear();
  return c;
}

double getEuroCost(void) {
  double cost;

  printf("Enter the cost of the vehicle in the European Union (from 100€ to 100000€): ");

  while (!scanf("%lf", &cost) || cost < 100.0 || cost > 100000.0) {
    clear();
    printf("Incorrect input. Please try again: ");
  }

  clear();
  return cost;
}

int getYear(void) {
  int year;

  printf("Enter the vehicle manufacture year: (from 1950 to 2021): ");

  while (!scanf("%d", &year) || year < 1950 || year > 2021) {
    clear();
    printf("Incorrect input. Please try again: ");
  }

  clear();
  return year;
}

double getEngineVolume(void) {
  double volume;

  printf("Enter the vehicle engine volume in liters: (from 1 to 20): ");

  while (!scanf("%lf", &volume) || volume < 1.0 || volume > 20.0) {
    clear();
    printf("Incorrect input. Please try again: ");
  }

  clear();
  return volume;
}

double getTransportingDistance(void) {
  double dist;

  printf("Enter the transporting distance in km: (from 0 to 10000): ");

  while (!scanf("%lf", &dist) || dist < 0.0 || dist > 10000.0) {
    clear();
    printf("Incorrect input. Please try again: ");
  }

  clear();
  return dist;
}

double calculateTranportingCost(double dist) {
  return dist * 0.5;
}

double calculateCustomsClearance(double volume, int year) {
  double clearance = 0.0;
  int age = CURRENT_YEAR - year;

  if (age <= 3) {
    clearance = volume * 1000.0 * 0.6;
  }
  else if (age > 3 && age <= 10) {
    if (volume * 1000.0 < 2500.0) {
      clearance = volume * 1000.0 * 0.35;
    }
    else {
      clearance = volume * 1000.0 * 0.6;
    }
  }
  else if (age > 10 && age <= 14) {
    clearance = volume * 1000.0 * 0.6;
  }
  else {
    clearance = volume * 1000.0 * 2.0;
  }

  return clearance;
}

double calculateVehicleCostBYN(double euro) {
  return euro * EUR_TO_BYN_RATE;
}

#ifndef TESTING

int main(void) {
  bool run = true;
  bool vehicleEntered = false;
  char choice;

  double vehicleEuroCost = 0.0, vehicleEngineVolume = 0.0, vehicleTransportingDistance = 0.0;
  int vehicleYear = 0;

  printIntroduction();

  while (run) {
    printf("Choose the option.\n");
    printf("a - Enter the parameters of the vehicle.\n");
    printf("b - Calculate and show the full cost.\n");
    printf("c - Exit.\n");
    printf("Enter a, b or c: ");

    choice = getABC();

    switch (choice) {
      case 'a': {
        if (vehicleEntered) {
          printf("The previous data about the vehicle will be lost!\n");
        }

        vehicleEntered = true;

        vehicleEuroCost = getEuroCost();
        vehicleYear = getYear();
        vehicleEngineVolume = getEngineVolume();
        vehicleTransportingDistance = getTransportingDistance();
        printf("\n\n");
        break;
      }

      case 'b': {
        if (vehicleEntered) {
          printf("The cost of the vehicle in Belarus: %f BYN.\n", calculateVehicleCostBYN(vehicleEuroCost));
          printf("The cost of transporting: %f €.\n", calculateTranportingCost(vehicleTransportingDistance));
          printf("The cost of the customs clearance: %f €.\n", calculateCustomsClearance(vehicleEngineVolume, vehicleYear));
          printf("\n\n");
        } else {
          printf("You didn't enter any data about the vehicle.\n");
          printf("\n\n");
        }

        break;
      }

      case 'c': {
        run = false;
      }
    }
  }

  return 0;
}

#endif
