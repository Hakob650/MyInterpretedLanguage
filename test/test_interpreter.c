#include <stdio.h>
#include "../include/interpreter.h"
#include "../include/ast.h"

void test_complex_expression() {
    // let x = 10 + 5 * 2;   // x = 10 + (5*2) = 20
    ast_node* mult_expr = create_binary_expression(op_mul,
                                create_integer_literal(5),
                                create_integer_literal(2));
    ast_node* add_expr = create_binary_expression(op_add,
                               create_integer_literal(10),
                               mult_expr);
    ast_node* let_x = create_variable_declaration("x", add_expr);

    // let y = x - 4 / 2;   // y = 20 - (4/2) = 18
    ast_node* div_expr = create_binary_expression(op_div,
                               create_integer_literal(4),
                               create_integer_literal(2));
    ast_node* sub_expr = create_binary_expression(op_sub,
                               create_identifier("x"),
                               div_expr);
    ast_node* let_y = create_variable_declaration("y", sub_expr);

    // print(x);  // expect 20
    ast_node* print_x = create_print_statement("x");

    // print(y);  // expect 18
    ast_node* print_y = create_print_statement("y");

    ast_node* stmts[] = { let_x, let_y, print_x, print_y };

    printf("Test: complex expression and multiple statements\nExpected output:\n20\n18\nActual output:\n");
    interpret(stmts, 4);
}

int main() {
    printf("=== Running Complex Interpreter Test ===\n\n");
    test_complex_expression();
    return 0;
}

