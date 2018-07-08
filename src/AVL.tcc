/*************************************************
 ** Copyright(c) 2018, luzeya
 ** All rights reserved
 **
 ** 文件名：AVL.tcc
 ** 创建人：zeya
 ** 创建日期： 2018-07-08
 **
 ** 描  述：1.
 ** 注  意：1.当没有树高的属性时，需要根据平衡因子进行判断。
 **          插入节点时，平衡因子趋向于0,则该子树树高不变
 **                    平衡因子远离0,则该子树树高增加或减少
                       当旋转时，旋转后树高比旋转前树高少1层
                               而跟不插入节点时的高度是一样的
 **************************************************/
#include <iostream>
#include <stack>
#include <cassert>
#include "AVL.h"

/**
 * 插入分两大步
 * 1. 查找到应该插入的地方
 * 2. 插入后，逐步向上平衡
 */
template <class Key>
void AVL<Key>::insert(Key key)
{
    Node *beinsert = NULL;
    Node *p = root;
    // 向上平衡时，子节点的方向。true是左，false是右
    bool dirent;

    // 查找插入的地方
    while (p) {
        if (key > p->key) {
            beinsert = p;
            p = p->right;
        } else if (key < p->key) {
            beinsert = p;
            p = p->left;
        } else {
            p->key = key;
            return;
        }
    }

    // beinsert现在为被插入的点。
    p = new Node(NULL, NULL, beinsert, 0, key);
    if (!beinsert) {
        // beinsert为空，树为空
        root = p;
        return;
    } else if (key > beinsert->key) {
        beinsert->right = p;
        dirent = false;
    } else {
        beinsert->left = p;
        dirent = true;
    }

    // 向上平衡
    p = beinsert;
    while (p) {
        // 判断平衡因子的绝对值变大还是变小
        // 变小则不向上回溯，变大则继续回溯，找平衡
        bool isabsdec = (dirent)
            // +1
            ? ((p->bf >= 0) ? false : true)
            // -1
            : ((p->bf <= 0) ? false : true);

        p->bf += (dirent) ? 1 : -1;

        // NOTE: 当平衡值的绝对值变小时，树是平衡的，不在回溯
        if (isabsdec) { return; }

        // 判断当前节点是其父节点的那个孩子
        if (p->parent) {
            dirent = (p == p->parent->left) ? true : false;
        }

        switch (p->bf) {
        case 0:
        case -1:
        case 1:
            // 当前暂时平衡，继续向上回溯
            break;

            // 不平衡
        case -2:
            // 右
            assert(p->right);
            assert(p->right->bf != 0);

            if (p->right->bf == 1) {
                // 右左
                p = leftRightRotate(p);
            } else {
                // 右右
                p = leftRotate(p);
            }
            // 根节点变更
            if (p->parent)
                if (dirent) p->parent->left = p;
                else        p->parent->right = p;
            else
                root = p;
            return;

        case 2:
            // 左
            assert(p->left);
            assert(p->left->bf != 0);

            if (p->left->bf == 1) {
                // 左左
                p = rightRotate(p);
            } else {
                // 左右
                p = rightLeftRotate(p);
            }

            // 根节点变更
            if (p->parent)
                if (dirent) p->parent->left = p;
                else p->parent->right = p;
            else
                root = p;
            return;

        default:
            assert(!"[insert] bf value error!");
        }

        p = p->parent;
    }
}

