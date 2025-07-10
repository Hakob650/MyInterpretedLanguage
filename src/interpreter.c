#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/interpreter.h"

// Simple environment: A linked list mapping variable names to integer values 
typedef struct variable_entry
{
    char* name;
    int value;
    struct variable_entry* next;
} variable_entry;

static variable_entry* environment = NULL;

static void set_environment(const char* name, int value)
{
    variable_entry* current = environment;

    while (current)
    {
        if (strcmp(current->name, name) == 0)  // ✅ names match
        {
            current->value = value;
            return;
        }
        current = current->next;  // ✅ move to next entry
    }

    // Add new variable
    variable_entry* new_entry = malloc(sizeof(variable_entry));
    if (!new_entry)
    {
        fprintf(stderr, "Allocation for new variable entry failed!\n");
        exit(1);
    }

    new_entry->name = strdup(name);
    new_entry->value = value;
    new_entry->next = environment;
    environment = new_entry;
}


static int get_environment(const char* name, int* out_value)
{
    variable_entry* current = environment;

    while(current)
    {
        if(strcmp(current->name, name) == 0)
        {
            *out_value = current->value;
            
            return 1;
        }

        current = current->next;
    }

    return 0;
}

static void free_environment()
{
    variable_entry* current = environment;

    while(current)
    {
        variable_entry* next = current->next;

        free(current->name);

        free(current);

        current = next;
    }

    environment = NULL;
}

static int evaluate_expression(ast_node* node, int* out_value);

static int execute_statement(ast_node* node)
{
    switch(node->type)
    {
        case ast_variable_declaration:
        {
            int value;

            if(!evaluate_expression(node->variable_declaration.value, &value))
            {
                fprintf(stderr, "evaluating initializer for variable '%s' failed\n!", node->variable_declaration.name);

                return 0;
            }

            set_environment(node->variable_declaration.name, value);
            return 1;
        }   
        
        case ast_print_statement:
        {
            int value;

            if(!get_environment(node->print_statement.name, &value))
            {
                fprintf(stderr, "undefined variable '%s' is in print statment", node->print_statement.name);

                return 0;
            }
            printf("%d\n", value);

            return 1;
        }

        default:
                fprintf(stderr, "unknown statement type: %d\n", node->type);
                return 0;
    }
}

static int evaluate_expression(ast_node* node, int* out_value)
{
    switch(node->type)
    {
        case ast_int_literal:
                            *out_value = node->integer_value;
                            return 1;
        case ast_identifier:
        {
            if(!get_environment(node->identifier, out_value))
            {
                fprintf(stderr, "undefined variable '%s'\n", node->identifier);
                return 0;
            }
            return 1;
        }

        case ast_binary_operator:
        {
            int left_side_operand, right_side_operand;
            
            if(!evaluate_expression(node->binary_expression.left, &left_side_operand)
            || !evaluate_expression(node->binary_expression.right, &right_side_operand))
            {
                return 0;
            }

            switch(node->binary_expression.operator_type)
            {
                case op_add:
                            *out_value = left_side_operand + right_side_operand;
                            break;
                case op_sub:
                            *out_value = left_side_operand - right_side_operand;
                            break;
                case op_mul:
                            *out_value = left_side_operand * right_side_operand;
                            break;
                case op_div:
                {
                    if(right_side_operand == 0)
                    {
                        fprintf(stderr, "division by zero gives undefined result!\n");
                        return 0;
                    }
                    *out_value = left_side_operand / right_side_operand;
                    break;
                }

                default:
                        fprintf(stderr, "unknown binary operator! %d\n", node->binary_expression.operator_type);
                        return 0;
            }
            return 1;
        }

        default:
                fprintf(stderr, "unknown expression type! %d\n", node->type);
                return 0;
    }
}

int interpret(ast_node** statements, int count)
{
    int success = 1;

    for(int i = 0; i < count; ++i)
    {
        if(!execute_statement(statements[i]))
        {
            success = 0;
            break;  
        }
    }
    free_environment();

    return success ? 1 : 0;
}



    

