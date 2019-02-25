/*
 * app_live_face_check.h
 *
 *  Created on: 2018Äê9ÔÂ18ÈÕ
 *      Author: wengyedong
 */

#ifndef USER_CODE_FACE_APP_LIVE_FACE_CHECK_H_
#define USER_CODE_FACE_APP_LIVE_FACE_CHECK_H_


#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */
int app_live_face_check (void *p_app, void *img, int width, int height);

struct app_face_rect {
    int x0,x1;
    int y0,y1;
};

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
                                                       struct app_face_rect *p_rect));
#ifdef __cplusplus
}
#endif  /* __cplusplus  */



#endif /* USER_CODE_FACE_APP_LIVE_FACE_CHECK_H_ */
