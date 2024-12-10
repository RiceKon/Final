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
  std::cout<<"\n\n----------running testB.cpp---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}