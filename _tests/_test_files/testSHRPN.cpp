#include "gtest/gtest.h"
#include <iostream>
#include <set>
#include <vector>

using namespace std;

//------------------------------------------------------------------------------------------
// Files we are testing:
// #include "../../includes/stack/Stack.h"
#include "../../includes/SY/SY.h"
#include "../../includes/RPN/Rpn.h"
// test

//------------------------------------------------------------------------------------------


using namespace std;


bool testRPN(bool debug = false) {
    RPN rpn;
    Queue<Token> q;
    q.push(Token("3"));
    q.push(Token("5"));
    q.push(Token( "+"));
    q.push(Token("2"));
    q.push(Token("*"));
    q.push(Token("4"));
    q.push(Token("3"));
    q.push(Token("-"));
    q.push(Token("/"));
    double result = rpn.evaluate(q);

    if (debug) {
        cout << "RPN Result: " << result << endl;
    }
    return fabs(result - 16.0) < 1e-5; // ((3 + 5) * 2) / (4 - 3) = 16
}
bool testSY(bool debug = false) {
    SY shuntingYard;
    Queue<Token> tokens;
    tokens.push(Token("("));
    tokens.push(Token("3"));
    tokens.push(Token("+"));
    tokens.push(Token("5"));
    tokens.push(Token(")"));
    tokens.push(Token("*"));
    tokens.push(Token("2"));
    tokens.push(Token("/"));
    tokens.push(Token("("));
    tokens.push(Token("4"));
    tokens.push(Token("-"));
    tokens.push(Token("3"));
    tokens.push(Token(")"));

    Queue<Token> rpn = shuntingYard.convertToRPN(tokens);

    vector<string> expected = {"3", "5", "+", "2", "*", "4", "3", "-", "/"};
    if (debug){
        cout << "RPN: " << rpn << endl;;
    }
    for (const auto& exp : expected) {
        if (rpn.empty()) return false;
        Token token = rpn.pop();
        if (token.getValue() != exp) return false;
    }
    return rpn.empty();
}


// TEST(TESTRPN, TESTrpn) {
//     EXPECT_EQ(testRPN(1), true);
// }

// TEST(TESTSY, TESTsy) {
//     EXPECT_EQ(testSY(1), true);
// }


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}