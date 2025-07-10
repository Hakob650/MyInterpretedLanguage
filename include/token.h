#ifndef TOKEN_H
#define TOKEN_H

typedef enum
{
    token_int, // integer literal
    token_identifier, // variable names
    token_assign, // =
    token_plus, // +
    token_minus, // -
    token_multiplication, // *
    token_division, // /
    token_left_parenthesis, // (
    token_right_parenthesis, // )
    token_semicolon, // ;
    token_print, // print keyword
    token_let, // let keyword(for variable declrations)
    token_eof, //end of file/input
    token_unrecognized, //undefined token
} token_type;

typedef struct  
{
    token_type type; //token type
    char* lexeme; //string representing thee token(copied from input)
    int line_number; //line number in source code
} token;


#endif