/*
 * app_gbk_utf8.c
 *
 *  Created on: 2018年5月12日
 *      Author: wengyedong
 */

#include "aworks.h"
#include "stdlib.h"
#include "include/converters.h"

uint8_t app_utf82gbk (const char *p_utf8,
                      char       *p_gbk,
                      uint32_t    size)
{
    ucs4_t ucs4 = 0;
    unsigned char *p_from = (unsigned char *) p_utf8;
    char *p_to = p_gbk;
    int gbk_ret = 0;
    int ret_size = 0;

    while (p_from[0] != '\0') {
        if (*p_from < 0x80) {  /* ascii */
            if (size - (p_to - p_gbk) < 2) {
                break;  /* 剩余空间不足2字节转换结果+'0' 转换结束 */
            }

            *p_to = *p_from;
            p_to++;
            p_from++;
            ret_size++;
        } else {               /* utf8 */
            if (p_from[1] == '\0') {

                /* 紧接着为空字符的最有可能的还是ASII字符 */
                break;
            }

            /* utf8 to ucs4 */
            if (utf8_mbtowc(NULL, &ucs4, (unsigned char*) p_from, 3) < 0) {
                break;
            }

            if (size - (p_to - p_gbk) < 3) {
                break;  /* 剩余空间不足3字节转换结果+'0' 转换结束 */
            }

            /* ucs4 to gbk */
            gbk_ret = gbk_wctomb(NULL, (unsigned char *)p_to, ucs4, 2);
            if (gbk_ret < 0) {
                break;
            }

            p_to     += gbk_ret;

            /* uft8中文字符一般占3个字节,所以源地址偏移加3 */
            p_from   += 3;
            ret_size += gbk_ret;
        }
    }

    *p_to = '\0';
    return p_from - (unsigned char *)p_utf8;
}


uint8_t app_gbk2utf8 (const char *p_gbk,
                      char       *p_utf8,
                      uint32_t    size)
{
    ucs4_t ucs4 = 0;
    unsigned char *p_from = (unsigned char *)p_gbk;
    char *p_to = p_utf8;
    int utf8_ret;
    int ret_size = 0;

    while (p_from[0] != '\0') {
        if (*p_from < 0x80) {  /* ascii */
            if (size - (p_to - p_utf8) < 2) {
                break;  /* 剩余空间不足2字节转换结果+'0' 转换结束 */
            }

            *p_to = *p_from;
            p_to++;
            p_from++;
            ret_size++;
        } else {               /* gbk */
            if (p_from[1] == '\0') {
                break;
            }

            /* gbk to ucs4 */
            if (gbk_mbtowc(NULL, &ucs4, (unsigned char*) p_from, 2) < 0) {
                break;
            }

            /* ucs4 to utf8, utf8表示一个中文字符最少需要3个字节 */
            if (size - (p_to - p_utf8) < 4) {
                break;  /* 剩余空间不足4字节转换结果+'0' 转换结束 */
            }

            /* ucs4 to utf8 */
            utf8_ret = utf8_wctomb(NULL, (unsigned char *)p_to, ucs4, 3);
            if (utf8_ret < 0) {
                break;
            }

            p_to     += utf8_ret;
            p_from   += 2;
            ret_size += utf8_ret;
        }
    }

    *p_to = '\0';
    return p_from - (unsigned char *)p_gbk;
}
