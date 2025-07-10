Simple C Interpreter

This project implements a simple interpreted programming language in C, including:

    Lexer: Tokenizes source code into tokens

    Parser: Converts tokens into an Abstract Syntax Tree (AST)

    AST: Represents language constructs (variables, expressions, print statements)

    Interpreter: Evaluates AST nodes and executes statements with a simple environment

    Tests: Basic test suite verifying arithmetic, variable declarations, and printing

Features

    Variable declarations and assignments

    Integer arithmetic with operator precedence (+, -, *, /)

    Print statements for output

    Basic error handling for undefined variables and division by zero

Project Structure
```bash
    include/      # Header files
    src/          # Source files (lexer, parser, interpreter, AST)
    test/         # Test files for interpreter
    Makefile      # Build automation
```

Build and Run

To compile and run tests:

```bash
    make
    ./test_interpreter
```

To clean build artifacts:
```bash
    make clean
```

Future Improvements

    Expand parser to support more syntax

    Add functions, conditionals, and loops

    Improve error reporting

    Add automated assertions and more test coverage

Usage Example

Here is an example of a small program written in this language:
```plain text
    let x = 10 + 5 * 2;
    let y = x - 4 / 2;
    print(x);
    print(y);
```

This program declares two variables x and y, performs arithmetic operations respecting operator precedence, and prints their values.

Running this program

    1.Tokenize and parse the source code into an AST (handled by your lexer and parser).

    2.Interpret the AST:
                        // Construct AST nodes (example in test_interpreter.c)
                            ast_node* stmts[] = {
                                    // let x = 10 + 5 * 2;
                                    create_variable_declaration("x", 
                                    create_binary_expression(op_add,
                                    create_integer_literal(10),
                                    create_binary_expression(op_mul,
                                    create_integer_literal(5),
                                    create_integer_literal(2)))),
                                    // let y = x - 4 / 2;
                                    create_variable_declaration("y", 
                                    create_binary_expression(op_sub,
                                    create_identifier("x"),
                                    create_binary_expression(op_div,
                                    create_integer_literal(4),
                                    create_integer_literal(2)))),
                                    // print(x);
                                    create_print_statement("x"),
                                    // print(y);
                                    create_print_statement("y")
                        };
                                    interpret(stmts, 4);

                        3.Output:
                                   === Running Complex Interpreter Test ===

                                   Test: complex expression and multiple statements
                                   
                                   Expected output: 20 18
                                   
                                   Actual output: 20 18

            
