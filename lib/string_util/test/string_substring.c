#include "string_util.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

extern bool TEST_string_substring() {
  string_t *dummy_text = string_create("This works", 0);
  string_t *sub_text = string_new(0);
  string_substring(dummy_text, sub_text, (size_t)0, (size_t)4);

  if (!(strncmp(sub_text->content, dummy_text->content, 4))) {
    return true;
  }
  printf("%s\n", sub_text->content);

  return false;
}
