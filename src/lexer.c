#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"
#include "string_util.h"

extern string_t *get_token_id_name(enum token_type token_id) {

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

extern token_t *lex_parse(const string_t *const source) {
  /// Gets each token from the soruce code and assigns the correct token_type

  /// passed to the get_token function
  size_t index = 0;
  token_t *t_list = nullptr; /// linked list that contains tokens
  enum token_type
      token_id; /// The enum token_type is defined in the lexer.h header file

  while (index < source->size) {
    string_view_t *token = get_token(source, &index);
    switch (*(token->begin)) {
    case '*':
      if (memcmp(token->begin, "**", token->size)) {
        /// for the raise to power operator
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

      /// Each character in the current token would be iterated through to check
      /// that it is a valid token. A valid alphanumeric token is one that
      /// contains alphabetic characters and(or) an underscore. It must not
      /// start with a number for an identifiers or keywords but can contain a
      /// number after an alphabetic character or an underscore.
      char _err_token[1024];
      /// 1024 characters is the maximum length for a variable

      /// Since the token is of type string_view_t *, it cannot be printed to
      /// stderr by fprintf since it only accepts null terminated strings.
      /// Hence, _err_token would contain the invalid token to be printed out.
      memcpy(_err_token, token->begin, token->size);
      _err_token[token->size] = '\0';

      if (isalnum(*(token->begin)) || *(token->begin) == '_') {
        bool isDigit = false;
        for (size_t i = 0; i < token->size; ++i) {
          if (isdigit(*(token->begin))) {
            if (isalpha(*(token->begin + i)) || *(token->begin + i) == '_') {
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

      /// For the invalid tokens or tokens that haven't been handlded, this just
      /// prints it out for debugging
      else {
        fprintf(stderr, "Unhandled or Invalid token %s\n", _err_token);
      }
      break;
    }
    t_list = token_insert(t_list, (void *)token, token_id);
  }
  /// Prints out the token value and the token id
  auto p = t_list;
  while (p) {
    auto tok = (string_view_t *)(p->value);
    // printf("---------------------------------\n");
    prints(tok->begin, tok->size);
    printf(" %s\n\n", get_token_id_name(p->token_id)->content);
    p = p->next;
  }

  return t_list;
}
