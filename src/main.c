#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "string_util.h"

static string_t* read_file(string_t* sourcefile){
	#define BUFLEN 1024
	char _buffer[BUFLEN];
	FILE* fileptr = fopen(sourcefile->content, "r");
	fread(_buffer, sizeof(char), BUFLEN, fileptr);
	fclose(fileptr);

	return string_create(_buffer, 0);
}

int main (int argc, char** argv){
	string_t* sourcefile = string_create(argv[1], 0);
	string_t* contents = read_file(sourcefile);

	printf(contents->content);

	return EXIT_SUCCESS;
}
