/********************************************************************
 ** Copyright(c) 2016, luzeya
 ** All rights reserved
 **
 ** 文件名：AC.h
 ** 创建人：路泽亚
 ** 创建日期： 2016-12-21
 **
 ** 描  述：简单的AC自动机
 ** 问  题：1. 构建过程中仅有内存分配失败才会失败
 ** 使用方法：1. init -> build -> search
             2. add -> add ...  -> build -> search
             3. load -> search
 ********************************************************************/
#ifndef AC_H
#define AC_H

class AC
{
public:

    // 设置State类型，不超过65535个状态时可以改为short来进一步减少内存占用
    typedef unsigned int State;

public:

    enum { ALPHABET_NUM = 256 };

    struct Keyword {
        // type小于0，则命中即返
        int       type;
        // 单词长度
        int       wordlen;
        // 单词指针
        char     *word;
        // 提供上层使用的指针
        void     *ptr;
    };

    // 流状态保存
    struct Stream {
        State state;
    };

    // 返回小于0的值立即返回
    typedef int (walk)(Keyword *w, int end, void *arg);

public:

    AC(int icase = false)
        : icase(icase), table(0), words(0), wordslen(0), nwords(0) {}

    ~AC() { destroy(); }

    /**
     * 以下是三种配置初始化的方法，只需调用其中一种，不可混用
     */
    // 添加单词，默认命中即返
    int confAdd(char *word, int len, int type = -1, void *ptr = 0);

    // 如果单词固定，可直接传入一个数组（使用add时可不用该接口）
    int confLoad(const char **wordvec = 0, int len = 0);

    /**
     * 加载打印的单词表与状态表
     * @param table 打印的状态表
     */
    void confLoad(State (*table)[ALPHABET_NUM + 1]);

    // 构建自动机
    int build();

    // 搜索（命中即返），返回索引
    int search(const char *data, int len,
               int *end = 0, Stream *s = 0);

    // 带回调的搜索（搜索所有关键字，根据type判断），返回找到单词的个数
    int search(const char *data, int len, walk *walk,
               void *arg = 0, Stream *s = 0);

    // 拉取单词（search匹配中的时候的返回值）
    Keyword *get(int index);

    // 销毁
    void destroy();

    /**
     * 打印状态表，如果单词表固定，可以以此减少加载的速度
     */
    void print();

private:

    // 将单词全部加入表中
    int buildTable();

    // 生成失败指针
    int buildFailPtr();

private:

    // 大小写敏感
    int icase;

    // build完毕后总状态数
    int statenum;

    // 状态转移图，二维数组，最后一列为单词的索引
    State (*table)[ALPHABET_NUM + 1];

    // 单词表
    Keyword *words;

    // 单词表长度
    int wordslen;

    // 单词表空间长度
    int nwords;

    // 是否为静态生成的状态表
    int isstatic;
};

#endif /* AC_H */
