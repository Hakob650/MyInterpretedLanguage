#ifndef LEXER_H
#define LEXER_H

#include "token.h"

// tokenize the source code into array of tokens.
// parameters:
//    source code: the input program as a string
//    out_count: pointer to an int where the number of tokens will be stored
// returns:
//    a dynamically allocated array of token structs
//    must be freed using free_tokens()
token* tokenize(const char* source_code, int* out_count);

// free the memory allocated for token array
// parameters:
//       token* tokens: array of tokens that must be freed
//       int count: count of the tokens in the array
void free_tokens(token* tokens, int count);

#endif