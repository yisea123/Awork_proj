/*******************************************************************************
*                                 AWorks
*                       ---------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

#include "apollo.h"
#include "aw_task.h"
#include "aw_serial.h"
#include "aw_clk.h"
#include "aworks.h"
#include "aw_vdebug.h"
#include "aw_time.h"
#include "aw_task.h"
#include "fs/aw_mount.h"
#include "fs/aw_blk_dev.h"
#include "io/aw_fcntl.h"
#include "io/aw_unistd.h"
#include "io/aw_dirent.h"
#include "io/sys/aw_stat.h"
#include "aw_delay.h"
#include <string.h>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "zal_common.h"
#include "zal_face_detection.h"
#include "zal_ai_interface.h"
#include "face/app_live_face_check.h"

typedef uint8_t ZalDataType;

using namespace std;

#ifndef MAX
#define MAX(a, b) a>b ? a:b
#endif

#ifndef MIN
#define MIN(a, b) a<b ? a:b
#endif




//
//
//// image resize
//void zalImResize(ZalDataType* src, int srcWidth, int srcHeight, int srcChannel,
//                 ZalDataType* dst, int dstWidth, int dstHeight, int dstChannel)
//{
//    float k1 = (float)dstWidth / srcWidth;
//    float k2 = (float)dstHeight / srcHeight;
//    for (int j = 0; j < dstHeight; j++)
//    {
//        ZalDataType*dstData = (ZalDataType*)(dst + j*dstWidth*dstChannel);
//        for (int i = 0; i < dstWidth; i++)
//        {
//
//            float x = (i - dstWidth/2.0f)/k1 + srcWidth/2.0f;
//            float y = (j - dstHeight/2.0f)/k2 + srcHeight/2.0f;
//
//            int u = (int)x;
//            int v = (int)y;
//
//            float alpha = x - u;
//            float beta =  y - v;
//
//            if (x >= 0 && x < srcWidth && y >= 0 && y < srcHeight)
//            {
//                for(int k = 0; k < dstChannel; k++)
//                {
//                    ZalDataType pb00 = ((ZalDataType*)(src + v*srcWidth*srcChannel))[srcChannel*u + k];
//                    ZalDataType pb10 = ((ZalDataType*)(src + v*srcWidth*srcChannel))[srcChannel*(u+1)+ k];
//                    ZalDataType pb01 = ((ZalDataType*)(src + (v+1)*srcWidth*srcChannel))[srcChannel*u+ k];
//                    ZalDataType pb11 = ((ZalDataType*)(src + (v+1)*srcWidth*srcChannel))[srcChannel*(u+1)+ k];
//                    dstData[dstChannel*i+k] =(ZalDataType)(pb00*(1-alpha)*(1-beta)+pb01*(1-alpha)*beta+pb11*alpha*beta+pb10*alpha*(1-beta) + 0.5);
//                }
//
//            }
//            else
//            {
//                for(int k = 0; k < dstChannel;k++)
//                {
//                    dstData[dstChannel*i+k] = 0;
//                }
//
//            }
//        }
//    }
//}

//// 人脸/活体检测案例
//int LivingCheck_Demo(char *p_fc_model_path, char *p_lc_model_path, char *p_img_path)
//{
//	// 人脸检测模型加载及窗口参数设置
//	zal::FaceDetection detector(p_fc_model_path);
//	detector.SetMinFaceSize(120);
//	detector.SetScoreThresh(2.f);
//	detector.SetImagePyramidScaleFactor(0.8f);
//	detector.SetWindowStep(8, 8);
//
//	// 活体检测模型加载
//	int resize = 60;
//	int resize_squ = resize * resize;
//	int lc_labels = 2;
//	DateType *p_lc_output, *p_lc_input;
//	ZalAiHandle_t h_living_check;
//
//	h_living_check = zal_ai_create(p_lc_model_path);
//	p_lc_input = (DateType *)malloc(sizeof(DateType) * resize_squ);
//	p_lc_output = (DateType *)malloc(sizeof(DateType) * lc_labels);
//
//	// 读取图片
//	uint8_t *p_img_data = (uint8_t *) malloc(sizeof(uint8_t) * 640 *480);
//	FILE *fp = fopen(p_img_path, "r");
//	int num, k=0;
//	while(fscanf(fp, "%d", &num) != EOF){
//		p_img_data[k++] = (uint8_t) num;
//	}
//	fclose(fp);
//
//	uint8_t *p_face_data_u8  = (uint8_t *) malloc(sizeof(uint8_t) * 640 *480);
//	uint8_t *p_face_resize_u8 = (uint8_t *) malloc(sizeof(uint8_t) * resize_squ);
//
//	// img resize
//	uint8_t *p_img_resize = (uint8_t *) malloc(sizeof(uint8_t) * 320 *240);
//	zalImResize(p_img_data, 640, 480, 1, p_img_resize, 320, 240, 1);
//
//	// 开始检测
//	zal::ImageData img_data;
//	img_data.width = 320;
//	img_data.height = 240;
//	img_data.num_channels = 1;
//	ZalFaceRect_t face_rect;
//	while (1)
//	{
//		img_data.data = p_img_resize;
//
//		// 人脸检测
//		aw_tick_t tick0 = aw_sys_tick_get();
//		std::vector<zal::FaceInfo> faces = detector.Detect(img_data);
//
//		int32_t num_face = static_cast<int32_t>(faces.size());
//		if (num_face == 0) {
//			aw_kprintf("No face detected. \n");
//			continue;
//		}
//
//		// 选择主要人脸
//		int max_face_index = 0;
//		if (num_face > 1) {
//			int max_face_area = faces[0].bbox.width * faces[0].bbox.height;
//			for (int i = 1; i < num_face; i++) {
//				int face_area = faces[i].bbox.width * faces[i].bbox.height;
//				if (max_face_area < face_area) {
//					max_face_index = i;
//					max_face_area = face_area;
//				}
//			}
//		}
//		face_rect.x = MAX(0, faces[max_face_index].bbox.x)*2;
//		face_rect.y = MAX(0, faces[max_face_index].bbox.y)*2;
//		face_rect.width  = MIN(320-faces[max_face_index].bbox.x, faces[max_face_index].bbox.width)*2;
//		face_rect.height = MIN(240-faces[max_face_index].bbox.y, faces[max_face_index].bbox.height)*2;
//		//face_rect.x = (face_rect.x - 160) * 2 + 320;
//		//face_rect.y = (face_rect.y - 120) * 2 + 240;
//
//		aw_tick_t tick1 = aw_sys_tick_get();
//
//		aw_kprintf("Face position and size: [%d,%d], [%d,%d] ==> ", \
//			face_rect.x, face_rect.y, face_rect.width, face_rect.height);
//
//		// 活体检测
//		for(int i=0; i<face_rect.height; i++)
//			for(int j=0; j<face_rect.width; j++)
//				p_face_data_u8[i*face_rect.width + j] = p_img_data[(i+face_rect.y)*face_rect.width + j + face_rect.x];
//
//		// face resize
//		zalImResize(p_face_data_u8, face_rect.width, face_rect.height, 1, p_face_resize_u8, resize, resize, 1);
//
//		for (int i = 0; i < resize_squ; i++) {
//			p_lc_input[i] = p_face_resize_u8[i] / 255.0;
//		}
//		zal_ai_calc(p_lc_input, p_lc_output, h_living_check);
//
//		aw_tick_t tick2 = aw_sys_tick_get();
//
//		// 活体检测结果
//		if (p_lc_output[0] > p_lc_output[1]) {
//			aw_kprintf("Check results: Living.\n");
//		}
//		else {
//			aw_kprintf("Check results: Non-living.\n");
//		}
//		aw_kprintf("Detect time: %dms, Living check time %dms\n\n", tick1-tick0, tick2-tick1);
//
//	}
//
//	free(p_img_data);
//	free(p_lc_output);
//	free(p_lc_input);
//	free(p_face_data_u8);
//	free(p_face_resize_u8);
//	zal_ai_release(h_living_check);
//	return 0;
//}
//
//aw_local int  __fs_task_entry(void)
//{
//    aw_err_t  ret;
//
//    AW_INFOF(("\n\n\n**********************************************\n"));
//    AW_INFOF((" test file system function:\n"));
//
//    aw_mdelay(3000);
//
//    /* 文件系统挂载 */
//    ret = aw_mount("/export", __DISK_NAME, __FS_NAME, 0);
//    if (ret != AW_OK) {
//        AW_ERRF(("/export mount /dev/mtd0 error: %d!\n", ret));
//        return ret;
//    }
//    AW_INFOF(("mount OK\n"));
//
//    return  AW_OK;
//}

