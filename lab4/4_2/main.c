/*
 * 4.2 (5). Один из способов идентификации автора литературного
            произведения – подсчет частоты вхождения отдельных слов. В
            заданном текстовом файле найти 20 наиболее часто встречающихся
            слов с указанием частоты использования каждого из них.
 * */

#include "main.h"

bool is_letter(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

char to_lower(char c) {
  if (c >= 'A' && c <= 'Z') {
    return c - 'A' + 'a';
  }
  
  return c;
}

int str_length(const char* a) {
  int len = 0;
  
  while (*a) {
    a++;
    len++;
  }
  
  return len;
}

bool str_equal(const char* a, const char* b) {
  int a_len = str_length(a);
  int b_len = str_length(b);
  int i;
  
  if (a_len != b_len) { return false; }
  
  for (i = 0; i < a_len; i++) {
    if (a[i] != b[i]) {
      return false;
    }
  }
  
  return true; 
}

void str_copy(char* dest, const char* from) {
  int dest_len = str_length(dest);
  int from_len = str_length(from);
  int i;
  
  for (i = 0; i < dest_len; i++) {
    dest[i] = (char)0;
  }
  
  for (i = 0; i < from_len; i++) {
    dest[i] = from[i];
  }
}

void str_add_symbol(char* dest, char what) {
  int len = str_length(dest);
  dest[len] = what;
  dest[len + 1] = '\0';
}

void str_erase(char* s, int n) {
  int i;
  
  for (i = 0; i < n; i++) {
    s[i] = (char)0;
  }
}

word* read_words(FILE* fin, int* num_words) {
  word current_word = { 0 };
  word* words = NULL;
  int num = 0, i = 0;
  char curr = '\0';
  
  /* определить количество слов */
  while ((curr = fgetc(fin)) != EOF) {
    if (is_letter(curr)) {
      str_add_symbol(current_word, curr);
    } else {
      if (str_length(current_word) > 0) {
        num++;
        str_erase(current_word, 256);
      }
    }
  }
  
  /* выделить память под слова */
  *num_words = num;
  if (!(words = malloc(sizeof(word) * num))) {
    fprintf(stderr, "Error while allocating memory!\n");
    free(words);
    exit(EXIT_FAILURE);
  }
  
  /* переместиться в начало файла */
  rewind(fin);
  
  /* уже нормально считать слова */
  i = 0;
  while ((curr = fgetc(fin)) != EOF) {
    if (is_letter(curr)) {
      str_add_symbol(current_word, curr);
    } else {
      if (str_length(current_word) > 0) {
        str_copy(words[i], current_word);
        str_erase(current_word, 256);
        i++;
      }
    }
  }
  
  return words;
}

void get_most_frequent(word* words, int num_words, word most_frequent, int* max_freq) {
  int max_frequency = 0, frequency = 0;
  word current_word = { 0 };
  int i = 0, j = 0;
  
  str_erase(most_frequent, 256);
  
  for (i = 0; i < num_words; i++) {
    str_erase(current_word, 256);
    str_copy(current_word, words[i]);
    frequency = 0;
    
    for (j = 0; j < num_words; j++) {
      if (str_equal(current_word, words[j]) && !str_equal(current_word, "")) {
        frequency++;
      }
    }
    
    if (frequency > max_frequency) {
      str_copy(most_frequent, current_word);
      max_frequency = frequency;
    }
  }
  
  *max_freq = max_frequency;
}

int main() {
  word* words = NULL;
  word most_frequent = { 0 };
  int max_freq = 0;
  int num_words = 0;
  int i = 0, j = 0;
  
  FILE* text_file = fopen("text.txt", "r");
  if (!text_file) {
    fprintf(stderr, "Cannot open file\n");
  }
  
  words = read_words(text_file, &num_words);
  
  for (i = 0; i < num_words; i++) {
    for (j = 0; j < str_length(words[i]); j++) {
      words[i][j] = to_lower(words[i][j]);
    }
  }
  
  for (j = 0; j < 20; j++) {
    get_most_frequent(words, num_words, most_frequent, &max_freq);
    
    if (str_equal(most_frequent, "")) {
      break;
    }
    
    printf("The most frequent word N%d: %s - %d times\n", j + 1, most_frequent, max_freq);
  
    for (i = 0; i < num_words; i++) {
      if (str_equal(words[i], most_frequent)) {
        str_erase(words[i], 256);
      }
    }
  }
  
  free(words);
  fclose(text_file);
  return 0;
}
