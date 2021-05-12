#ifndef CRIME_H
#define CRIME_H

#include <stdlib.h>
#include <string.h>

#include "check.h"
#include "list.h"

typedef char participant[100];

typedef struct {
    char place[50];
    list* participants;
    char aftermath[200];
    char specialists_comments[300];
} crime;

void* create_participant(const char* name);
void* create_participant_copy(const char* p);
void* create_crime(const char* place, const char* aftermath, const char* comments, list* participants);
void delete_crime(crime* cr);
crime* create_crime_copy(crime* cr);
crime* read_crime_from_user();
list* read_crimes(const char* filename);
list* read_crimes_file(FILE* fin);
void write_crimes(list* crimes, const char* filename);
void write_crimes_file(list* crimes, FILE* fout);
void print_crime(crime* cr);

#endif // CRIME_H
