#include "SY.h"

SY::SY() {}

int SY::getPrecedence(const Token &token)
{
    if (token.isOperator())
    {
        if (token.getValue() == "+" || token.getValue() == "-")
            return 1;
        if (token.getValue() == "*" || token.getValue() == "/")
            return 2;
        if (token.getValue() == "^")
            return 3;
    }
    else if (token.isFunction())
    {
        return 4;
    }

    return 0;
}

Queue<Token> SY::convertToRPN(const Queue<Token> &infix, bool hadEqual)
{
    Stack<Token> operators;
    Queue<Token> result;

    Queue<Token> tokenQueue = (hadEqual) ? isolate(infix) : infix;

    cout << tokenQueue << endl;
    while (!tokenQueue.empty()) {
        Token token = tokenQueue.pop();
        Token top = operators.empty() ? Token() : operators.top();
        // treat numbers and variables as the same
        if (token.isNumber() || token.isVariable()) {
            result.push(token);
        } 
        else if (token.isOperator() || token.isFunction()) {
            pushOperator(operators, result, token);
        } 
        else if (token.getValue() == "(") {
            operators.push(token);
        } 
        else if (token.getValue() == ")") {
            while (!operators.empty() && top.getValue() != "(") {
                result.push(operators.pop());
                top = operators.empty() ? Token() : operators.top();
            }
            operators.pop(); // Pop the '('
            if (!operators.empty() && (top.isOperator() || top.isFunction())) {
                result.push(operators.pop());
            }
        }
    }


    while (!operators.empty()) {
        result.push(operators.pop());
    }

    return result;
}

Queue<Token> SY::isolate(const Queue<Token> &infix)    // if infix has an "=" operator, move the equations into the RHS where it is 0 = LHS - RHS
{                                            // exmaple if the equation is x + 2y = y, the result of this function will be y - x - 2y
    cout << infix << endl;
    Token token;
    Queue<Token> temp = infix, result;
    while (!temp.empty()) {
        token = temp.pop();
        cout << token << endl;
        if(token.isEqual()){
            result.push(Token("-"));
            result.push(Token("("));
        }else{
            result.push(token);
        }
    }
    
    result.push(Token(")"));
    return result;
}

void SY::pushOperator(Stack<Token> &operators, Queue<Token> &result, Token token){
    Token top = operators.empty() ? Token() : operators.top();
    while (!operators.empty() && (top.isOperator() || top.isFunction()) &&
        ((token.isLeftAssociative() && getPrecedence(token) <= getPrecedence(top)) ||
        (!token.isLeftAssociative() && getPrecedence(token) < getPrecedence(top))))
    {
        result.push(operators.pop());
    }
    operators.push(token);
}