#ifndef ORGANIZATION_H
#define ORGANIZATION_H

#include <stdio.h>
#include <string.h>

#include "check.h"
#include "list.h"

#define MIN_DANGER_LEVEL 1
#define MAX_DANGER_LEVEL 10

typedef struct {
    char name[40];
    char direction[60];
    int danger_level;
} organization;

void* create_organization(char name[], char direction[], int danger_level);
organization* create_organization_copy(organization* org);
void print_organization(organization* org);
organization* read_organization(FILE* fin);
organization* read_organization_from_user();
list* read_organizations(const char* filename);
list* read_organizations_file(FILE* fin);
void write_organization(organization* org, FILE* fout, bool end);
void write_organizations(list* organizations, const char* filename);
void write_organizations_file(list* organizations, FILE* fout);

#endif // ORGANIZATION_H