template <class Key>
void AVL<Key>::del(Key key)
{
    bool isfound = false;

    Node *p = root;
    // 被删节点的父节点(也是向上平衡时的开始节点)
    Node *bedel = NULL;
    Node **temp;
    // 方向，左true，右false
    bool dirent;

    if (!root)
        return;

    // 查找删除的地方
    while (p) {
        if (key > p->key) {
            bedel = p;
            dirent = false;
            p = p->right;
        } else if (key < p->key) {
            bedel = p;
            dirent = true;
            p = p->left;
        } else {
            p->key = key;
            isfound = true;
            break;
        }
    }

    if (!isfound)
        return;

    /**
     * 找到节点，分三种情况来分析
     * 1. 该节点无孩子
     * 2. 该节点一个孩子
     * 3. 该节点两个孩子，删除后，找孩子进行替代
     */
    temp = (bedel)
        ? (dirent) ? &bedel->left : &bedel->right
        : &root;
    if (p->left == NULL || p->right == NULL) {
        // 都为空，或者其中一个为空
        if (p->left == NULL) {
            *temp = p->right;
        } else if (p->right == NULL) {
            *temp = p->left;
        }
        if (*temp)
            (*temp)->parent = bedel;
        delete p;
    } else {
        /**
         * 两个孩子
         */
        Node *max;

        max = p->left;
        while (max->right) {
            max = max->right;
        }
        // 替换
        p->key = max->key;
        if (max == p->left) {
            max->parent->left = max->left;
            dirent = true;
        } else {
            max->parent->right = max->left;
            dirent = false;
        }
        if (max->left)
            max->left->parent = max->parent;

        bedel = max->parent;
        delete max;
    }

    // 开始向上平衡
    p = bedel;
    while (p) {

        /**
         * 删除时，
         * 树高没变的情况下，平衡值在[-1,1]间，树都是平衡的，不必再次回溯
         */
        p->bf += (dirent) ? -1 : 1;

        // 判定树高没变
        // if (p->bf == 0 || p->bf == 1 || p->bf == -1)
        //     return;

        // 判断当前节点是其父节点的那个孩子
        if (p->parent) {
            dirent = (p == p->parent->left) ? true : false;
        }

        switch (p->bf) {
        case 0:
            // 树高变了
            // 因子从-1或1到0
            break;
        case -1:
        case 1:
            // 树高没变，平衡值在-1,1之间，停止回溯
            // 因子从0到-1或1
            return;

        case -2:
            // 右
            assert(p->right);
            // assert(p->right->bf != 0);

            if (p->right->bf == 1) {
                // 右左(树高变化)
                p = leftRightRotate(p);
            } else if (p->right->bf == -1) {
                // 右右(树高变化)
                p = leftRotate(p);
            } else {
                // 删除时，比增加多一种情况
                // 这种情况下，树高不变，不再回溯
                p = leftRotate(p);
                p->bf = 1;
                p->left->bf = -1;

                // 根节点变更
                // TODO: 代码重复，考虑怎么去掉
                if (p->parent)
                    if (dirent) p->parent->left = p;
                    else        p->parent->right = p;
                else
                    root = p;
                return;
            }
            // 根节点变更
            if (p->parent)
                if (dirent) p->parent->left = p;
                else        p->parent->right = p;
            else
                root = p;
            break;

        case 2:
            // 左
            assert(p->left);
            // assert(p->left->bf != 0);

            if (p->left->bf == 1) {
                // 左左(树高变化)
                p = rightRotate(p);
            } else if (p->left->bf == -1) {
                // 左右(树高变化)
                p = rightLeftRotate(p);
            } else {
                // 删除时，比增加多一种情况
                // 这种情况下，树高不变，不再回溯
                p = rightRotate(p);
                p->bf = -1;
                p->right->bf = 1;

                // 根节点变更
                if (p->parent)
                    if (dirent) p->parent->left = p;
                    else p->parent->right = p;
                else
                    root = p;
                return;
            }

            // 根节点变更
            if (p->parent)
                if (dirent) p->parent->left = p;
                else p->parent->right = p;
            else
                root = p;
            break;

        default:
            assert(!"[del] bf value error");
        }

        p = p->parent;
    }
}

template <class Key>
typename AVL<Key>::Node *AVL<Key>::rightRotate(Node *root)
{
    Node *left = root->left;

    assert(root);
    assert(left);

    root->left   = left->right;
    if (root->left) root->left->parent = root;
    left->right  = root;

    left->parent = root->parent;
    root->parent = left;

    root->bf = 0;
    left->bf = 0;
    return left;
}