//int aw_main()
//{
//	char *p_img_path = "/export/gray_image_data.txt";
//    char *p_fc_model_path = "/export/zal_face_detection.dat";
//    char *p_lc_model_path = "/export/zal_living_check.dat";
//
//    __fs_task_entry();
//
//	LivingCheck_Demo(p_fc_model_path, p_lc_model_path, p_img_path);
//
//    return 0;
//}

















#include "aw_mem.h"
#include "aw_task.h"
#include "aw_sem.h"

#define __LIVE_FACE_TSK_STACK  (64 * 1024)


struct __app_live_face_chk {
    zal::ImageData     *img;
    zal::FaceDetection *detector;
    ZalAiHandle_t      *living_chk;
    void               *p_buf;
    void               *p_rgb565;

    aw_task_id_t        task;
    AW_SEMB_DECL(       sync);
    bool_t              busy;

    void  *p_arg;
    void (*pfn_done) (void                 *p_arg,
                      bool_t                found,
                      void                 *img,
                      int                   width,
                      int                   height,
                      struct app_face_rect *p_rect);
};




aw_local void __rgb565_to_gray (uint16_t *p_565, int width, int height, uint8_t *p_gray)
{
    int n = width * height;
    int i;

    for (i = 0; i < n; i++) {
        *p_gray = ((*p_565) >> 11) * 0.3 * 8 +
                  (((*p_565) >> 5) & 0x3F) * 0.59 * 4 +
                  ((*p_565) & 0x1F) * 0.11 * 8;

        p_gray++;
        p_565++;
    }
}




