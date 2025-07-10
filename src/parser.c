#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/parser.h"

// === Utitlity Functions
static token peek(parser* parser)
{
    if(parser->current < parser->count)
    {
        return parser->tokens[parser->current];
    }
    return (token){ .type = token_eof };
}

static token advance(parser* parser)
{
    if(parser->current < parser->count)
    {
        return parser->tokens[parser->current++];
    }
    return (token){ .type = token_eof };
}

static int match(parser* parser, token_type type)
{
    if(peek(parser).type == type)
    {
        advance(parser);
        return 1;
    }   
    return 0;
}

static token expect(parser* parser, token_type type, const char* message)
{
    token _token = peek(parser);

    if(_token.type == type)
    {
        return advance(parser);
    }
    else
    {
        fprintf(stderr, "[Parser Error] Line %d: Expected %s but got %d ('%s')\n", _token.line_number, message, _token.type, _token.lexeme);
        exit(1);
    }
}

// === Forward Declarations === //
static ast_node* parse_statement(parser* parser);
static ast_node* parse_expression(parser* parser);
static ast_node* parse_term(parser* parser);
static ast_node* parse_factor(parser* parser);


// === API === //
void init_parser(parser* parser, token* tokens, int count)
{
    parser->tokens = tokens;
    parser->count = count;
    parser->current = 0;
}

ast_node** parse_program(parser* parser, int* out_stmt_count)
{
    ast_node** statements = NULL;

    int capacity = 0;

    int count = 0;

    while(peek(parser).type != token_eof)
    {
        
        if(count >= capacity)
        {
            capacity = capacity == 0 ? 8 : capacity * 2;

            statements = realloc(statements, capacity * sizeof(ast_node*));

            if(!statements)
            {
                fprintf(stderr, "Rellocation failed!");
                
                exit(1);
            }
        }
        
        statements[count++] = parse_statement(parser);
    }
    
    *out_stmt_count = count;
    
    return statements;
}

void free_ast_list(ast_node** node_list, int count)
{
    for(int i = 0; i < count; ++i)
    {
        free(node_list[i]);
    }
    free(node_list);
}

// === Parser Implementation === //
static ast_node* parse_statement(parser* parser)
{
    if(match(parser, token_let))
    {
        token token_name = expect(parser, token_identifier, "identifier after 'let' ");

        expect(parser, token_assign, "'='");

        ast_node* value = parse_expression(parser);

        expect(parser, token_semicolon, "';'");

        return create_variable_declaration(token_name.lexeme, value);
    }

    if(match(parser, token_print))
    {
        expect(parser, token_left_parenthesis, "'('");

        token token_name = expect(parser, token_identifier, "identifier inside print");

        expect(parser, token_right_parenthesis, "')'");

        expect(parser, token_semicolon, "';'");

        return create_print_statement(token_name.lexeme);
    }

    token _token = peek(parser);

    fprintf(stderr, "[Parser Error] Line %d: Unexpected token '%s'\n", _token.line_number, _token.lexeme);

    exit(1);
}

static ast_node* parse_expression(parser* parser)
{
    ast_node* node = parse_term(parser);

    while(peek(parser).type == token_plus || peek(parser).type == token_minus)
    {
        token _operator = advance(parser);

        ast_node* right = parse_term(parser);

        binary_operator_type binary_operator = (_operator.type == token_plus) ? op_add : op_sub;

        node = create_binary_expression(binary_operator, node, right);
    }

    return node;
}

static ast_node* parse_term(parser* parser)
{
    ast_node* node = parse_factor(parser);

    while(peek(parser).type == token_multiplication || peek(parser).type == token_division)
    {
        token _operator = advance(parser);

        ast_node* right = parse_factor(parser);

        binary_operator_type binary_operator = (_operator.type == token_multiplication) ? op_mul : op_div;

        node = create_binary_expression(binary_operator, node, right);
    }

    return node;
}

static ast_node* parse_factor(parser* parser)
{
    token _token = peek(parser);

    if(match(parser, token_int))
    {
        return create_integer_literal(atoi(_token.lexeme));
    }
    
    if(match(parser, token_identifier))
    {
        return create_identifier(_token.lexeme);
    }

    if(match(parser, token_left_parenthesis))
    {
        ast_node* inner = parse_expression(parser);

        expect(parser, token_right_parenthesis, "')'");

        return inner;
    }

    fprintf(stderr, "[Parser Error] Line %d : Unexpected token '%s' in expression\n", _token.line_number, _token.lexeme);
    exit(1);
}

