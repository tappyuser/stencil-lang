#include "string_util.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

void DO_test(bool value) {
  static size_t test_no = 1;
  if (value) {
    printf("\033[32mTest %zu pass\033[0m\n", test_no);
  } else {
    printf("\033[31mTest %zu fail\033[0m\n", test_no);
  }
  test_no++;
}

extern bool TEST_string_substring() {
  string_t *dummy_text = string_create("This works", 0);
  string_t *sub_text = string_new(0);
  string_substring(dummy_text, sub_text, (size_t)0, (size_t)4);

  if (!(strncmp(sub_text->content, dummy_text->content, 4))) {
    return true;
  }

  return false;
}

int main() {
  DO_test(TEST_string_substring());
  return 0;
}
