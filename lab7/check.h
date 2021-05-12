#ifndef CHECK_H
#define CHECK_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

void error(const char* msg);
void check_mem_alloc(void* data);
void check(const char* what, bool err);
void fgets_without_newline(char* dest, int n, FILE* fin);
void fputs_with_newline(const char* str, FILE* fout);
void clear();
void tolower_str(char* str);

#endif // CHECK_H
