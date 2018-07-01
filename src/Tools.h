/*************************************************
 ** Copyright(c) 2018, luzeya
 ** All rights reserved
 **
 ** 文件名：Tools.h
 ** 创建人：zeya
 ** 创建日期： 2018-07-01
 **
 ** 描  述：工具函数
 ** 注  意：bit操作没有利用64位寄存器，性能有待考证
 **************************************************/
#ifndef TOOLS_H
#define TOOLS_H

namespace zymadc {
    namespace Tools {
        /**
         * 以hexdump的格式打印内存
         * 用以内存相关的调试
         */
        void Hexdump(void *data, int len);

        /**
         * 位图的三种操作
         */
        inline void BitSet(void *set, int n);

        inline bool BitCheck(void *set, int n);

        inline void BitUnset(void *set, int n);
    }
}

inline void zymadc::Tools::BitSet(void *set, int n)
{
    ((((char*)(set))[(n) >> 3]) |= (1 << ((n) & 0x7)));
}

inline void zymadc::Tools::BitUnset(void *set, int n)
{
    ((((char*)(set))[(n) >> 3]) &= (~(1 << ((n) & 0x7))));
}

inline bool zymadc::Tools::BitCheck(void *set, int n)
{
    return ((((char*)(set))[(n) >> 3]) & (1 << ((n) & 0x7)));
}

#endif /* TOOLS_H */
