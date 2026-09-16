#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"
#include "string_util.h"

static string_t *read_file(string_t *sourcefile) {
  /// Takes a filename and reads the contents of the file
  /// Returns a string_t pointer to the filecontents
#define BUFLEN 1024
  char _buffer[BUFLEN];
  FILE *fileptr;
  if ((fileptr = fopen(sourcefile->content, "r")) == nullptr) {
    fclose(fileptr);
    return nullptr;
  }
  fread(_buffer, sizeof(char), BUFLEN, fileptr);
  fclose(fileptr);

  return string_create(_buffer, 0);
}

int main(int argc, char **argv) {
  // TODO: Add a help message when run without arguments or with the "--help"
  // TODO: Add the ability to parse code on the command line without writing it
  // in a file
  if (argc == 1) {
    fprintf(stderr, "No text file to parse.\n");
    return EXIT_FAILURE;
  }
  string_t *sourcefile = string_create(argv[1], 0);
  string_t *const filecontents = read_file(sourcefile);
  if (filecontents == nullptr) {
    fprintf(stderr, "Error processing the file");
    return EXIT_FAILURE;
  }

  printf("%s\n\n------------------\n", filecontents->content);

  lex_parse(filecontents);

  return EXIT_SUCCESS;
}
