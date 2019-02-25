/*
 * app_main.c
 *
 *  Created on: 2018年9月17日
 *      Author: wengyedong
 */

#include "aworks.h"
#include "aw_shell.h"
#include "aw_vdebug.h"
#include "aw_delayed_work.h"
#include "fs/aw_blk_dev.h"
#include "fs/aw_mount.h"
#include "io/aw_fcntl.h"
#include "io/aw_unistd.h"
#include "io/sys/aw_stat.h"
#include "face/app_live_face_check.h"
#include "app_video.h"
#include "string.h"
#include "aw_types.h"
#include "aw_mem.h"
#include "aw_buzzer.h"

#define __FS_NAME        "lffs"
#define __DISK_NAME      "/dev/mtd0"
#define __MOUNT_NAME     "/mnt"
#define __FACE_MODEL     __MOUNT_NAME"/zal_face_detection.dat"
#define __LIVING_MODEL   __MOUNT_NAME"/zal_living_check.dat"
//#define __BLK_DISK
#define __BLK_NAME       "/dev/h0-d1-0"
#define __BLK_MOUNT_NAME "/u"

aw_local void   *__gp_face = NULL;
aw_local void   *__gp_video = NULL;
aw_local void   *__gp_net = NULL;
struct app_video_rect   __g_rect = {0, 0, 0, 0};
struct aw_delayed_work  __g_dly_work;

aw_local uint8_t *__gp_img = NULL;
aw_local int      __g_img_size = 0;

aw_local uint8_t  __g_img_flag = 0;
aw_local char    *__gp_img_path = NULL;

extern void *app_net_create (void *p_arg,
		                     void (*pfn_response) (void *p_arg, void *response, int len));
							 
extern aw_err_t app_net_face_send (void *p_app, uint8_t *p_img, int len);


aw_local int __img_save (int argc, char *argv[], struct aw_shell_user *p_user)
{
    if (!__g_img_flag) {
        if (argc > 0) {
        	sprintf(__gp_img_path, "%s/%s", __BLK_MOUNT_NAME, argv[0]);
        } else {
        	sprintf(__gp_img_path, "%s/%s", __BLK_MOUNT_NAME, "img.bmp");
        }
        aw_kprintf("%s", __gp_img_path);
        __g_img_flag = TRUE;
    }
    return 0;
}

aw_local int __img_get_cmd (void)
{
	int fd;
    fd = aw_open(__gp_img_path,  O_RDWR | O_CREAT | O_TRUNC, 0777);
    if (fd < 0) {
    	aw_kprintf("open bmp path failed!\r\n");
    	return 0;
    }
    aw_write(fd, __gp_img, __g_img_size);
    aw_close(fd);
	return 0;
}

aw_local const struct aw_shell_cmd __g_img_get_cmds[] = {
    {__img_save,  "img",  "get IMG"},
};


struct __bmp_head {
    uint16_t type;      // 位图类型， “BM”, 0x4d42
    uint32_t size;      // 整个文件大小，以字节为单位
    uint16_t res1;
    uint16_t res2;
    uint32_t offs;      // 位图数据起始位置
} __attribute__((packed));

struct __bmp_info {
    uint32_t size;          // 本结构体大小 40
    int32_t  width;         // 图像宽像素
    int32_t  height;        // 图像高像素
    uint16_t planes;        // 设备级别  1
    uint16_t bitcnt;        // 像素位数，1（黑白）、 4（16色）、 8（256色）、 16（高彩色）、 24（真彩色）
    uint32_t compression;   // 是否压缩， 不压缩 0
    uint32_t sizeimg;       // 位图数据大小， width * height * (bitcnt/8)
    int32_t  xpels;         // 目标设备水平分辨率
    int32_t  ypels;         // 目标设备垂直分辨率
    uint32_t clrused;       // 颜色数...
    uint32_t clrimportant;  // 重要颜色，0
} __attribute__((packed));




