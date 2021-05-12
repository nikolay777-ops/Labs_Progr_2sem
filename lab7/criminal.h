#ifndef CRIMINAL_H
#define CRIMINAL_H

#include "list.h"
#include "crime.h"
#include "organization.h"

#define MAX_HEIGHT_CM 250.0f
#define MIN_HEIGHT_CM 110.0f
#define MAX_WEIGHT_KG 200.0f
#define MIN_WEIGHT_KG 30.0f

typedef struct {
    char name[50];
    char nickname[50];
    float height_cm;
    float weight_kg;
    char hair_color[20];
    char special_signs[200];
    char citizenship[30];
    char languages[100];
    char kind_of_crimes[50];
    list* crimes;
    list* organizations;
} criminal;

void* create_criminal(const char* name, const char* nickname, const char* citizenship, const char* hair_color,
                      const char* languages, const char* special_signs, float height_cm, float weight_kg, 
                      const char* kind_of_crimes, list* crimes, list* organizations);
criminal* create_criminal_copy(criminal* cr);
void delete_criminal(criminal* cr);
void print_criminal(criminal* cr);
void print_criminal_name(criminal* cr);
criminal* read_criminal_from_user();
list* read_criminals(const char* filename);
void write_criminals(list* criminals, const char* filename);
void write_criminal(criminal* cr, FILE* fout, bool end);
void write_criminals_file(list* criminals, FILE* fout);

#endif // CRIMINAL_H
