#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#include "../include/lexer.h"


#define INITIAL_CAPACITY 64

static token make_token(token_type type, const char* start, int length, int line) 
{
    
    token _token;
    
    _token.type = type;
    
    _token.lexeme = (char*)malloc(length + 1);
    
    strncpy(_token.lexeme, start, length);
    
    _token.lexeme[length] = '\0';
    
    _token.line_number = line;
    
    return _token;
}

static token_type check_keyword(const char* str, int length) 
{
    
    if(length == 3 && strncmp(str, "let", 3) == 0) { return token_let; }

    if(length == 5 && strncmp(str, "print", 5) == 0) { return token_print; }
    
    return token_identifier;
}

token* tokenize(const char* source_code, int* out_count)
{
    
    int capacity = INITIAL_CAPACITY;

    token* tokens = (token*)malloc(sizeof(token) * capacity);

    if(!tokens)
    {
        printf("token creation failed!");
        return NULL;
    }

    int count = 0;

    int line = 1;

    const char* current = source_code;

    while(*current != '\0')
    {
        if(count >= capacity)
        {
            capacity *= 2;

            tokens = (token*)realloc(tokens, sizeof(token) * capacity);

            if(!tokens)
            {
                printf("tokens expansion failed!");
                free(tokens);
                return NULL;
            }
        }

        if(isspace(*current))
        {
            if(*current == '\n') { line++; }

            current++;

            continue;
        }

        if(isalpha(*current) || *current == '_')
        {
            const char* start = current;

            while(isalnum(*current) || *current == '_') { current++; }

            int length = current - start;

            token_type type = check_keyword(start, length);

            tokens[count++] = make_token(type, start, length, line);

            continue;
        }

        if(isdigit(*current))
        {
            const char* start = current;

            while(isdigit(*current)) { current++; }

            int length = current - start;

            tokens[count++] = make_token(token_int, start, length, line);

            continue;
        }

        switch(*current)
        {
            case '=' : tokens[count++] = make_token(token_assign, current, 1, line); 
                       break;
            case '+' : tokens[count++] = make_token(token_plus, current, 1, line);
                       break;
            case '-' : tokens[count++] = make_token(token_minus, current, 1, line);
                       break;
            case '*' : tokens[count++] = make_token(token_multiplication, current, 1, line);
                       break;
            case '/' : tokens[count++] = make_token(token_division, current, 1, line);
                       break;
            case '(' : tokens[count++] = make_token(token_left_parenthesis, current, 1, line);
                       break;
            case ')' : tokens[count++] = make_token(token_right_parenthesis, current, 1, line);
                       break;
            case ';' : tokens[count++] = make_token(token_semicolon, current, 1, line);
                       break;
            default: tokens[count++] = make_token(token_unrecognized, current, 1, line);
                       break;
        }
        
        
        current++;
}

        tokens[count++] = make_token(token_eof, "", 0, line);
        *out_count = count;
        return tokens;
}

void free_tokens(token* tokens, int count)
{
    for(int i = 0; i < count; ++i)
    {
        free(tokens[i].lexeme);
    }
    free(tokens);
}

