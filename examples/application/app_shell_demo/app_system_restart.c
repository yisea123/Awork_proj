

#include "aworks.h"
#include "aw_wdt.h"
#include "aw_shell.h"
#include "aw_delay.h"
#include "app_config.h"

#ifdef APP_SYS_RST


int app_system_restart  (int argc, char **argv, struct aw_shell_user *p_user)
{
    struct awbl_wdt wdt_dev;
    aw_err_t  ret = AW_OK;

    /* 设置看门狗时间 */
    ret = aw_wdt_add(&wdt_dev, 1);
    if (ret != AW_OK) {
        aw_kprintf("*ERR: WDT add error %d\n", ret);
        return -EINVAL;
    }


    /* LED0 间隔闪烁 */
    while (1) {
        aw_mdelay(100);
    }

    return AW_OK;
}


#endif
