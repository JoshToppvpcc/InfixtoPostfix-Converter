#pragma once
#include <iostream>
#include <stack>
#include <string>
#include <cctype>  

class Converter {
private:
    std::string postfix;  // Holds the converted postfix expression

    // Assign precedence values to operators
    int precedence(char op) {
        if (op == '+' || op == '-') {
            return 1;
        }
        else if (op == '*' || op == '/') {
            return 2;
        }
        return 0;  // For invalid characters, although not necessary based on the constraints
    }

public:
    // Constructor
    Converter() : postfix("") {}

    // Convert infix to postfix
    void Convert(const std::string& infix) {
        std::stack<char> operatorStack;
        postfix = "";  // Clear any previous postfix expression

        for (char c : infix) {
            if (isalpha(c)) {
                // If the character is an operand (alphabet), add it to the postfix expression
                postfix += c;
            }
            else if (c == '(') {
                // If the character is '(', push it to the stack
                operatorStack.push(c);
            }
            else if (c == ')') {
                // If the character is ')', pop from the stack until '(' is found
                while (!operatorStack.empty() && operatorStack.top() != '(') {
                    postfix += operatorStack.top();
                    operatorStack.pop();
                }
                // Pop the '('
                if (!operatorStack.empty() && operatorStack.top() == '(') {
                    operatorStack.pop();
                }
            }
            else if (c == ' ') {
                // Skip spaces
                continue;
            }
            else {
                // The character is an operator (+, -, *, /)
                while (!operatorStack.empty() && precedence(operatorStack.top()) >= precedence(c)) {
                    postfix += operatorStack.top();
                    operatorStack.pop();
                }
                operatorStack.push(c);
            }
        }

        // Pop any remaining operators from the stack
        while (!operatorStack.empty()) {
            postfix += operatorStack.top();
            operatorStack.pop();
        }
    }

    // Accessor function to get the postfix expression
    std::string getPostfix() const {
        return postfix;
    }
};
