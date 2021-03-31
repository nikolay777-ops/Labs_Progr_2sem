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

void test_all_letters_are_different() {
  assert(all_letters_are_different("qwerty"));
  assert(!all_letters_are_different("kfdodf"));
  assert(all_letters_are_different("a"));
}

void test_str_erase() {
  char s[20] = "Hello World";
  int i;
  str_erase(s, 20);
  
  for (i = 0; i < 20; i++) {
    assert(s[i] == 0);
  }
}

void test_get_max_word() {
  char max_word[30] = { 0 };
  const char* ln = "Hello World";
  get_max_word(max_word, ln);
  assert(str_equal(max_word, "World"));
}

#undef main
int main() {
  test_str_length();
  test_str_equal();
  test_str_copy();
  test_str_add_symbol();
  test_is_letter();
  test_str_erase();
  test_all_letters_are_different();
  test_get_max_word();
  
  puts("All tests passed successfully");
  return 0;
}
