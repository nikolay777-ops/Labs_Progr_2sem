/*
 * 4.1 (5). Разнобуквица. С клавиатуры вводится многострочный текст.
 *          Распечатать самое длинное слово, в котором все буквы разные.
 * */

#include "main.h"

int str_length(const char* a) {
  int len = 0;
  
  while (*a) {
    a++;
    len++;
  }
  
  return len;
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

bool all_letters_are_different(const char* a) {
  int i, j;
  char word[256];
  int word_len;
  
  str_copy(word, a);
  word_len = str_length(word);
  
  for (i = 0; i < word_len; i++) {
    for (j = 0; j < word_len; j++) {
      if (i == j) {
        continue;
      }
      
      if (word[i] == word[j]) {
        return false;
      }
    }
  }
  
  return true;
}

bool is_letter(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
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

void get_max_word(char* max_word, const char* str) {
  int i;
  char word[256] = { 0 };
  
  for (i = 0; i < str_length(str); i++) {
    if (is_letter(str[i])) {
      str_add_symbol(word, str[i]);
    } else {
      if (all_letters_are_different(word) && str_length(word) > str_length(max_word)) {
        str_copy(max_word, word);
      }
      
      str_erase(word, 256);
    }
  }
  
  if (all_letters_are_different(word) && str_length(word) > str_length(max_word)) {
    str_copy(max_word, word);
  }
      
  str_erase(word, 256);
}

int main() {
  line str;
  char line_max_word[256] = { 0 };
  char text_max_word[256] = { 0 };
  int j, len;
  
  puts("Enter the text. Enter '-' to finish:");
  fgets(str, 255, stdin);
  
  while (!str_equal(str, "-\n")) {
    len = str_length(line_max_word);
    for (j = 0; j < len; j++) {
      line_max_word[j] = (char)0;
    }
    
    get_max_word(line_max_word, str);
    
    if (str_length(text_max_word) < str_length(line_max_word)) {
      str_copy(text_max_word, line_max_word);
    }
    
    fgets(str, 255, stdin);
  }
  
  printf("Max word: %s\n", text_max_word);
  printf("Max word length: %d\n", str_length(text_max_word));
  
  return 0;
}
