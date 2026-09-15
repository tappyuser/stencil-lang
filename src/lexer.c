#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"
#include "string_util.h"

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

extern token_t *lex_parse(const string_t *const source) {
  /// Gets each token from the soruce code and assigns the correct token_type
  size_t index = 0;
  token_t *t_list = nullptr;
  enum token_type token_id;
  while (index < source->size) {
    string_view_t *token = get_token(source, &index);
    switch (*(token->begin)) {
    case '*':
      if (memcmp(token->begin, "**", token->size)) {
        token_id = OPPOW;
      } else {
        token_id = OPMUL;
      }
      break;

    case '/':
      if (memcmp(token->begin, "//", token->size)) {
        token_id = S_COMMENT;
      } else {
        token_id = OPDIV;
      }
      break;

    case '+':
      if (memcmp(token->begin, "++", token->size)) {
        token_id = INCREMENT;
      } else {
        token_id = OPADD;
      }
      break;

    case '-':
      if (memcmp(token->begin, "--", token->size)) {
        token_id = DECREMENT;
      } else {
        token_id = OPSUB;
      }
      break;

    case '=':
      if (memcmp(token->begin, "==", token->size)) {
        token_id = OPEQS;
      } else {
        token_id = OPEQU;
      }
      break;

    case '.':
      if (memcmp(token->begin, "...", token->size)) {
        token_id = VARADIC;
      } else {
        token_id = OPDOT;
      }
      break;

    /// Quote
    case '\'':
      token_id = S_QUOTE;
      break;

    case '"':
      token_id = D_QUOTE;
      break;

    // Brackets
    case '(':
      token_id = O_PARENTHESIS;
      break;

    case ')':
      token_id = C_PARENTHESIS;
      break;

    case '{':
      token_id = O_CURLEYBRACKET;
      break;

    case '}':
      token_id = C_CURLEYBRACKET;
      break;

    case '[':
      token_id = O_SQAUREBRACKET;
      break;

    case ']':
      token_id = C_SQUAREBRACKET;
      break;

    case ';':
      token_id = SEMICOLON;
      break;

    case ',':
      token_id = COMMA;
      break;

    case '\n':
      token_id = NEWLINE;
      break;

      /// Handles numbers, keywords and identifiers ie function names, variable
      /// names
    default:
      /// The rest that needs to be handled is are the alphanumerics like
      /// identifiers and keywords and the invalid tokens
      char _err_token[1024];
      memcpy(_err_token, token->begin, token->size);
      _err_token[token->size] = '\0';
      if (isalnum(*(token->begin))) {
        bool isDigit = false;
        for (size_t i = 0; i < token->size; ++i) {
          if (isdigit(*(token->begin))) {
            if (isalpha(*(token->begin + i))) {
              fprintf(stderr, "Invalid token %s\n", _err_token);
              return nullptr;
            }
            isDigit = true;
          }
        }
        if (isDigit) {
          token_id = NUMERICLITERAL;
        } else {
          token_id = IDENTIFIER;
        }
      }

      /// For the invalid tokens or tokens that haven't been handlded this just
      /// prints it out for debugging
      else {
        fprintf(stderr, "Unhandled or Invalid token %s\n", _err_token);
      }
      break;
    }
    t_list = token_insert(t_list, (void *)token, token_id);
  }
  // TODO: Identify each of the tokens and add the correct token_id
  auto p = t_list;
  while (p) {
    auto tok = (string_view_t *)(p->value);
    printf("---------------------------------\n");
    prints(tok->begin, tok->size);
    printf("%d\n\n", p->token_id);
    p = p->next;
  }

  return t_list;
}
