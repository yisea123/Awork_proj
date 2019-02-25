
#include "app_video.h"
#include "aw_sdcard.h"
#include "fs/aw_mount.h"

static int __mount_sdcard (void)
{
    int ret     = 0;
    uint8_t rty = 255;

    /* ¼ì²âSD¿¨ÊÇ·ñ²åÈë */
    AW_INFOF(("wait for sdcard insert...\n"));
    while (rty-- > 0) {
        if (!aw_sdcard_is_insert("/dev/sd0")) {
            aw_mdelay(500);
        } else {
            break;
        }
    }

    if (rty <= 0 ) {
        AW_ERRF(("no sdcard found.\n"));
        return -1;
    }

    /* ¹ÒÔØ */
    ret = aw_mount( "/sd0", "/dev/sd0", "vfat", 0 );
    if (ret != AW_OK) {

        aw_kprintf("¹ÒÔØÊ§°Ü\r\n");
    }
    return 0;
}

void app_video_demo (void)
{
    GUI_Init();

    /* ¼ì²é²¢¹ÒÔØSD¿¨  */
    __mount_sdcard();

    /* ´¥ÃþÖ§³Ö */
    app_touch_task();

    /*×ÀÃæÈÎÎñ*/
    app_desktop_task();

    /*ÊÓÆµÈÎÎñ*/
    app_vedio_task();

}

