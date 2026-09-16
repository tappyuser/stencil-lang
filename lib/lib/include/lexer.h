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

  OPEQU, // =

  // Comparison Operators
  OPEQS, // ==
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
  OPMUL,     // *
  OPDIV,     // /
  OPSUB,     // -
  OPADD,     // +
  OPMOD,     // %
  OPPOW,     // **
  INCREMENT, // ++
  DECREMENT, // --

  // Arithmetic Operators
  OPAND, // &&
  OPOR,  // ||

  // Symbols
  POINTER,   // *
  ADDRESSOF, // &
  S_COMMENT, // // Single line Comment
  M_COMMENT, // /**/ Multi line Comment
  S_QUOTE,   // '
  D_QUOTE,   // "
  SEMICOLON, // ;
  OPDOT,     // .
  VARADIC,   // ...
  COMMA,     // ,
  NEWLINE,   // \n
};

typedef struct _token_t {
  void *value;
  enum token_type token_id;
  struct _token_t *next;
} token_t;

extern token_t *token_init(void *value, enum token_type token_id);
extern token_t *token_insert(token_t *token_head, void *token,
                             enum token_type token_id);
extern string_view_t *
get_token(const string_t *const text, /// The source code
          size_t *const _index);      /// The index to start from
extern token_t *lex_parse(const string_t *const source);

#endif /* ifndef _STNL_LEXER__ */
