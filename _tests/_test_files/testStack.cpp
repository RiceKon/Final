#include "gtest/gtest.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <set>
#include <vector>

//------------------------------------------------------------------------------------------
// Files we are testing:
#include "../../includes/stack/MyStack.h"
// #include "../../includes/queue/Queue.h"
// test

//------------------------------------------------------------------------------------------

using namespace std;

bool TestStack(bool debug = 1) {
    Stack<int> s;
    for(int i = 0; i < 10; i++){
        s.push(i);
    }
    
    if(debug){
        cout << s << endl;
    }

    for(int i = 9; i >= 0; i--){
        if(s.top() != i){
            cout << "s.top() != "<< i << "it s.top() =" << s.top() << endl;
            return false;
        }
                if(debug){cout << s << endl;}
        s.pop();
    }
    
    if(!s.empty()){
        cout << "s is not empty" << endl;
        return false;
    }
    
    return true;
}



TEST(Stack, SQLBasic) {
    EXPECT_EQ(TestStack(), 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}