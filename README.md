# Arithmetic Expressions Parser

This is a C++ program that can parse and evaluate arithmetic expressions. For example, on input 3+(5+(4*3))-12, the program return 8. The program also detect an invalid input and report an appropriate error.

Supported Symbols

    Positive and negative numbers.
    +, -, *, / and parentheses.
    
You can run this code in your favorite compiler or IDE (Visual Studio, Code::Blocks...). You can try to run your expression by modifying the expression toParse and compile!

The code is extensively commentated but to sum up the idea behind the algorithm. The algorithm recursively calls the additionner/substracter. The additioner himself calls the multplier/divider that will return the values of any multiplication/division to be added by the additioner. The multiplier himself calls the factorizer to detect which expression or number to multiply, the factorizer returns the number to be multiplied, or call recursively the additionner when an open bracket '(' is detected and deal with the expression between brackets the same way described before until there is no more expressions between brackets, then it will be a matter of simple arithmetic operations.

As for errors, the program detects many invalid inputs that you can try such as:
- Characters that are nor digits, operators or brackets. But it handles empty spaces.
- Dividing by either a litteral zero or by an expression equals to zero.
- The presence of two operators consecutively in the expression like '+)' or '*/'.
- the presence of a closing bracket before an opening bracket.