// 人脸/活体检测案例
int app_live_face_check (void *p_app, void *img, int width, int height)
{
    struct __app_live_face_chk *p = (struct __app_live_face_chk *)p_app;

    if (p->busy) {
        return -AW_EBUSY;
    }
    p->busy = TRUE;

    memcpy(p->p_rgb565, img, width * height * 2);
    __rgb565_to_gray((uint16_t*)img, width, height, (uint8_t *)p->p_buf);

    AW_SEMB_GIVE(p->sync);

    return AW_OK;
}

/******************************************************************************/
aw_local void __tsk_handle (void *p_arg)
{
    struct __app_live_face_chk *p_app = (struct __app_live_face_chk *)p_arg;
    std::vector<zal::FaceInfo>  faces;
    int32_t                     num_face;
    int32_t                     max_face_index = 0;
    struct app_face_rect        rect;

    AW_FOREVER {
        p_app->busy = FALSE;
        AW_SEMB_TAKE(p_app->sync, AW_SEM_WAIT_FOREVER);

        max_face_index = 0;
        faces = p_app->detector->Detect(*p_app->img);

        num_face = static_cast<int32_t>(faces.size());
        if (num_face == 0) {
            continue;
        }

        if (num_face > 1) {
            int max_face_area = faces[0].bbox.width * faces[0].bbox.height;
            for (int i = 1; i < num_face; i++) {
                int face_area = faces[i].bbox.width * faces[i].bbox.height;
                if (max_face_area < face_area) {
                    max_face_index = i;
                    max_face_area = face_area;
                }
            }
        }

        rect.x0 = MAX(faces[max_face_index].bbox.x, 0);
        rect.y0 = MAX(faces[max_face_index].bbox.y, 0);
        rect.x1 = MIN(rect.x0 + faces[max_face_index].bbox.width, p_app->img->width) - 1;
        rect.y1 = MIN(rect.y0 + faces[max_face_index].bbox.height, p_app->img->height) - 1;

        aw_kprintf("face in rectangle->(%d, %d),(%d, %d)\r\n", rect.x0, rect.y0, rect.x1, rect.y1);

        if (p_app->pfn_done) {
            p_app->pfn_done(p_app->p_arg,
                            num_face ? TRUE : FALSE,
                            p_app->p_rgb565,
                            p_app->img->width,
                            p_app->img->height,
                            &rect);
        }
    }
}


