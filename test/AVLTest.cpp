#include <cstdlib>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "AVL.tcc"


TEST(avl, insert_short)
{
    AVL<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(6);
    tree.insert(2);
    tree.insert(4);
    tree.debugPrint();
    EXPECT_EQ(3, tree.height());
    EXPECT_TRUE(tree.checkHeight());
    EXPECT_TRUE(tree.checkSort());
}

TEST(avl, insert2)
{
    AVL<int> tree;
    tree.insert(10889);
    tree.insert(121);
    tree.insert(6490);
    tree.insert(8283);
    tree.insert(11924);
    tree.debugPrint();
    EXPECT_EQ(tree.height(), 3);
    EXPECT_TRUE(tree.checkHeight());
    EXPECT_TRUE(tree.checkSort());
}

// 左右
TEST(avl, insert3)
{
    AVL<int> tree;
    tree.insert(221);
    tree.insert(1790);
    tree.insert(585);
    tree.insert(840);
    tree.insert(1349);
    tree.debugPrint();
    EXPECT_EQ(tree.height(), 3);
    EXPECT_TRUE(tree.checkHeight());
    EXPECT_TRUE(tree.checkSort());
}

TEST(avl, insert4)
{
    AVL<int> tree;
    tree.insert(568);
    tree.insert(559);
    tree.insert(931);
    tree.insert(241);
    tree.insert(382);
    tree.insert(62);
    EXPECT_EQ(tree.height(), 3);
    tree.insert(179);
    EXPECT_EQ(tree.height(), 3);
    tree.insert(929);
    tree.insert(675);
    tree.insert(498);
    tree.insert(762);
    tree.insert(29);
    tree.debugPrint();
    EXPECT_TRUE(tree.checkHeight());
    EXPECT_TRUE(tree.checkSort());
}

TEST(avl, insert5)
{
    AVL<int> tree;
    tree.insert(230);
    tree.insert(64);
    tree.insert(924);
    EXPECT_EQ(tree.height(), 2);
    tree.insert(746);
    tree.insert(377);
    tree.insert(365);
    EXPECT_EQ(tree.height(), 3);
    tree.insert(920);
    EXPECT_EQ(tree.height(), 3);
    tree.insert(295);
    tree.insert(857);
    tree.debugPrint();
    EXPECT_TRUE(tree.checkHeight());
    EXPECT_TRUE(tree.checkSort());
}

TEST(avl, insert6)
{
    AVL<int> tree;
    tree.insert(313);
    tree.insert(429);
    tree.insert(449);
    tree.insert(435);
    tree.insert(142);
    tree.insert(195);
    tree.insert(784);
    tree.insert(532);
    tree.insert(455);
    tree.insert(511);
    EXPECT_TRUE(tree.checkHeight());
    EXPECT_TRUE(tree.checkSort());
}

TEST(avl, insert7)
{
    AVL<int> tree;
    tree.insert(618);
    tree.insert(794);
    tree.insert(369);
    EXPECT_EQ(2, tree.height());
    tree.insert(519);
    tree.insert(430);
    tree.insert(589);
    tree.insert(149);
    EXPECT_EQ(3, tree.height());
    EXPECT_TRUE(tree.checkHeight());
    EXPECT_TRUE(tree.checkSort());
}

TEST(avl, insert8)
{
    AVL<int> tree;
    tree.insert(295);
    tree.insert(106);
    tree.insert(555);
    tree.insert(579);
    tree.insert(192);
    tree.insert(868);
    tree.insert(727);
    tree.insert(768);
    tree.insert(959);
    tree.insert(739);
    EXPECT_TRUE(tree.checkHeight());
    EXPECT_TRUE(tree.checkSort());
}

TEST(avl, insert9)
{
    AVL<int> tree;
    tree.insert(962);
    tree.insert(687);
    tree.insert(985);
    tree.insert(433);
    tree.insert(610);
    tree.insert(650);
    tree.insert(291);
    tree.insert(651);
    tree.insert(933);
    EXPECT_TRUE(tree.checkHeight());
    EXPECT_TRUE(tree.checkSort());
}

TEST(avl, insert_many)
{
    using namespace std;
    AVL<int> tree;
    srand(time(0));

    for (int i = 0; i < 10000; i++) {
        int a = rand();
        tree.insert(a);
        ASSERT_TRUE(tree.checkHeight());
        ASSERT_TRUE(tree.checkSort());
    }

}
