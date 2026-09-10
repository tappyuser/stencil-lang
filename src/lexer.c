#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "lexer.h"
#include "string_util.h"

// extern token_t *token_init(void *value, enum token_type token_id) {
//   /// Creates a signly linked list
//   token_t *token = (token_t *)malloc(sizeof(token_t));
//   token->value = value;
//   token->next = nullptr;
//   token->token_id = token_id;
//
//   return token;
// }

extern token_t *token_insert(token_t *token_head, token_t *token,
                             enum token_type token_id) {
  token_t *temp = (token_t *)malloc(sizeof(token_t));
  temp->value = (void *)token;
  temp->next = nullptr;
  temp->token_id = token_id;

  if (token_head == nullptr) {
    token_head = temp;
  } else {
    token_t *current_token = token_head;
    token_t *previous;
    while (current_token) {
      previous = current_token;
      current_token = current_token->next;
    }
    previous->next = temp;
  }

  return token_head;
}
extern string_view_t *get_token(const string_t *const text,
                                size_t *const _index) {
  bool isQuote = false; /// For parsing inside of a string
  char *contents = text->content;
  string_view_t *token; /// Contains the token

  /// index passes through the text and checks if  each character meets a
  /// specific condition eg if `abc = 5;` abc, = and 5 are all tokens. While
  /// parsing _start_index would point to 'a', index would keep incrementing
  /// until it sees a space then it would stop to get the token 'abc'.
  size_t *index = _index;

  /// Ignore whitespace
  while (contents[*index] == ' ') {
    (*index)++;
  }

  /// _start_index points to the start of a token
  size_t _start_index = *_index;

  /// Get an identifier or numeral literal
  if (isalnum(contents[*index])) {
    while (isalnum(contents[*index + 1]))
      (*index)++;

    token = string_view(contents, _start_index, *index + 1);
  }

  else {
    /// Handles semicolon
    if (contents[*index] == ';' || contents[*index] == '\n') {
      token = string_view(contents, _start_index, *index + 1);
    }

    /// For reapeating non alphanumeric tokens like '**' '++' '--' '...' '//'
    else if (contents[*index] == '*' || contents[*index] == '-' ||
             contents[*index] == '+' || contents[*index] == '.' ||
             contents[*index] == '/' || contents[*index] == '&' ||
             contents[*index] == '|') {
      while (contents[*index + 1] == contents[*index])
        (*index)++;
      token = string_view(contents, _start_index, *index + 1);
    }

    /// Parse the contents of a double quote
    else if (contents[*index] == '"') {
      isQuote = true;
      while (isQuote) {
        (*index)++;
        if (contents[*index] == '"' && contents[*index - 1] != '\\') {
          isQuote = false;
        }
      }
      token = string_view(contents, _start_index, *index + 1);
    }

    /// Parse the contents of a single quote
    else if (contents[*index] == '\'') {
      isQuote = true;
      while (isQuote) {
        (*index)++;
        if (contents[*index] == '\'' && contents[*index - 1] != '\\') {
          isQuote = false;
        }
      }
      token = string_view(contents, _start_index, *index + 1);
    }

    /// Everything else
    else {
      token = string_view(contents, _start_index, *index + 1);
    }
  }

  (*index)++;
  return token;
}

extern string_t lex_parser(const string_t *const source) {
  size_t index = 0;
  token_t *t_list = nullptr;
  while (index < source->size) {
    string_view_t *token = get_token(source, &index);
    // TODO: Identify each of the tokens and add the correct token_id
    if (t_list == nullptr) {
      t_list = token_insert(t_list, (void *)token, IDENTIFIER);
    } else {
      t_list = token_insert(t_list, (void *)token, NUMERICLITERAL);
    }
  }

  // TODO: Properly test the t_list variable if it contains the proper tokens ie
  // print the string_view_t * token contents
  token_t *p = t_list;
  while (p) {
    printf("%x\n", p /* ->token_id */);
    p = p->next;
  }
}
