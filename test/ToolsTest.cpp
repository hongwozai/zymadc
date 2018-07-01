#include <cstdio>
#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Tools.h"
using namespace std;
using namespace zymadc::Tools;

TEST(tools, bitset)
{
    char bit[10] = {0};

    BitSet(&bit, 1);
    EXPECT_TRUE(BitCheck(&bit, 1));
    EXPECT_FALSE(BitCheck(&bit, 2));
    BitUnset(&bit, 1);
    EXPECT_FALSE(BitCheck(&bit, 1));
}