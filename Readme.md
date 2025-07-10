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

