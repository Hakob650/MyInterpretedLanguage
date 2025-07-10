#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include "ast.h"

// holds a list of tokens and current position
typedef struct
{
    token* tokens; // array of tokens
    int count; // total token count
    int current; // current token index
} parser;

// initialize parser with list of tokens
void init_parser(parser* parser, token* tokens, int count);

// parse the entire program and return a list of ast nodes (array)
ast_node** parse_program(parser* parser, int* out_statement_count);

// free the array of ast nodes returned by parse_program
void free_ast_list(ast_node** node_list, int count);

#endif