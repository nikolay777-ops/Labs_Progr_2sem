#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef char word[256];

bool is_letter(char c);
char to_lower(char c);
int str_length(const char* a);
bool str_equal(const char* a, const char* b);
void str_copy(char* dest, const char* from);
void str_add_symbol(char* dest, char what);
void str_erase(char* s, int n);
word* read_words(FILE* fin, int* num_words);
void get_most_frequent(word* words, int num_words, word most_frequent, int* max_freq);

#endif 
