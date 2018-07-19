#include <cstdio>
#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "AC.h"
#include "config.h"
using namespace std;

const char *words[3] = {
    "123",
    "qwe",
    "asd"
};

TEST(ac, insert)
{
    AC ac;

    ac.confLoad(words, 3);
    ac.build();
    ac.print();
}

TEST(ac, load)
{
    AC ac;
    int ret;
    string str = "23qweasd";
    ac.confLoad((unsigned int (*)[AC::ALPHABET_NUM+1])table);
    ret = ac.search(str.data(), str.size());
    ASSERT_EQ(ret, 1);
}