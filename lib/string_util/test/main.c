#include "string_util.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

typedef struct _test {
  bool status;
  string_t *value_of_failure;
} test_t;

static test_t TEST_string_substring() {
  string_t *dummy_text = string_create("This works", 0);
  string_t *sub_text = string_new(0); /// Empty string

  test_t ret_val = {true};

  /// Case 1: The begining of the string_t
  string_substring(dummy_text, sub_text, (size_t)0, (size_t)4);
  if (strncmp(sub_text->content, dummy_text->content, 4) != 0) {
    ret_val.status = false;
    ret_val.value_of_failure = sub_text;
    return ret_val;
  }

  /// Case 2: The last character in a string_t
  string_substring(dummy_text, sub_text, dummy_text->size - 1,
                   dummy_text->size);
  if (strncmp(sub_text->content, dummy_text->content + dummy_text->size - 1,
              1) != 0) {
    ret_val.status = false;
    ret_val.value_of_failure = sub_text;
    return ret_val;
  }

  /// Case 3: The whole string_t
  string_substring(dummy_text, sub_text, (size_t)0, (size_t)dummy_text->size);
  if (strncmp(sub_text->content, dummy_text->content, dummy_text->size) != 0) {
    ret_val.status = false;
    ret_val.value_of_failure = sub_text;
    return ret_val;
  }

  return ret_val;
}

static test_t TEST_string_view_to_string() {
  string_t *dummy_text = string_create("Some Dummy Text To Be Used", 0);
  string_view_t *view = string_view(dummy_text->content, (size_t)5, (size_t)10);

  test_t ret_val = {true};

  /// Actual test
  string_t *converted_view = string_view_to_string(view);
  if (strncmp(converted_view->content, "Dummy", 5) != 0) {
    ret_val.status = false;
    ret_val.value_of_failure = converted_view;
    return ret_val;
  }

  return ret_val;
}

static test_t TEST_string_insert() {
  string_t *text = string_new(0);

  test_t ret_val = {true};

  string_insert(text, 0, "Hello", 5);
  if (strncmp(text->content, "Hello", 5) != 0) {
    ret_val.status = false;
    ret_val.value_of_failure = text;
    return ret_val;
  }

  string_insert(text, 5, " World", 6);
  if (strncmp(text->content, "Hello World", 11) != 0) {
    ret_val.status = false;
    ret_val.value_of_failure = text;
    return ret_val;
  }
  return ret_val;
}

static void DO_test(test_t value, size_t test_no) {
  /// The value is a test_t type containing both the status of the test and the
  /// string of the test in case of failure.
  /// The test_no is the idenfifier of the test.
  if (value.status) {
    printf("\033[32mTest %zu pass\033[0m\n", test_no);
  } else {
    printf("\033[31mTest %zu fail:\033[0m %s\n", test_no,
           value.value_of_failure->content);
  }
}

int main() {
  DO_test(TEST_string_substring(), 1);
  DO_test(TEST_string_view_to_string(), 2);
  DO_test(TEST_string_insert(), 3);
  return 0;
}
