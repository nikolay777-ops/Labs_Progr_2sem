#include <assert.h>

#include "main.h"

void test_str_length() {
  assert(str_length("aaa") == 3);
  assert(str_length("tgby") == 4);
  assert(str_length("qqqqqq") == 6);
}

void test_str_equal() {
  assert(str_equal("bool", "bool") == true);
  assert(str_equal("bjojo", "bjo") == false);
  assert(str_equal("doskofdkdso", "fsdkofdko") == false);
}

void test_str_copy() {
  char str1[20] = "Hello World!";
  char str2[20] = "";
  
  str_copy(str2, str1);
  assert(str_equal(str2, "Hello World!") == true);
  
  str_copy(str1, "dfokfso");
  assert(str_equal(str1, "Hello World!") == false);
}

void test_str_add_symbol() {
  char str[30] = "Hello Worl";
  str_add_symbol(str, 'd');
  assert(str_equal(str, "Hello World"));
}

void test_is_letter() {
  assert(is_letter('a'));
  assert(!is_letter('5'));
  assert(is_letter('N'));
  assert(!is_letter(']'));
}

void test_str_erase() {
  char s[20] = "Hello World";
  int i;
  str_erase(s, 20);
  
  for (i = 0; i < 20; i++) {
    assert(s[i] == 0);
  }
}

void test_to_lower() {
  assert(to_lower('A') == 'a');
  assert(to_lower('n') == 'n');
  assert(to_lower('8') == '8');
}

void test_read_words() {
  FILE* fin = fopen("test_text.txt", "r");
  int num_words = 0;
  word* words = read_words(fin, &num_words);
  
  assert(num_words == 8);
  assert(str_equal(words[0], "I"));
  assert(str_equal(words[4], "am"));
  assert(str_equal(words[7], "danger"));
  
  fclose(fin);
  free(words);
}

void test_get_most_frequent() {
  FILE* fin = fopen("test_text.txt", "r");
  int num_words = 0;
  word* words = read_words(fin, &num_words);
  int max_freq = 0;
  word most_frequent;
  
  get_most_frequent(words, num_words, most_frequent, &max_freq);
  assert(str_equal(most_frequent, "am"));
  
  fclose(fin);
  free(words);
}

#undef main
int main() {
  test_str_length();
  test_str_equal();
  test_str_copy();
  test_str_add_symbol();
  test_is_letter();
  test_str_erase();
  test_to_lower();
  test_read_words();
  test_get_most_frequent();
  
  puts("All tests passed successfully");
  return 0;
}
