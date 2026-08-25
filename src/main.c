#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "string_util.h"

static string_t* read_file(string_t* sourcefile){
	#define BUFLEN 1024
	char _buffer[BUFLEN];
	FILE* fileptr = fopen(sourcefile->content, "r");
	fread(_buffer, sizeof(char), BUFLEN, fileptr);
	fclose(fileptr);

	return string_create(_buffer, 0);
}

static string_t* parse(string_t* text){
	bool isQuote = false; /// For parsing inside of a string
	bool isToken = false;
	size_t _start_index = 0;
	char* contents = text->content;
	char c;
	string_view_t* token;
	size_t index = 0;
	/* for(size_t index = 0; index < text->size; ++index){ */
	while(index < text->size){
		c = contents[index];
		_start_index = index;
		if (isspace(c)) { 
			index++;
			continue;
		}

		if (isalnum(c)){
			/* _start_index = index; */
			while (isalnum(contents[index + 1])) index++;			
			
			token = string_view(contents, _start_index, index + 1);
			prints(token->begin, token->size);
		}
		else{
			if (c == ';') {
				index++;
				continue;
			}
			if (c == '*' || c == '-' || c == '+' || c == '.'){
				/// For reapeating non alphanumeric tokens like '**' '++' '--'
				while (contents[index + 1] == c) index++;
				token = string_view(contents, _start_index, index + 1);
				prints(token->begin, token->size);
			}
			else {
				token = string_view(contents, _start_index, index + 1);
				prints(token->begin, token->size);
			}
			
		}

		index++;
	}	
	
}

int main (int argc, char** argv){
	string_t* sourcefile = string_create(argv[1], 0);
	string_t* filecontents = read_file(sourcefile);

	printf("%s\n\n", filecontents->content);

	parse(filecontents);

	return EXIT_SUCCESS;
}
