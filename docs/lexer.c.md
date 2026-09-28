# Lexer Source
Contains the functions for generating the CST

## Functions
The tokenize function 
```C 
extern string_t lex_parser(const string_t *const source);

Takes the source code and converts it to the indiviual tokens

Parameters:
  source      - The source C code

Return Value:
  Returns a string_t * containing the tokenized code
```
