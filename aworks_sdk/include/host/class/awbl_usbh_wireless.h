/*
 * awbl_usbh_wireless.h
 *
 *  Created on: 2017Äê7ÔÂ21ÈÕ
 *      Author: wengyedong
 */

#ifndef __AWBL_USBH_WIRELESS_H
#define __AWBL_USBH_WIRELESS_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */


#define AWBL_USBH_WIRELESS_DRV_NAME     "awbl_usbh_wireless_driver"







void *awbl_usbh_wireless_pipe_open (int     pid,
                                    int     vid,
                                    int     inum,
                                    bool_t  rngbuf,
                                    int     size,
                                    int     timeout);
void awbl_usbh_wireless_pipe_close (void *pipe);
int awbl_usbh_wireless_pipe_write (void *pipe, void *p_buf, int len, int timeout);
int awbl_usbh_wireless_pipe_read (void *pipe, void *p_buf, int len, int timeout);

void awbl_usbh_wireless_drv_register (void);


#ifdef __cplusplus
}
#endif  /* __cplusplus  */


#endif /* __AWBL_USBH_WIRELESS_H */
