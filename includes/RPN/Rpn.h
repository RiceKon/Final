#ifndef RPN_H
#define RPN_H

#include <iostream>
#include <stack>
#include <string>
#include <cmath>
#include "../tokenizer/Token.h"
#include "../queue/MyQueue.h"
#include "../stack/MyStack.h"

using namespace std;

class RPN
{
public:
    RPN();
    double evaluate(const Queue<Token> &tokens, double X = 0, double Y = 0);
    

private:
    double applyOperator(const string &op, double a, double b);
    double applyFunction(const string &func, double a);
};



#endif // RPN_H