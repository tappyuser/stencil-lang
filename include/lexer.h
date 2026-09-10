#ifndef _STNL_LEXER_
#define _STNL_LEXER_

#include "string_util.h"
#include <stdio.h>
#include <stdlib.h>

enum token_type {
  // Literals
  NUMERICLITERAL = 1,
  CHARACTERLITERAL,

  // Language specific
  IDENTIFIER,
  KEYWORD,

  // Comparison Operators
  OPEQ,  // =
  OPNEQ, // !=
  OPLT,  // <
  OPGT,  // >
  OPLE,  // <=
  OPGE,  // >=

  // Brackets
  O_PARENTHESIS,   // (
  C_PARENTHESIS,   // )
  O_SQAUREBRACKET, // [
  C_SQUAREBRACKET, // ]
  O_CURLEYBRACKET, // {
  C_CURLEYBRACKET, // }

  // Arithmetic Operators
  OPMUL, // *
  OPDIV, // /
  OPSUB, // -
  OPADD, // +
  OPMOD, // %
  OPPOW, // **

  // Arithmetic Operators
  OPAND, // &&
  OPOR,  // ||
  // Symbols
  POINTER,  // *
  ADDRESSOF // &
};

typedef struct _token_t {
  void *value;
  enum token_type token_id;
  struct _token_t *next;
} token_t;

extern token_t *token_init(void *value, enum token_type token_id);
extern token_t *token_insert(token_t *token_head, token_t *token,
                             enum token_type token_id);
extern string_view_t *
get_token(const string_t *const text, /// The source code
          size_t *const _index);      /// The index to start from
extern string_t lex_parser(const string_t *const source);

#endif /* ifndef _STNL_LEXER__ */
