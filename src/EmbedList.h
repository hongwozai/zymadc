/*************************************************
 ** Copyright(c) 2018, luzeya
 ** All rights reserved
 **
 ** 文件名：EmbedList.h
 ** 创建人：zeya
 ** 创建日期： 2018-07-01
 **
 ** 描  述：嵌入式的链表
 ** 注  意：1. 该链表输入嵌入方式，参考linux内核链表
           2. 由于使用了模板进行类型转换和内存在外申请，
              内存方面的错误还有使用方面的错误容易在
              该链表中显现出来
           3. 由于无法分辨该节点是否为该链表中的节点，摘下
              节点时，最容易出现错误。出现错误时，调试可以
              使用check函数进行检查，之后再去掉该函数
 **************************************************/
#ifndef EMBEDLIST_H
#define EMBEDLIST_H

namespace zymadc {
    struct EmbedListLink;
    template <class Type> class EmbedList;
}

struct zymadc::EmbedListLink {
    EmbedListLink *prev;
    EmbedListLink *next;

    EmbedListLink() : prev(0), next(0) {}
};

template <class T>
class zymadc::EmbedList
{
public:

    typedef EmbedListLink Link;

public:

    EmbedList(int offset = 0)
        : head(0), tail(0), len(0), offset(offset) {}

    void attach(Link *node, T *data);

    void detach(Link *node);

    T*   containerOf(Link *data) {
        return (T*)((char*)data - offset);
    }

    void append(T *data) {
        if (data) attach(tail, data);
    }

    void push(T   *data) {
        if (data) attach(0, data);
    }

    void del(T    *data) {
        Link *temp = (Link*)((char*)data + offset);
        if (data && (temp->prev != 0 || temp->next != 0))
            detach(temp);
    }

    T*    pop() {
        if (!len) return 0;
        else {
            T* ret = containerOf(head);
            detach(head);
            return ret;
        }
    }

    T*    popBack() {
        if (!len) return 0;
        else {
            T* ret = containerOf(tail);
            detach(tail);
            return ret;
        }
    }

    T*    first() { return head ? containerOf(head) : 0; }

    T*    end() { return tail ? containerOf(tail) : 0; }

    bool  empty() { return (head == 0); }

    // 返回节点是否是该链表中（调试使用）
    bool check(T *data);

public:

    Link *head;

    Link *tail;

    int   len;

    int   offset;
};

template <class T>
void zymadc::EmbedList<T>::attach(Link *node, T* data)
{
    Link *temp = (Link*)((char*)data + offset);

    temp->prev = node;
    temp->next = (node == 0) ? head : node->next;
    if (temp->prev == 0) head = temp;
    else                 temp->prev->next = temp;
    if (temp->next == 0) tail = temp;
    else                 temp->next->prev = temp;
    ++len;
}

template <class T>
void zymadc::EmbedList<T>::detach(Link *node)
{
    if (node->prev == 0) head = node->next;
    else                 node->prev->next = node->next;
    if (node->next == 0) tail = node->prev;
    else                 node->next->prev = node->prev;
    --len;

    // set point to 0
    node->prev = 0;
    node->next = 0;
}

template <class T>
bool zymadc::EmbedList<T>::check(T* data)
{
    Link *temp = (Link*)((char*)data + offset);
    Link *iter = head;
    for (iter = head; iter != 0; iter = iter->next) {
        if (iter == temp)
            return true;
    }
    return false;
}

#endif /* EMBEDLIST_H */
