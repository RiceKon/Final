#ifndef SY_H
#define SY_H

#include <iostream>
#include <vector>
#include <string>
#include "../stack/MyStack.h"
#include "../queue/MyQueue.h"
#include "../tokenizer/Token.h"
#include "../RPN/Rpn.h"

using namespace std;

class SY
{
public:
    SY();
    Queue<Token> convertToRPN(const Queue<Token> &infix, bool hadEqual = false);

private:
    int getPrecedence(const Token &token);      // get the precedence of an operator

    void pushOperator(Stack<Token> &operators, Queue<Token> &result, Token token);     // push an operator to the operator stack

    Queue<Token> isolate(const Queue<Token> &infix);    // move the equations into the RHS where it is 0 = RHS - LHS

    double numericalSolve(double x, double initialGuess, Queue<Token>& LHS, Queue<Token>& RHS);   // if equation is y + x = ln(x), numerically solve


};

#endif // SY_H