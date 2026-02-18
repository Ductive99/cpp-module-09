#ifndef RPN_HPP_
#define RPN_HPP_

#include <stack>
#include <string>
#include <iostream>
#include <sstream>

void computeRPN(std::stack<int> &stack, const char *str);

class InsufficientOperandsException : public std::exception {
public:
    const char* what() const throw() {
        return "Error: Not enough operands on the stack.";
    }
};

class InvalidOperandException : public std::exception {
public:
    const char* what() const throw() {
        return "Error: Token is not a valid single-digit integer (0-9).";
    }
};

class TooManyOperandsException : public std::exception {
public:
    const char * what() const throw() {
        return "Error: Incomplete expression, too many operands left.";
    }
};

class EmptyOperationException : public std::exception {
public:
    const char* what () const throw () {
        return "Error: Empty operation.";
    }
};

#endif /* RPN_HPP_ */
