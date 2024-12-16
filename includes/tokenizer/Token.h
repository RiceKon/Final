#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <iostream>

using namespace std;

class Token
{
public:
    enum Type
    {
        Number,
        Operator,
        Parenthesis,
        Function,
        Variable,
        Equal,
        Void
    };

    Token() : value_("")
    {
        type_ = Void;
    }
    Token(const string &value) : value_(value)
    {
        if (value == "+" || value == "-" || value == "*" || value == "/" || value == "^")
        {
            type_ = Operator;
            isLeftassociative_ = (value != "^");
        }
        else if (value == "(" || value == ")")
        {
            type_ = Parenthesis;
        }
        else if (value == "x" || value == "y")
        {
            type_ = Variable;
        }else if (value == "=")
        {
            type_ = Equal;
        }
        else if (value == "sin" || value == "cos" || value == "tan" ||
                 value == "csc" || value == "sec" || value == "cot" ||
                 value == "sinh"|| value == "cosh"|| value == "tanh"||
                 value == "log" || value == "ln"  || value == "sqrt"||
                 value == "pi"  || value == "e"   || value == "phi" ||
                 value == "abs" || value == "exp" ||
                 value == "arcsinh" || value == "arccosh" || value == "arctanh" ||
                 value == "arcsin"  || value == "arccos"  || value == "arctan"  ||
                 value == "log_" || value == "root_")
        {
            type_ = Function;
            isLeftassociative_ = false;
        }
        else
        {
            type_ = Number;
        }
    }
    
    Token complementary() const
    {
        if (value_ == "+")
            return Token("-");
        if (value_ == "-")
            return Token("+");
        if (value_ == "*")
            return Token("/");
        if (value_ == "/")
            return Token("*");
        if (value_ == "^")
            return Token("^");
        return Token();
    }


    Type getType() const { return type_; }
    string getValue() const { return value_; }
    bool isLeftAssociative() const { return isLeftassociative_; }

    bool isNumber() const { return type_ == Token::Number; }
    bool isOperator() const { return type_ == Token::Operator; }
    bool isParenthesis() const { return type_ == Token::Parenthesis; }
    bool isFunction() const { return type_ == Token::Function; }
    bool isVariable() const { return type_ == Token::Variable; }
    bool isEqual() const { return type_ == Token::Equal; }
    

    friend ostream &operator<<(ostream &outs, const Token &printMe)
    {
        outs << printMe.value_;
        return outs;
    }

private:
    Type type_;
    string value_;
    bool isLeftassociative_;
};

#endif // TOKEN_H