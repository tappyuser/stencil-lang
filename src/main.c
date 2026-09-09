#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "string_util.h"

static string_t *read_file(string_t *sourcefile) {
  /// Takes a filename and reads the contents of the file
  /// Returns a pointer to the filecontents
#define BUFLEN 1024
  char _buffer[BUFLEN];
  FILE *fileptr = fopen(sourcefile->content, "r");
  fread(_buffer, sizeof(char), BUFLEN, fileptr);
  fclose(fileptr);

  return string_create(_buffer, 0);
}

static string_view_t *get_token(const string_t *const text, size_t *_index) {
  bool isQuote = false; /// For parsing inside of a string
  char *contents = text->content;
  string_view_t *token;

  /// index passes through the text and checks if  each character meets a
  /// specific condition eg if `abc = 5;` abc, = and 5 are all tokens While
  /// parsing _start_index would point to 'a', index would keep incrementing
  /// until it sees a space then it would stop to get the token 'abc'.
  size_t *index = _index;

  /// Ignore whitespace
  while (isspace(contents[*index])) {
    (*index)++;
    continue;
  }

  /// _start_index points to the start of a token
  size_t _start_index = *_index;

  /// Get an identifier
  if (isalnum(contents[*index])) {
    while (isalnum(contents[*index + 1]))
      (*index)++;

    token = string_view(contents, _start_index, *index + 1);
    prints(token->begin, token->size);
  } else {
    while (contents[*index] == ';') {
      /// Colon depicts a new line
      (*index)++;
      continue;
    }
    if (contents[*index] == '*' || contents[*index] == '-' ||
        contents[*index] == '+' || contents[*index] == '.') {
      /// For reapeating non alphanumeric tokens like '**' '++' '--' '...'
      while (contents[*index + 1] == contents[*index])
        (*index)++;
      token = string_view(contents, _start_index, *index + 1);
      prints(token->begin, token->size);
    } else if (contents[*index] == '"') {
      isQuote = true;
      while (isQuote) {
        (*index)++;
        if (contents[*index] == '"' && contents[*index - 1] != '\\') {
          isQuote = false;
        }
      }
      token = string_view(contents, _start_index, *index + 1);
      prints(token->begin, token->size);
    } else if (contents[*index] == '\'') {
      isQuote = true;
      while (isQuote) {
        (*index)++;
        if (contents[*index] == '\'' && contents[*index - 1] != '\\') {
          isQuote = false;
        }
      }
      token = string_view(contents, _start_index, *index + 1);
      prints(token->begin, token->size);
    } else {
      token = string_view(contents, _start_index, *index + 1);
      prints(token->begin, token->size);
    }
  }
  (*index)++;
  return token;
}

static string_t parse(const string_t *const filecontents) {
  size_t index = 0;
  while (index < filecontents->size) {
    get_token(filecontents, &index);
  }
}

int main(int argc, char **argv) {
  // TODO: Add a help message
  if (argc == 1) {
    printf("No text file to parse\n");
    return EXIT_FAILURE;
  }
  string_t *sourcefile = string_create(argv[1], 0);
  string_t *const filecontents = read_file(sourcefile);

  printf("%s\n\n------------------\n", filecontents->content);

  parse(filecontents);

  return EXIT_SUCCESS;
}
