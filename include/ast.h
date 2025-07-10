#ifndef AST_H
#define AST_H

// binary operator types(+,-,*,/)
typedef enum
{
    op_add,
    op_sub,
    op_mul,
    op_div
} binary_operator_type;

// abstract syntax tree node types
typedef enum
{
    ast_variable_declaration, //let x = expression
    ast_print_statement, // print(x)
    ast_binary_operator, // eg. expression + expression
    ast_int_literal, // integer number
    ast_identifier // eg. x,a,b,...
} ast_node_type;

// forward declaration
typedef struct ast_node ast_node;

// ast node structure
struct ast_node
{
    ast_node_type type;

    union
    {
        // let x = expression
        struct 
        {
            char* name;
            ast_node* value;
        } variable_declaration;

        // print(x)
        struct 
        {
            char* name;
        } print_statement;

        // expression + expression
        struct 
        {
            binary_operator_type operator_type; // +,-,*,/
            ast_node* left; //left side operand of binary operator
            ast_node* right; // right side operand of binary operator
        } binary_expression;

        // number
        int integer_value;

        // x,a,y,...
        char* identifier;
    };
};

// allocate and create an integer literal node in abstract syntax tree
ast_node* create_integer_literal(int value);

// allocate and create an identifier node in abstract syntax tree
ast_node* create_identifier(const char* name);

// allocate and create a binary operation node in abstract syntax tree
ast_node* create_binary_expression(binary_operator_type _operator, ast_node* left, ast_node* right);

// allocate and create a variable declaration node in abstract syntax tree
ast_node* create_variable_declaration(const char* name, ast_node* value);

// allocate and create a print statement node in abstract syntax tree
ast_node* create_print_statement(char* name);

// free and abstract syntax tree parent node and all itss child nodes recursively
void free_ast(ast_node* node);

#endif