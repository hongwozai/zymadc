#include <cstdio>
#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "EmbedList.h"
using namespace std;
using namespace zymadc;

struct Node {
    EmbedListLink link;
    int i;
};

TEST(embedlist, attach)
{
    EmbedList<Node> list;
    Node n1; n1.i = 1;
    Node n2; n2.i = 2;
    Node n3; n3.i = 3;
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.len, 0);

    // append
    list.append(&n1);
    list.append(&n2);
    list.append(&n3);
    EXPECT_EQ(3, list.len);
    EXPECT_EQ(list.head, &n1.link);
    EXPECT_EQ(list.tail, &n3.link);

    // del
    list.del(&n1);
    EXPECT_EQ(list.len, 2);
    list.del(&n1);
    list.del(&n1);
    list.del(&n1);
    EXPECT_EQ(list.len, 2);
    EXPECT_FALSE(list.check(&n1));
    EXPECT_TRUE(list.check(&n2));
    EXPECT_TRUE(list.check(&n3));
    EXPECT_EQ(list.first(), &n2);
    EXPECT_EQ(list.end(), &n3);

    list.push(&n1);
    EXPECT_EQ(list.len, 3);
    EXPECT_TRUE(list.check(&n1));

    // first
    EXPECT_EQ(&n1, list.first());
    // end
    EXPECT_EQ(&n3, list.end());
}

TEST(embedlist, detach)
{
    EmbedList<Node> list;
    Node n1; n1.i = 1;
    Node n2; n2.i = 2;
    Node n3; n3.i = 3;
    Node *temp;
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.len, 0);

    // 删除一个prev,next为空的节点
    list.append(&n1);
    EXPECT_EQ(list.len, 1);
    temp = list.pop();
    EXPECT_EQ(temp->link.next, (EmbedListLink*)0);
    EXPECT_EQ(temp->link.prev, (EmbedListLink*)0);
    ASSERT_EQ(list.len, 0);
    list.append(&n2);
    ASSERT_EQ(list.len, 1);
    list.del(&n1);
    ASSERT_EQ(list.len, 1);
    ASSERT_EQ(list.head, &n2.link);
}

TEST(embedlist, push_or_pop)
{
     EmbedList<Node> list;
    Node n1; n1.i = 1;
    Node n2; n2.i = 2;
    Node n3; n3.i = 3;
    Node *temp;

    // single node
    list.push(&n1);
    EXPECT_EQ(list.head, &n1.link);
    EXPECT_EQ(list.len, 1);
    temp = list.pop();
    EXPECT_EQ(list.len, 0);
    EXPECT_EQ(temp, &n1);

    // multi node(mismatch push/pop)
    list.push(&n1);
    list.push(&n2);
    list.push(&n3);
    list.pop();
    list.pop();
    list.pop();
    temp = list.pop();
    EXPECT_EQ(list.len, 0);
    EXPECT_EQ(temp, (Node*)0);
    EXPECT_TRUE(list.empty());

    // append popback
    list.append(&n1);
    list.append(&n2);
    list.append(&n3);
    list.popBack();
    list.popBack();
    EXPECT_EQ(list.len, 1);
    EXPECT_EQ(list.head, &n1.link);
    EXPECT_TRUE(list.check(&n1));
    EXPECT_FALSE(list.check(&n2));
    EXPECT_FALSE(list.check(&n3));

    list.popBack();
    list.popBack();
    EXPECT_EQ(list.len, 0);
    EXPECT_TRUE(list.empty());

    list.append(0);
    EXPECT_EQ(list.len, 0);
    EXPECT_TRUE(list.empty());
}