aw_local void __rgb565_to_rgb888 (uint8_t *p_565, int width, int height, uint8_t *p_888)
{
    uint16_t rgb;
    int      n, i;

    n = width * height;

    for (i = 0; i < n; i++, p_565 += 2, p_888 += 3) {
        memcpy(&rgb, p_565, 2);
        p_888[0] = ((rgb >> 11) & 0x1F) << 3;
        p_888[1] = ((rgb >> 5) & 0x3F) << 2;
        p_888[2] = (rgb & 0x1F) << 3;
    }
}




aw_local int __bmp_create (uint8_t              *p_img,
                           int                   width,
                           int                   height,
                           uint8_t              *p_bmp)
{
    struct __bmp_head  head;
    struct __bmp_info  info;
    int                y, tmp;
    uint8_t           *p_dst = p_bmp;

    head.type = 0x4d42;
    head.offs = 54;
    head.res1 = 0;
    head.res2 = 0;

    info.size         = 40;
    info.width        = width;
    info.height       = height;
    info.planes       = 1;
    info.bitcnt       = 24;
    info.compression  = 0;
    info.sizeimg      = 3 * width * height;
    info.xpels        = 0;
    info.ypels        = 0;
    info.clrused      = 0;
    info.clrimportant = 0;

    memcpy(p_dst, &head, sizeof(head));
    p_dst += sizeof(head);
    memcpy(p_dst, &info, sizeof(info));
    p_dst += sizeof(info);

    p_img += (height * width * 3);

    for (y = 0; y < height; y++) {
        p_img -= (width * 3);

        memcpy(p_dst, p_img, width * 3);
        p_dst += width * 3;

        tmp = width * 3 % 4;
        if (tmp) {
            tmp = 4 - tmp;
            memset(p_dst, 0, tmp);
            p_dst += tmp;
        }
    }

    head.size = p_dst - p_bmp;

    return head.size;
}




aw_local void __dly_work (void *p_arg)
{
    __g_rect.x0 = 0;
    __g_rect.x1 = 0;
    __g_rect.y0 = 0;
    __g_rect.y1 = 0;
}


// image resize
void zalImResize(uint8_t* src, int srcWidth, int srcHeight, int srcChannel,
                 uint8_t* dst, int dstWidth, int dstHeight, int dstChannel)
{
    float k1 = (float)dstWidth / srcWidth;
    float k2 = (float)dstHeight / srcHeight;
    for (int j = 0; j < dstHeight; j++)
    {
        uint8_t*dstData = (uint8_t*)(dst + j*dstWidth*dstChannel);
        for (int i = 0; i < dstWidth; i++)
        {

            float x = (i - dstWidth/2.0f)/k1 + srcWidth/2.0f;
            float y = (j - dstHeight/2.0f)/k2 + srcHeight/2.0f;

            int u = (int)x;
            int v = (int)y;

            float alpha = x - u;
            float beta =  y - v;

            if (x >= 0 && x < srcWidth && y >= 0 && y < srcHeight)
            {
                for(int k = 0; k < dstChannel; k++)
                {
                    uint8_t pb00 = ((uint8_t*)(src + v*srcWidth*srcChannel))[srcChannel*u + k];
                    uint8_t pb10 = ((uint8_t*)(src + v*srcWidth*srcChannel))[srcChannel*(u+1)+ k];
                    uint8_t pb01 = ((uint8_t*)(src + (v+1)*srcWidth*srcChannel))[srcChannel*u+ k];
                    uint8_t pb11 = ((uint8_t*)(src + (v+1)*srcWidth*srcChannel))[srcChannel*(u+1)+ k];
                    dstData[dstChannel*i+k] =(uint8_t)(pb00*(1-alpha)*(1-beta)+pb01*(1-alpha)*beta+pb11*alpha*beta+pb10*alpha*(1-beta) + 0.5);
                }

            }
            else
            {
                for(int k = 0; k < dstChannel;k++)
                {
                    dstData[dstChannel*i+k] = 0;
                }

            }
        }
    }
}



aw_local void __img_cut (void *img, int width, int height, int nchn,
                         struct app_face_rect *p_rect, void *output)
{
    int         i, offs, len;
    uint8_t    *p_src, *p_dst;

    p_src = (uint8_t *)img + (p_rect->y0 * width + p_rect->x0) * nchn;
    p_dst = (uint8_t *)output;
    len   = (p_rect->x1 - p_rect->x0 + 1) * nchn;
    offs  = width * nchn;

