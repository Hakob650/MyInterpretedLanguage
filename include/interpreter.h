#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "ast.h"

// interpret an array of ast statements
// returns 0 on success, non-zero on error
int interpret(ast_node** statements, int count);

#endif