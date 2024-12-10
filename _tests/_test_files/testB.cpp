#include "gtest/gtest.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <set>
#include <vector>

//------------------------------------------------------------------------------------------
// Files we are testing:

// test

//------------------------------------------------------------------------------------------

using namespace std;

bool test(bool debug = false) {
    return true;
}


TEST(testing, SQLBasic) {
    EXPECT_EQ(test(), true);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}