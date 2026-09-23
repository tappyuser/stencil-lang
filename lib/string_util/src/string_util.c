#include "string_util.h"
#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// Prints the contents of a buffer up to a specific size
extern void prints(char *arr, size_t size) {
  for (int i = 0; i < size; i++)
    if (arr[i] == '\n') {
      printf("\\n");
    } else {
      putchar(arr[i]);
    }
  errno = 0;
}

/// Does the same as prints but adds a newline
extern void printsn(char *arr, size_t size) {
  prints(arr, size);
  putchar('\n');
  errno = 0;
}

extern string_t *string_new(size_t n) {
  /// Initialises the string_t * arr with the capacity of n
  /// If arr is a nullptr, then it create the string_t *
  /// Returns the new arr

  string_t *tmp_arr = (string_t *)malloc(sizeof(string_t));
  tmp_arr->size = 0;
  tmp_arr->capacity = n;
  tmp_arr->content = (char *)malloc(sizeof(char) * n);

  return tmp_arr;
}

extern string_t *string_create(char *text, size_t n) {
  /// Creates a string_t from char *
  /// If the n is zero for null terminated string, then it uses the strlen
  /// function to determine the length. The length n must be specified for non
  /// null terminated strings.
  n = n == 0 ? strlen(text) : n;
  string_t *arr = string_new(n); /// Initialize the string_t * arr
  if (string_insert(arr, 0, text, n) == 0) {
    errno = 0;
  }

  return arr;
}

extern int8_t string_insert(string_t *arr, size_t index, char *elem, size_t n) {
  /// Inserts n bytes of char * elem into the string * arr at index.
  /// index must be zero when the arr is empty, that is arr->size is zero.
  /// Returns -1 if there is an IndexOutOfRange error.
  if (n == 0) {
    return -1;
  }
  if (n > strlen(elem))
    n = strlen(elem);

  char *temp = arr->content;

  /// Doubles the capacity if the container would not contain it. If the doubled
  /// capacity is still not enough, then it sets it to the required capacity.
  if (arr->capacity < arr->size + n) {
    arr->capacity =
        arr->capacity * 1 < arr->size + n ? arr->size + n : arr->capacity * 2;

    /// Reallocate memory for the arr->content and copy the memory
    arr->content = (char *)malloc(sizeof(char) * arr->capacity);
  }

  if (arr->size == 0) {
    if (index != 0) { /// index must be zero when the array is empty
      fprintf(stderr,
              "IndexOutOfRange: index must be zero for an empty array\n");
      return -1;
    }
    memcpy(arr->content, elem, n);
  } else {
    /// Copy the element into the arr->content buffer
    memcpy(arr->content, temp,
           index); /// Copies the begining of the string until the index
    memcpy(arr->content + index, elem,
           n); /// Copies the text at the specific index
    memcpy(arr->content + index + n, temp + index,
           arr->size - index); /// Copies the rest of the array
  }

  /// Free the old memeory
  if (temp != arr->content)
    free((void *)temp);
  arr->size += n;
  return 0;
}

extern int8_t string_push(string_t *arr, char *elem, size_t n) {
  /// Inserts an char * elem at the end of the string_t * arr
  return string_insert(arr, arr->size, elem, n);
}

static int8_t _remove_at(string_t *arr, size_t _index_s, size_t _index_e) {
  if (_index_e > arr->size || _index_s >= _index_e)
    return -1;
  char *temp = arr->content;
  arr->content = (char *)malloc(sizeof(char) * arr->capacity);
  memcpy(arr->content, temp, _index_s);
  memcpy(arr->content + _index_s, temp + _index_e, arr->size - _index_e);
  arr->size -= _index_e - _index_s;
  free((void *)temp);
  return 0;
}

extern int8_t string_remove_at(string_t *arr, size_t _index_s,
                               size_t _index_e) {
  /// Removes a range of characters from the container
  /// _index_s is inclusive
  /// _index_e is exclusive
  return _remove_at(arr, _index_s, _index_e);
}

extern string_t *string_substring(string_t *arr, string_t *dst, size_t _index_s,
                                  size_t _index_e) {
  /// Copies a range of characters starting from a start index till the end
  /// index, from the string_t * arr to the string_t * dst
  ///
  /// Returns the string_t * dst if successful, else returns nullptr
  ///
  /// _index_s is the start index and is inclusive
  /// _index_e is the end index and is exclusive
  if (_index_e > arr->size) {
    fprintf(stderr, "IndexOutOfRange: the end index is larger than the size of "
                    "the string_t * arr");
    return nullptr;
  }
  memcpy(dst->content, arr->content + _index_s, _index_e - _index_s);
  dst->size = _index_e - _index_s + 2;
  dst->capacity = dst->capacity == 0 ? dst->size : dst->capacity;
  *(dst->content + dst->size - 1) = '\0'; /// Null terminating the string
  return dst;
}

/* String View Functions */
extern string_view_t *string_view(char *arr, size_t _index_s, size_t _index_e) {
  if (_index_s >= _index_e)
    return nullptr;
  string_view_t *_view = (string_view_t *)malloc(sizeof(string_view_t));
  _view->size = _index_e - _index_s;
  _view->begin = arr + _index_s;
  _view->end = arr + _index_e;

  return _view;
}

extern string_t *string_view_to_string(string_view_t *view) {
  string_t *container = string_new(view->size + (size_t)1);
  strncpy(container->content, view->begin, view->size);
  *(container->content + container->size - 1) =
      '\0'; /// Makeing sure to null terminate
  return container;
}
