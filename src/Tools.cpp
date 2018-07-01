/*************************************************
 ** Copyright(c) 2018, luzeya
 ** All rights reserved
 **
 ** 文件名：Tools.cpp
 ** 创建人：zeya
 ** 创建日期： 2018-07-01
 **
 ** 描  述：工具函数
 ** 注  意：
 **************************************************/
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include "Tools.h"

using namespace zymadc;

#define PCHAR(p, index)                         \
    (isprint((p)[index]) ? ((p)[index]) : '.')

void Tools::Hexdump(void *data, int len)
{
    int off = 0;
    char *p = (char*)data;

    for (; len > 0; len -= 16, p += 16) {
        printf("%08X ", off);
        for (int i = 0; i < 16; i++) {
            if (i == 8) {
                printf(" ");
            }
            printf((i < len) ? " %02X" : "   ", p[i]);
        }
        printf("  |");
        for (int i = 0; i < 16; i++) {
            printf("%c", (i < len) ? (PCHAR(p, i)) : ' ');
            if (i == 7)
                printf(" ");
        }
        printf("|\n");
        off += (len > 16) ? 16 : len;
    }
    printf("%08X\n", off);
    return;
}