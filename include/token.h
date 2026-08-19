#ifndef _STLTOKEN_H_
#define _STLTOKEN_H_

#include <stdio.h>

typedef struct { // Contains a string and its length
	unsigned int len;     // Length of the string
	const char* content;  // Holds the string	
} string_t;

static const string_t* initcontent(size_t n){
	string_t* content = (string_t*)malloc(sizeof(string_t));
	content->content = (const char*)calloc(n, sizeof(char));
	content->len = n; 

	return content;
}

extern const string_t* readfile(const char* filename, size_t n){
	/* Reads the contents of a file given the filename and the
	 unsinged int n which is the filename length */
	#define BUFLEN 100
	const string_t* filecontent = initcontent(BUFLEN);
	FILE* filehandle = fopen(filename, "r");
	fread(filecontent->content, sizeof(char), BUFLEN, filehandle);	
	snprintf(filecontent->content+BUFLEN-1, (size_t)1, "\0"); // Make sure that the buffer contains a NULL terminated character
	fclose(filehandle);

	return filecontent;
}

extern const token_t* token(const string_t* _buffer, const void* iter){
	/* Starts form the current position until a delimeter is hit */
	char* it = _buffer; 
	char* buffer = (char*)malloc(20);
	
	token_t* tok = (token_t*)malloc(sizeof(token_t));
	tok->buffer = (void*)buffer;
	
	// Ignores whitespaces and delimeter ';'
	while (isspace(*it)){
		if (*it++ == ';') continue;
		continue;
	}

	char* startpos = it;
	while (!(isspace(*it))){
		printf("*it = '%c'\n", *it);
			if (*it == ';') break;
			if (*it == '"'){
		printf("*it = '%c'\n", *it);
				while(*++it != '"') continue;
				memcpy(buffer, startpos, it - startpos + 1);
				buffer[it - startpos + 1] = '\0';
				tok->it = (void*)it;
				return tok;
			}
			it++;
	}

	memcpy(buffer, startpos, it - startpos);
	buffer[it - startpos + 1] = '\0';
	tok->it = (void*)it;

	return tok;
}


#endif
