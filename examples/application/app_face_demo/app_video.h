/*
 * app_video.h
 *
 *  Created on: 2018Äê9ÔÂ21ÈÕ
 *      Author: wengyedong
 */

#ifndef USER_CODE_APP_VIDEO_H_
#define USER_CODE_APP_VIDEO_H_


struct app_video_rect {
    int x0,x1;
    int y0,y1;
};

extern void *app_video_create (void  *p_arg,
                               void (*pfn_img) (void *p_arg, void *img, int width, int height));

extern aw_err_t app_video_rect_line (void                  *handle,
                                     struct app_video_rect *p_rect,
                                     uint16_t               color);


#endif /* USER_CODE_APP_VIDEO_H_ */