void *app_live_face_chk_create (int         width,
                                int         height,
                                const char *fpath,
                                const char *lpath,
                                void       *p_arg,
                                void (     *pfn_done) (void                 *p_arg,
                                                       bool_t                found,
                                                       void                 *img,
                                                       int                   width,
                                                       int                   height,
                                                       struct app_face_rect *p_rect))
{
    __app_live_face_chk *p_app;

    p_app = new __app_live_face_chk;
    if (p_app == NULL) {
        goto __failed;
    }

    memset(p_app, 0, sizeof(*p_app));

    p_app->detector = new zal::FaceDetection(fpath);
    if (p_app->detector == NULL) {
        goto __failed;
    }

    p_app->img = new zal::ImageData();
    if (p_app->img == NULL) {
        goto __failed;
    }

    p_app->living_chk = new ZalAiHandle_t();
    if (p_app->living_chk == NULL) {
        goto __failed;
    }

    p_app->p_buf = aw_mem_alloc(width * height);
    if (p_app->p_buf == NULL) {
        goto __failed;
    }

    p_app->p_rgb565 = aw_mem_alloc(width * height * 2);
    if (p_app->p_rgb565 == NULL) {
        goto __failed;
    }

    p_app->detector->SetMinFaceSize(60);
    p_app->detector->SetScoreThresh(2.f);
    p_app->detector->SetImagePyramidScaleFactor(0.8f);
    p_app->detector->SetWindowStep(8, 8);

    p_app->img->width        = width;
    p_app->img->height       = height;
    p_app->img->num_channels = 1;
    p_app->img->data         = (uint8_t *)p_app->p_buf;

    p_app->p_arg    = p_arg;
    p_app->pfn_done = pfn_done;

    AW_SEMB_INIT(p_app->sync, 0, AW_SEM_Q_PRIORITY);

    p_app->task = aw_task_create("face",
                                 19,
                                 __LIVE_FACE_TSK_STACK,
                                 __tsk_handle,
                                 (void *)p_app);
    if (p_app->task == NULL) {
        goto __failed;
    }

    aw_task_startup(p_app->task);

    return p_app;

__failed:
    if (p_app) {
        if (p_app->detector) {
            delete(p_app->detector);
        }

        if (p_app->img) {
            delete(p_app->img);
        }

        if (p_app->living_chk) {
            delete(p_app->living_chk);
        }

        if (p_app->p_buf == NULL) {
            aw_mem_free(p_app->p_buf);
        }

        if (p_app->p_rgb565 == NULL) {
            aw_mem_free(p_app->p_rgb565);
        }
        delete(p_app);
    }

    return NULL;
}




void app_live_face_chk_destory (void *p_app)
{
    __app_live_face_chk *p = (__app_live_face_chk *)p_app;

    if (p) {
        if (p->detector == NULL) {
            delete(p->detector);
        }

        if (p->img == NULL) {
            delete(p->img);
        }

        if (p->living_chk == NULL) {
            delete(p->living_chk);
        }

        if (p->p_buf == NULL) {
            aw_mem_free(p->p_buf);
        }

        if (p->p_rgb565 == NULL) {
            aw_mem_free(p->p_rgb565);
        }
        delete(p);
    }
}
