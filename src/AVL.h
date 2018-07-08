/*************************************************
 ** Copyright(c) 2018, luzeya
 ** All rights reserved
 **
 ** 文件名：AVL.h
 ** 创建人：zeya
 ** 创建日期： 2018-07-07
 **
 ** 描  述：1.
 ** 注  意：
 **************************************************/
#ifndef AVL_H
#define AVL_H

template <class Key>
class AVL
{
public:

    AVL() : root(0) {}

    // 插入
    void insert(Key key);

    // 删除
    void del(Key key);

    // 查找
    Key find(Key key);

    // 清除所有节点
    void clear();

    // Height
    int height();

    // NOTE: (debug) height
    bool checkHeight();

    // NOTE: (debug) orderring
    bool checkSort();

    // NOTE: (debug) print
    void debugPrint();

private:

    struct Node {
        Node *left;
        Node *right;
        Node *parent;
        Key   key;
        // balance factor
        // bf = height(left) - height(right)
        int   bf;

        Node(Node *left, Node *right,
             Node *parent, int bf,
             Key key)
            : left(left),
              right(right),
              parent(parent),
              key(key),
              bf(bf)
        {}
    };

private:

    // 四种旋转
    // NOTE: 这几种旋转都会使当前的树比之前的高度-1
    Node *leftRotate(Node *);
    Node *rightRotate(Node *);
    Node *leftRightRotate(Node *);
    Node *rightLeftRotate(Node *);

    // 高度内部函数
    int height(Node *);
    bool checkHeight(Node *);

private:

    Node *root;
};

#endif /* AVL_H */