    for (i = p_rect->y0; i < p_rect->y1; i++) {
        memcpy(p_dst, p_src, len);
        p_dst += len;
        p_src += offs;
    }
}


aw_local void __img_get (void *p_arg, void *img, int width, int height)
{
    if (__gp_face) {
        app_live_face_check(__gp_face, img, width, height);
    }

    app_video_rect_line(__gp_video, &__g_rect, 0x0F00);
}


aw_local  void __face_done (void                 *p_arg,
                            bool_t                found,
                            void                 *img,
                            int                   width,
                            int                   height,
                            struct app_face_rect *p_rect)
{
    if (found) {
        aw_delayed_work_start(&__g_dly_work, 1000);
        __g_rect = *(struct app_video_rect *)p_rect;

        __img_cut(img, width, height, 2, p_rect, img);

        width  = p_rect->x1 - p_rect->x0 + 1;
        height = p_rect->y1 - p_rect->y0 + 1;

        __rgb565_to_rgb888(img, width, height, __gp_img);

        zalImResize(__gp_img, width, height, 3,
                    img, 150, 150, 3);

        __g_img_size = __bmp_create((uint8_t *)img, 150, 150, __gp_img);

        if (__gp_net) {
            app_net_face_send(__gp_net,
                              __gp_img,
                              __g_img_size);
        }

        if (__g_img_flag) {
        	__img_get_cmd();
        	__g_img_flag = FALSE;
        }

    } else {
        __g_rect.x0 = 0;
        __g_rect.x1 = 0;
        __g_rect.y0 = 0;
        __g_rect.y1 = 0;
    }
}

aw_local void __face_response(void *p_arg, void *response, int len)
{
	uint8_t *result = (uint8_t *)strstr(response, "result");
	if (result[8] == 'f') {
		aw_kprintf("response is false!\r\n");
		return;
	}

	uint8_t *data = (uint8_t *)strrchr(response, ':');
	if (data[2] != '-') {
		aw_buzzer_loud_set(50);
		aw_buzzer_beep(50);
	} else {
		aw_buzzer_loud_set(50);
		aw_buzzer_beep(50);
		aw_mdelay(50);
		aw_buzzer_beep(50);
	}
}

aw_local aw_err_t __fs_init (void)
{
    aw_err_t      ret = AW_OK;
    static bool_t init = FALSE;

    if (init == FALSE) {
#ifdef __BLK_DISK
        ret = aw_blk_dev_wait_install(__BLK_NAME, -1);
        if (ret != AW_OK) {
        	aw_kprintf("wait disk install failed!\r\n");
        }
        aw_kprintf("wait disk install success!\r\n");

        ret = aw_mount(__BLK_MOUNT_NAME, __BLK_NAME, "vfat", 0);
        if (ret != AW_OK) {
            aw_kprintf("%s mount failed %d!\n", __BLK_NAME, ret);
            return ret;
        }
        __gp_img_path = aw_mem_alloc(32);
#endif
        ret = aw_mount(__MOUNT_NAME, __DISK_NAME, __FS_NAME, 0);
        if (ret != AW_OK) {
            aw_kprintf("%s __DISK_NAME mount failed %d!\n", __DISK_NAME, ret);
        }
        init = TRUE;
    }
    return ret;
}



void app_main (void)
{
    static struct aw_shell_cmd_list  cl;
    if (__fs_init() != AW_OK) {
        return;
    }

    (void)AW_SHELL_REGISTER_CMDS(&cl, __g_img_get_cmds);

    aw_delayed_work_init(&__g_dly_work,
                         __dly_work,
                         NULL);

    __gp_video = app_video_create(NULL, __img_get);
    if (__gp_video == NULL) {
        return;
    }
    __gp_face = app_live_face_chk_create(320, 240, __FACE_MODEL, __LIVING_MODEL, NULL, __face_done);
    if (__gp_face == NULL) {
        return;
    }

    __gp_img = aw_mem_alloc(320 * 240 * 3 + 54 + 240 * 3);

    __gp_net = app_net_create(NULL, __face_response);
    if (__gp_net == NULL) {
        return;
    }
}


