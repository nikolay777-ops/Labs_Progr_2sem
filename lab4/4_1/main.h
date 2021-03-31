#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef char line[256];

int str_length(const char* a);
void str_copy(char* dest, const char* from);
bool str_equal(const char* a, const char* b);
bool all_letters_are_different(const char* a);
bool is_letter(char c);
void str_add_symbol(char* dest, char what);
void str_erase(char* s, int n);
void get_max_word(char* max_word, const char* str);

#endif
