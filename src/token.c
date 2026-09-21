#include "lexer.h"
#include "string_util.h"
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

extern string_t *get_token_id_name(enum token_type token_id) {
  /// Returns the name of a enum token_type token_id
  /// Returns nullptr if not found
  string_t *id = nullptr;
  switch (token_id) {
  case NUMERICLITERAL:
    id = string_create("NUMERICLITERAL", 0);
    break;

  case CHARACTERLITERAL:
    id = string_create("CHARACTERLITERAL", 0);
    break;

  case IDENTIFIER:
    id = string_create("IDENTIFIER", 0);
    break;

  case KEYWORD:
    id = string_create("KEYWORD", 0);
    break;

  case OPEQU:
    id = string_create("OPEQU", 0);
    break;

  case OPEQS:
    id = string_create("OPEQS", 0);
    break;

  case OPNEQ:
    id = string_create("OPNEQ", 0);
    break;

  case OPLT:
    id = string_create("OPLT", 0);
    break;

  case OPGT:
    id = string_create("OPGT", 0);
    break;

  case OPLE:
    id = string_create("OPLE", 0);
    break;

  case OPGE:
    id = string_create("OPGE", 0);
    break;

  case O_PARENTHESIS:
    id = string_create("O_PARENTHESIS", 0);
    break;

  case C_PARENTHESIS:
    id = string_create("C_PARENTHESIS", 0);
    break;

  case O_SQAUREBRACKET:
    id = string_create("O_SQAUREBRACKET", 0);
    break;

  case C_SQUAREBRACKET:
    id = string_create("C_SQUAREBRACKET", 0);
    break;

  case O_CURLEYBRACKET:
    id = string_create("O_CURLEYBRACKET", 0);
    break;

  case C_CURLEYBRACKET:
    id = string_create("C_CURLEYBRACKET", 0);
    break;

  case OPMUL:
    id = string_create("OPMUL", 0);
    break;

  case OPDIV:
    id = string_create("OPDIV", 0);
    break;

  case OPSUB:
    id = string_create("OPSUB", 0);
    break;

  case OPADD:
    id = string_create("OPADD", 0);
    break;

  case OPMOD:
    id = string_create("OPMOD", 0);
    break;

  case OPPOW:
    id = string_create("OPPOW", 0);
    break;

  case INCREMENT:
    id = string_create("INCREMENT", 0);
    break;

  case DECREMENT:
    id = string_create("DECREMENT", 0);
    break;

  case OPAND:
    id = string_create("OPAND", 0);
    break;

  case OPOR:
    id = string_create("OPOR", 0);
    break;

  case POINTER:
    id = string_create("POINTER", 0);
    break;

  case ADDRESSOF:
    id = string_create("ADDRESSOF", 0);
    break;

  case S_COMMENT:
    id = string_create("S_COMMENT", 0);
    break;

  case M_COMMENT:
    id = string_create("M_COMMENT", 0);
    break;

  case S_QUOTE:
    id = string_create("S_QUOTE", 0);
    break;

  case D_QUOTE:
    id = string_create("D_QUOTE", 0);
    break;

  case SEMICOLON:
    id = string_create("SEMICOLON", 0);
    break;

  case OPDOT:
    id = string_create("OPDOT", 0);
    break;

  case VARADIC:
    id = string_create("VARADIC", 0);
    break;

  case COMMA:
    id = string_create("COMMA", 0);
    break;

  case NEWLINE:
    id = string_create("NEWLINE", 0);
    break;
  }

  return id;
}

extern token_t *token_insert(token_t *token_head, void *token,
                             enum token_type token_id) {
  token_t *temp = (token_t *)malloc(sizeof(token_t));
  temp->value = token;
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

  /// Ignore space character
  while (contents[*index] == ' ') {
    (*index)++;
  }

  /// _start_index points to the start of a token
  size_t _start_index = *_index;

  /// Get an identifier or numeral literal
  if (isalnum(contents[*index]) || contents[*index] == '_') {
    while (isalnum(contents[*index + 1]) || contents[*index + 1] == '_')
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

extern string_t *_format_token_list(token_t *token_list) {
  token_t *currentptr = token_list;
  if (currentptr == nullptr) {
    fprintf(stderr, "The token_list is empty");
    return nullptr;
  }

  string_t *token_format = string_new(0);
  while (currentptr->next != nullptr) {
    auto tok = (string_t *)(currentptr->value);
    if (*(tok->content) == '\n') {
      char k;
      scanf("%c", &k);
      prints(token_format->content, token_format->size);
    }
    string_push(token_format, tok->content, tok->size);
    string_push(token_format, " ->", (size_t)3);

    currentptr = currentptr->next;
  }
  string_push(token_format, "null", (size_t)4);

  return token_format;
}
