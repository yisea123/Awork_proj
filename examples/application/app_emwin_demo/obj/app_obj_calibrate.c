/*
 * app_obj_calibrate.c
 *
 *  Created on: 2018年5月16日
 *      Author: Administrator
 */

#include "aworks.h"
#include "aw_sem.h"
#include "aw_ts.h"

#include "GUI.h"
#include "WM.h"
#include "FRAMEWIN.h"
#include "TEXT.h"
#include "BUTTON.h"

#include "../resource/app_resource.h"



extern int app_ts_calibrate (aw_ts_id                 id,
                             aw_ts_lib_calibration_t *p_cal);
extern bool_t app_dialog (WM_HWIN hwin, const char *info);




/******************************************************************************/
aw_local void __app_calibrate_cb (WM_MESSAGE * pMsg)
{
    aw_ts_id                sys_ts;
    aw_ts_lib_calibration_t cal;
    int                     ret;

    switch (pMsg->MsgId) {
    case WM_DELETE:
        break;

    case WM_CREATE:
        sys_ts = aw_ts_serv_id_get("480x272", 0x00, 0x00);
        if (sys_ts == NULL) {
            //TODO
        }

        while (1) {
            app_ts_calibrate(sys_ts, &cal);

            ret = aw_ts_calibrate(sys_ts, &cal);
            if (ret != AW_OK) {
                if (app_dialog(pMsg->hWin, "校准失败,是否重试？")) {
                    continue;
                } else {
                    WM_DeleteWindow(pMsg->hWin);
                    break;
                }
            } else {
                if (app_dialog(pMsg->hWin, "校准成功,是否保存？")) {
                    aw_ts_calc_data_write(sys_ts);
                } else {
                    aw_ts_calc_data_read(sys_ts);
                }
                WM_DeleteWindow(pMsg->hWin);
                break;
            }
        }
        break;

    case WM_PAINT:
        GUI_SetBkColor(GUI_WHITE);
        GUI_Clear();
        break;

    default:
        WM_DefaultProc(pMsg);
        break;
    }
}



/******************************************************************************/
void *app_calibrate_create (WM_HWIN parent, const char *name)
{
    WM_HWIN hwin = 0;

    if (app_dialog(parent, "是否进行校准")) {
        hwin = WM_CreateWindowAsChild(0, 0,
                                      LCD_GetXSize(),
                                      LCD_GetYSize(),
                                      WM_HBKWIN,
                                      WM_CF_SHOW,
                                      __app_calibrate_cb,
                                      0);
    }

    return (void *)hwin;
}


