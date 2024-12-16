#include "gtest/gtest.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <set>
#include <vector>

//------------------------------------------------------------------------------------------
// Files we are testing:
// #include "../../includes/stack/Stack.h"
#include "../../includes/queue/MyQueue.h"
// test

//------------------------------------------------------------------------------------------

using namespace std;

bool TestQueue(bool debug = 0) {
    Queue<int> q;
    for(int i = 0; i < 10; i++){
        q.push(i);
    }


    for(int i = 0; i < 10; i++){
        if(q.front() != i){
            cout << "q.front() != "<< i << "q.front() = " << q.front() << endl;
            return false;
        }
        if(debug){cout << q << endl;}        
        q.pop();
    }

    if(!q.empty()){
        return false;
    }
    
    return true;
}

bool TestQueue_EQ(bool debug = 0) {
    Queue<int> q;
    Queue<int> holder;
    for(int i = 0; i < 10; i++){
        q.push(i * 10);
    }
    
    holder = q;

    if(&holder == &q){
        return false;
    }
    if(debug){
        cout << holder << endl;
    }
    
    return true;
}

TEST(Queue, TESTQueue) {
    EXPECT_EQ(TestQueue(0), true);
}

TEST(Queue_eq, TESTQueue_EQ) {
    EXPECT_EQ(TestQueue_EQ(1), true);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}