# Lexer Source
Contains the functions for generating the CST

## Functions
```C 
extern string_view_t *get_token(const string_t *const text,
                                size_t *const _index);
Gets a token from the text starting from the index. Each token is seperated 
by a space. Anything in quotes are not parsed.

Parameters:
  text        - the source code 
  _index      - the starting point where then next token should be gotten 

Return Value:
  Returns a string_view_t * of the next token
```

The tokenize function 
```C 
extern string_t lex_parser(const string_t *const source);

Takes the source code and converts it to the indiviual tokens

Parameters:
  source      - The source C code

Return Value:
  Returns a string_t * containing the tokenized code
```
