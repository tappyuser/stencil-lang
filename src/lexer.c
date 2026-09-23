#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"
#include "string_util.h"

extern token_t *lex_parse(const string_t *const source) {
  /// Gets each token from the soruce code and assigns the correct token_type

  /// passed to the get_token function
  size_t index = 0;
  token_t *t_list = nullptr; /// linked list that contains tokens
  enum token_type token_id =
      NULLTYPE; /// The enum token_type is defined in the lexer.h header file

  while (index < source->size) {
    string_view_t *token = get_token(source, &index);
    switch (*(token->begin)) {
    case '*':
      if (memcmp(token->begin, "**", (size_t)2) == 0) {
        /// for the raise to power operator
        token_id = OPPOW;
      } else {
        token_id = OPMUL;
      }
      break;

    case '/':
      if (memcmp(token->begin, "//", (size_t)2) == 0) {
        token_id = S_COMMENT;
      } else {
        token_id = OPDIV;
      }
      break;

    case '+':
      if (memcmp(token->begin, "++", (size_t)2) == 0) {
        token_id = INCREMENT;
      } else {
        token_id = OPADD;
      }
      break;

    case '-':
      if (memcmp(token->begin, "--", (size_t)2) == 0) {
        token_id = DECREMENT;
      } else {
        token_id = OPSUB;
      }
      break;

    case '=':
      if (memcmp(token->begin, "==", (size_t)2) == 0) {
        token_id = OPEQS;
      } else {
        token_id = OPEQU;
      }
      break;

    case '.':
      if (memcmp(token->begin, "...", (size_t)3) == 0) {
        token_id = VARADIC;
      } else {
        token_id = OPDOT;
      }
      break;

    /// Quote
    case '\'':
      token_id = CHARACTERLITERAL;
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

    case '#':
      while (source->content[index] != '\n') {
        index++;
      }
      index++;
      token_id = NULLTYPE;
      break;

      /// Handles numbers, keywords and identifiers ie function names, variable
      /// names
    default:
      /// The rest that needs to be handled is are the alphanumerics like
      /// identifiers, and keywords and the invalid tokens

      /// Each character in the current token would be iterated through to check
      /// that it is a valid token. A valid alphanumeric token is one that
      /// contains alphabetic characters and(or) an underscore. It must not
      /// start with a number for identifiers or keywords but can contain a
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

    /// Add the token to the token list
    if (token_id != NULLTYPE)
      t_list = token_insert(t_list, (void *)token, token_id);
  }

#ifdef _STNL_DEBUG_
  /// Prints out the token value and the token id
  auto p = t_list;
  while (p) {
    auto tok = (string_view_t *)(p->value);
    prints(tok->begin, tok->size);
    printf(" %s\n\n", get_token_id_name(p->token_id)->content);
    p = p->next;
  }

  // prints out the contents of the list
  // string_t *formatted = _format_token_list(t_list);
  // printsn(formatted->content, formatted->size);
#endif /* ifdef _STNL_DEBUG_ */
  return t_list;
}
