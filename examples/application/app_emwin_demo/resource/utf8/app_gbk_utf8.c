/*
 * app_gbk_utf8.c
 *
 *  Created on: 2018��5��12��
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
                break;  /* ʣ��ռ䲻��2�ֽ�ת�����+'0' ת������ */
            }

            *p_to = *p_from;
            p_to++;
            p_from++;
            ret_size++;
        } else {               /* utf8 */
            if (p_from[1] == '\0') {

                /* ������Ϊ���ַ������п��ܵĻ���ASII�ַ� */
                break;
            }

            /* utf8 to ucs4 */
            if (utf8_mbtowc(NULL, &ucs4, (unsigned char*) p_from, 3) < 0) {
                break;
            }

            if (size - (p_to - p_gbk) < 3) {
                break;  /* ʣ��ռ䲻��3�ֽ�ת�����+'0' ת������ */
            }

            /* ucs4 to gbk */
            gbk_ret = gbk_wctomb(NULL, (unsigned char *)p_to, ucs4, 2);
            if (gbk_ret < 0) {
                break;
            }

            p_to     += gbk_ret;

            /* uft8�����ַ�һ��ռ3���ֽ�,����Դ��ַƫ�Ƽ�3 */
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
                break;  /* ʣ��ռ䲻��2�ֽ�ת�����+'0' ת������ */
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

            /* ucs4 to utf8, utf8��ʾһ�������ַ�������Ҫ3���ֽ� */
            if (size - (p_to - p_utf8) < 4) {
                break;  /* ʣ��ռ䲻��4�ֽ�ת�����+'0' ת������ */
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
