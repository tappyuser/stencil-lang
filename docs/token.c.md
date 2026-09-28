# Token Source
Contains functions for working with the tokens

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

```C 
extern string_t *get_token_id_name(enum token_type token_id);
Converts the enum token_type to a string

Parameters:
  token_id        - the token_id of type enum token_type

Return Value:
  Returns the string_t * name of the enum token_type
```

```C 
extern token_t *token_insert(token_t *token_head, void *token, enum token_type token_id);
Inserts the token and the token_id into a singly linked list

Parameters:
  token_head      - points to the beginning of the list 
  token           - a string_view_t * of the token
  token_id        - the token_id of the token 

Return Value:
  Returns the token_t * token_head 
```


```C 
extern string_t *_format_token_list(token_t *token_list);
Formats the singly linked list into a string_t 

Parameters:
  token_list        - the head of the singly linked list containing the token

Return Value:
  Returns the string_t * of the formatted token list
```

