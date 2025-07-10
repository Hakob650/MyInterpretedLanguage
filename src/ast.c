#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/ast.h"

// Helper: strdup for portability if not available
static char* str_clone(const char* str)
{
    char* copy = (char*)malloc(strlen(str) + 1);

    if(!copy)
    {
        printf("allocation for copy of the string failed!");
        return NULL;
    }

    strcpy(copy, str);

    return copy;
}


ast_node* create_integer_literal(int value)
{
    ast_node* node = (ast_node*)malloc(sizeof(ast_node));

    if(!node)
    {
        printf("Allocation for integer literal node failed!");
        return NULL;
    }

    node->type = ast_int_literal;

    node->integer_value = value;

    return  node;
}

ast_node* create_identifier(const char* name)
{
    ast_node* node = (ast_node*)malloc(sizeof(ast_node));

    if(!node)
    {
        printf("Allocation for indetifier node failed!");
        return NULL;
    }

    node->type = ast_identifier;

    node->identifier = str_clone(name);

    return node;
}

ast_node* create_variable_declaration(const char* name, ast_node* value)
{
    ast_node* node = (ast_node*)malloc(sizeof(ast_node));

    if(!node)
    {
        printf("Allocation for variable decalaration node failed!");
        return NULL;
    }

    node->type = ast_variable_declaration;

    node->variable_declaration.value = value;

    node->variable_declaration.name = str_clone(name);

    return node;
}

ast_node* create_binary_expression(binary_operator_type _operator, ast_node* left, ast_node* right)
{
    ast_node* node = (ast_node*)malloc(sizeof(ast_node));

    if(!node)
    {
        printf("Aloocation for binary expression node failed!");
        return NULL;
    }

    node->type = ast_binary_operator;
    
    node->binary_expression.operator_type = _operator;

    node->binary_expression.left = left;

    node->binary_expression.right = right;

    return node;
}

ast_node* create_print_statement(char* name)
{
    ast_node* node = (ast_node*)malloc(sizeof(ast_node));

    if(!node)
    {
        printf("Alloocation for print statement node failed!");
        return NULL;
    }

    node->type = ast_print_statement;

    node->print_statement.name = str_clone(name);

    return node;
}

// === Recursive Free Function === //
void free_ast(ast_node* node)
{
    if(!node)
    {
        return;
    }

    switch(node->type)
    {
        case ast_variable_declaration:
                                        free(node->variable_declaration.name);
                                        free_ast(node->variable_declaration.value);
                                        break;
        case ast_print_statement:
                                        free(node->print_statement.name);
                                        break;
        case ast_binary_operator:
                                        free_ast(node->binary_expression.left);
                                        free_ast(node->binary_expression.right);
                                        break;
        case ast_identifier:
                                        free(node->identifier);
                                        break;
        case ast_int_literal:
                                        break;
    }
    free(node);
}