template <class Key>
typename AVL<Key>::Node *AVL<Key>::leftRotate(Node *root)
{
    Node *right = root->right;

    assert(root);
    assert(right);

    root->right  = right->left;
    if (root->right) root->right->parent = root;
    right->left  = root;

    right->parent = root->parent;
    root->parent = right;

    root->bf = 0;
    right->bf = 0;
    return right;
}

template <class Key>
typename AVL<Key>::Node *AVL<Key>::rightLeftRotate(Node *root)
{
    Node *left = root->left;
    Node *subright = left->right; // 节点一定存在

    left->right = subright->left;
    if (left->right) left->right->parent = left;
    subright->left = left;
    left->parent = subright;

    root->left = subright->right;
    if (root->left) root->left->parent = root;
    subright->right = root;
    subright->parent = root->parent;
    root->parent = subright;

    switch (subright->bf) {
    case 0:
        subright->bf = 0;
        root->bf = 0;
        left->bf = 0;
        break;
    case -1:
        subright->bf = 0;
        left->bf = 1;
        root->bf = 0;
        break;
    case 1:
        subright->bf = 0;
        left->bf = 0;
        root->bf = -1;
        break;
    }
    return subright;
}

template <class Key>
typename AVL<Key>::Node *AVL<Key>::leftRightRotate(Node *root)
{
    Node *right = root->right;
    Node *subleft = right->left; // 节点一定存在

    right->left = subleft->right;
    if (right->left) right->left->parent = right;

    subleft->right = right;
    right->parent = subleft;

    root->right = subleft->left;
    if (root->right) root->right->parent = root;

    subleft->left = root;
    subleft->parent = root->parent;
    root->parent = subleft;

    switch (subleft->bf) {
    case 0:
        subleft->bf = 0;
        right->bf = 0;
        root->bf = 0;
        break;
    case -1:
        subleft->bf = 0;
        right->bf = 0;
        root->bf = 1;
        break;
    case 1:
        subleft->bf = 0;
        right->bf = -1;
        root->bf = 0;
        break;
    }
    return subleft;
}

template <class Key>
void AVL<Key>::debugPrint()
{
    using namespace std;
    typedef pair<Node*, int> pair;

    stack<pair> stack;

    // 中序遍历 (0需要遍历，1只需要打印)
    stack.push(pair(root, 0));
    while (!stack.empty()) {
        pair p = stack.top();
        stack.pop();

        if (!p.first) {
            continue;
        }
        switch(p.second) {
        case 0:
            stack.push(pair(p.first->right, 0));
            stack.push(pair(p.first, 1));
            stack.push(pair(p.first->left, 0));
            break;
        case 1:
            cout << p.first->key << ", ";
            break;
        }
    }
    cout << endl;
}

template <class Key>
int AVL<Key>::height(Node *root)
{
    if (!root)
        return 0;
    int lhs = height(root->left);
    int rhs = height(root->right);
    return ((lhs > rhs) ? lhs : rhs) + 1;
}

template <class Key>
int AVL<Key>::height()
{
    return height(root);
}

template <class Key>
bool AVL<Key>::checkHeight()
{
    return checkHeight(root);
}

template <class Key>
bool AVL<Key>::checkHeight(Node *root)
{
    if (!root)
        return true;
    if (!checkHeight(root->left))
        return false;
    if (!checkHeight(root->right))
        return false;

    int cha = height(root->left) - height(root->right);
    return (cha == 0 || cha == -1 || cha == 1);
}

template <class Key>
bool AVL<Key>::checkSort()
{
    using namespace std;
    typedef pair<Node*, int> pair;

    int min = 0x80000001 - 1;
    stack<pair> stack;

    // 中序遍历 (0需要遍历，1只需要打印)
    stack.push(pair(root, 0));
    while (!stack.empty()) {
        pair p = stack.top();
        stack.pop();

        if (!p.first) {
            continue;
        }
        switch(p.second) {
        case 0:
            stack.push(pair(p.first->right, 0));
            stack.push(pair(p.first, 1));
            stack.push(pair(p.first->left, 0));
            break;
        case 1:
            if (p.first->key <= min) {
                // 顺序不对失败
                return false;
            }
            min = p.first->key;
            break;
        }
    }
    return true;
}