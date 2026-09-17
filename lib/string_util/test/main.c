#include <stdio.h>

extern bool TEST_string_substring();

void DO_test(bool value) {
  if (value) {
    printf("Pass");
  }
}

int main() {
  DO_test(TEST_string_substring());
  return 0;
}
