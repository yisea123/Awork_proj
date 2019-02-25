
/*
 *  此文件由配置工具生产，请勿修改。
 *  现在作为一个例子。
 */
#undef  AW_IMG_PRJ_BUILD
#define AW_IMG_PRJ_BUILD

#include "aworks.h"
#include "awbus_lite.h"
#include "aw_task.h"
#include "awbl_plb.h"
#include "aw_serial.h"
#include "aw_prj_params.h"
#include "aw_vdebug.h"
#include "aw_gpio.h"
#include "awbl_gpio.h"
#include "awbl_led.h"
#include "awbl_wdt.h"
#include "awbl_pwm.h"
#include "awbl_driver_if.h"
#include "aw_bsp_driver_if.h"
#include "mtd/aw_mtd.h"
#include "aw_sdk_version.h"

/* including c source files */
#include "all/aworks_startup.c"
#include "all/aw_psp_startup.c"
#include "all/aw_psp_usr_app_init.c"
#include "core/awbus_lite_cfg.c"

#include "os/aw_isr_defer_cfg.c"
#include "os/aw_nor_defer_cfg.c"
#include "awsa/awsa_cfg.c"

#ifdef AW_COM_INPUT_EV
#include "core/awbus_input_cfg.c"
#endif

#ifdef AW_COM_LOG
#include "util/aw_loglib_cfg.c"
#endif

#ifdef AW_COM_FTL
#include "ftl/aw_ftl_cfg.c"
#endif

#ifdef AW_COM_NETWORK
#include "net/aw_net.h"
#endif  /* AW_COM_NETWORK */

#ifdef AW_COM_SHELL_SERIAL
#include "config/aw_shell_serial_cfg.c"
#endif  /* AW_COM_SHELL_SERIAL */

#ifdef AW_COM_SHELL_TELNET
#include "config/aw_telnet_cfg.c"
#endif

#ifdef AW_COM_FTPD
#include "config/aw_ftpd_cfg.c"
#endif

#ifdef AW_COM_SERIAL
#include "driver/serial/awbl_serial_cfg.c"
#endif  /* AW_COM_SERIAL */

#ifdef AW_DRV_SPI_FLASH
#include "driver/norflash/awbl_spi_flash_cfg.c"
#endif /* AW_DRV_SPI_FLASH */

#ifdef AW_COM_BLOCK_DEV
#include "fs/aw_blk_dev.h"
#endif  /* AW_DRV_BLOCK_DEV */

#ifdef AW_COM_I2C
#include "awbl_i2cbus.h"
#endif  /* AW_COM_I2C */

#ifdef AW_COM_FS_ROOTFS
#include "fs/aw_root_fs.h"
#endif  /* AW_COM_FS_ROOTFS */

#ifdef AW_COM_FS_FATFS
#include "fs/aw_fatfs_cfg.c"
#endif  /* AW_COM_FS_FATFS */

#ifdef AW_COM_FS_LFFS
#include "fs/aw_lffs_cfg.c"
#endif  /* AW_COM_FS_LFFS */

#ifdef AW_COM_FS_YAFFS
#include "fs/aw_yaffs_cfg.c"
#endif  /* AW_COM_FS_LFFS */

#ifdef AW_COM_EVENT
#include "util/aw_event_cfg.c"
#endif  /* AW_COM_EVENT */

#ifdef AW_COM_IO_SYSTEM
#include "io/aw_io_cfg.c"
#endif  /* AW_COM_IO_SYSTEM */

#ifdef AW_COM_MOUNT
#include "fs/aw_mount_cfg.c"
#endif  /* AW_COM_MOUNT */

#if  defined(__CC_ARM) || defined(AW_DRV_IMX1050_TS) || defined(AW_DRV_BU21029MUV_TS) || defined(AW_DRV_FT5X06_TS)
#include "ts/aw_ts_calc_cfg.c"
#endif  

#if defined(AW_COM_USBH) || defined(AW_COM_USBD)
#include "awbl_usb_cfg.c"
#endif

#ifdef AW_DRV_USBH_WIRELESS
#include "awbl_usbh_wireless_info.c"
#endif

#if defined(AW_COM_NETWORK) && defined(AW_NET_TOOLS)
    #include "config/aw_net_tools_cfg.h"
#endif  /* AW_NET_TOOLS */

#ifdef AW_COM_CONSOLE
#if AW_CFG_CONSOLE_SHOW_BANNER  != 0
static const char __g_aw_banner[] = {
    "\nAWorks for i.MX RT1050 V1.0.0, build " __DATE__ "\n"
};
#endif  /* AW_CFG_CONSOLE_SHOW_BANNER */
#endif  /* AW_COM_CONSOLE */

#ifdef AW_COM_CONSOLE
#if AW_CFG_CONSOLE_SHOW_BANNER  != 0
void aw_console_show_banner (void)
{
    AW_LOGF(("%s\n", __g_aw_banner));
    AW_LOGF(("AWorks SDK Version is %s  \r\n", aw_sdk_version_get()));
}
#endif  /* AW_CFG_CONSOLE_SHOW_BANNER */
#endif  /* AW_COM_CONSOLE */

static void awbl_group_init (void)
{
    awbus_lite_init();
    awbl_plb_register();

    awbl_armcm_nvic_drv_register();
    awbl_imx1050_gpio_drv_register();

#ifdef AW_DRV_IMX1050_GPT
    awbl_imx1050_gpt_drv_register();
#endif

#ifdef AW_DRV_IMX1050_PIT
    awbl_imx1050_pit_drv_register();
#endif

#ifdef AW_DRV_IMX1050_LPUART
    awbl_imx1050_lpuart_drv_register();
#endif

#ifdef AW_DRV_GPIO_LED
    awbl_led_gpio_drv_register();
#endif

#ifdef AW_DRV_GPIO_KEY
    awbl_gpio_key_drv_register();
#endif

#ifdef AW_DRV_IMX1050_ENET
    awbl_imx1050_enet_drv_register();
    awbl_miibus_init();
    awbl_generic_phy_drv_register();
#endif

#ifdef AW_DRV_IMX1050_FLEXSPI
    awbl_imx1050_flexspi_drv_register();
#endif

#ifdef AW_DRV_IMX1050_LPSPI
    awbl_imx1050_lpspi_drv_register();
#endif

#ifdef AW_DRV_SPI_FLASH
    awbl_spi_flash_cfg();
    awbl_spi_flash_drv_register();
#endif

#ifdef AW_DRV_IMX1050_WDT
    awbl_imx1050_wdt_drv_register();
#endif /* AW_DRV_IMX1050_WDT */

#ifdef AW_DRV_IMX1050_RTWDT
    awbl_imx1050_rtwdt_drv_register();
#endif /* AW_DRV_IMX1050L_RTWDT */

#ifdef AW_DRV_IMX1050_ADC
    awbl_imx1050_adc_drv_register();
#endif

#ifdef AW_DRV_IMX1050_USDHC
    awbl_sdiobus_init();
    awbl_sdcard_drv_register();
    awbl_imx1050_sdio_drv_register();
#endif

#ifdef AW_DRV_IMX1050_EDMA
    awbl_imx1050_edma_drv_register();
#endif

#ifdef AW_DRV_IMX1050_SAI
    awbl_imx1050_sai_drv_register();
#endif /* AW_DRV_IMX1050L_SAI */

#ifdef AW_DRV_IMX1050_MQS
    awbl_imx1050_mqs_drv_register();
#endif /* AW_DRV_IMX1050L_MQS */

#ifdef AW_DRV_IMX1050_LPI2C
    awbl_imx1050_lpi2c_drv_register();
#endif

#ifdef AW_DRV_IMX1050_OCOTP
    awbl_imx1050_ocotp_register();
#endif


#ifdef AW_DRV_IMX1050_CAN
    awbl_imx1050_flexcan_drv_register();
#endif


#ifdef AW_DRV_TFT_PANEL
    awbl_imx1050_tft_panel_drv_register();
#endif

#ifdef AW_DRV_EMWIN_FB
    awbl_imx1050_emwin_fb_drv_register();
#endif

#ifdef AW_DRV_FT5X06_TS
    awbl_ft5x06_drv_register();
#endif

#ifdef AW_DRV_BU21029MUV_TS
    awbl_bu21029muv_drv_register();
#endif

#ifdef AW_DRV_IMX1050_TS
    awbl_imx1050_touch_screen_drv_register();
#endif

#ifdef AW_DRV_IMX1050_EFLEX_PWM
    awbl_imx1050_eflex_pwm_drv_register();
#endif

#ifdef AW_DRV_IMX1050_QTIMER_PWM
    awbl_imx1050_qtimer_pwm_drv_register();
#endif

#ifdef AW_DRV_PWM_BUZZER
    awbl_pwm_buzzer_drv_register();
#endif

#ifdef AW_DRV_GPIO_I2C_0
    awbl_gpio_i2c_drv_register();
#endif

#ifdef AW_DRV_EXTEND_PCF85063
    awbl_pcf85063_drv_register();
#endif

#ifdef AW_DRV_EXTEND_PCF85263
    awbl_pcf85263_drv_register();
#endif

#ifdef AW_COM_NANDBUS
    void awbl_nand_bus_init(void);
    awbl_nand_bus_init();
#endif /* AW_COM_NANDBUS */

#ifdef AW_DRV_IMX1050_SEMC
    awbl_imx1050_semc_drv_register();
#endif /* AW_DRV_IMX1050_SEMC */

#ifdef AW_DRV_NANDFLASH
    awbl_imx1050_nand_drv_register();
#endif /* AW_DRV_NANDFLASH */

#if defined AW_DRV_IMX1050_FLEXIO_UART
    awbl_imx1050_flexio_uart_drv_register();
#endif

#ifdef AW_DRV_IMX1050_USBH
    awbl_imx1050_usbh_drv_register();
#endif

#ifdef AW_COM_USBH
    extern void awbl_usbh_bus_init (void);
    awbl_usbh_bus_init();
    awbl_usbh_hub_drv_register();
#endif

#ifdef AW_DRV_USBH_MASS_STORAGE
    extern void awbl_usbh_mass_storage_drv_register (int buffer_size);
    awbl_usbh_mass_storage_drv_register(AW_CFG_USB_MS_BUF_SIZE);
#endif

#ifdef AW_DRV_USBH_WIRELESS
    awbl_usbh_wireless_drv_register();
#endif

#ifdef AW_DRV_GPRS_SIM800
    extern void awbl_gprs_sim800_drv_register (void);
    awbl_gprs_sim800_drv_register();
#endif

#ifdef AW_DRV_GPRS_ME909S
    extern void awbl_gprs_me909s_drv_register (void);
    awbl_gprs_me909s_drv_register();
#endif

#ifdef AW_DEV_GPRS_U9300C
    extern void awbl_gprs_u9300c_drv_register (void);
    awbl_gprs_u9300c_drv_register();
#endif

#ifdef AW_DRV_FM175XX
    awbl_fm175xx_drv_register();
#endif

#ifdef AW_DRV_IMX1050_USBD
    awbl_imx1050_usbd_drv_register();
#endif

#ifdef AW_DRV_GPIO_WDT
    awbl_gpio_wdt_drv_register();
#endif

#ifdef AW_DRV_IMX1050_ENC1
    awbl_imx1050_enc_drv_register();
#endif

#ifdef AW_DRV_IMX1050_TEMPMON
    awbl_imx1050_tempmon_drv_register();
#endif

#ifdef AW_DRV_IMX1050_ACMP1
    awbl_imx1050_acmp_drv_register();
#endif

#ifdef AW_DRV_CYW43362_WIFI_SDIO
    extern void awbl_cyw43362_sdio_drv_register (void);
    awbl_cyw43362_sdio_drv_register();
#endif

#ifdef AW_DRV_CYW43362_WIFI_SPI
    extern void awbl_cyw43362_spi_drv_register (void);
    awbl_cyw43362_spi_drv_register();
#endif

#ifdef AW_DRV_AWBL_SX127X
    extern void awbl_sx127x_drv_register (void);
    awbl_sx127x_drv_register();
#endif

#ifdef AW_DRV_OV7725
    awbl_ov7725_drv_register();
#endif


#ifdef AW_DRV_IMX1050_CSI
    awbl_imx1050_csi_drv_register ();
#endif

#ifdef AW_DRV_IMX1050_RTC
    awbl_imx1050_rtc_drv_register();
#endif

#ifdef AW_DRV_IMX1050_QTIMER_CAP
    awbl_imx1050_qtimer_cap_drv_register();
#endif
}

void aw_prj_early_init (void)
{
    awbl_group_init();

    /* AWBus init phase 1 */
    awbl_dev_init1();
    awbl_intctlr_init();    /* AWBus IntCtlr service up */

#ifdef AW_COM_LED
    awbl_led_init();        /* AWBus LED service up */
#endif

#ifdef AW_COM_PWM
    awbl_pwm_init();
#endif

#ifdef AW_COM_CAP
    awbl_cap_init();
#endif

#ifdef AW_COM_I2C
    awbl_i2cbus_init();
#endif

#ifdef AW_COM_SPI
    awbl_spibus_init();
#endif

#ifdef AW_COM_ADC
    awbl_adc_init();
#endif  /* AW_COM_ADC */

#ifdef AW_DEV_IMX1050_EDMA
    awbl_imx1050_edma_init();
#endif

#ifdef AW_DEV_CAMERA
    aw_camera_serve_init();
#endif

    /*
     * Initialize serial I/O for kernel output. after this call, kprintf()
     * is ready for use
     */
#ifdef AW_COM_CONSOLE
    aw_koutput_sio_init(AW_CFG_CONSOLE_COMID, AW_CFG_CONSOLE_BAUD_RATE);
    aw_serial_ioctl(AW_CFG_CONSOLE_COMID, SIO_MODE_SET, (void *)SIO_MODE_INT);
#if AW_CFG_CONSOLE_SHOW_BANNER != 0
    aw_console_show_banner();
#endif  /* AW_CFG_CONSOLE_SHOW_BANNER */
#endif  /* AW_COM_CONSOLE */
}

void aw_prj_task_level_init (void)
{
    /* isr deferral library initialization */
    aw_isr_defer_lib_init();
    aw_nor_defer_lib_init();

#ifdef AW_COM_EVENT
    aw_event_lib_init();        /* event lib initialization */
#endif  /* AW_COM_EVENT */

#ifdef AW_COM_INPUT_EV
    awbl_input_ev_mgr_register();
#endif

#ifdef AW_COM_IO_SYSTEM
    aw_io_lib_init();
#endif  /* AW_COM_IO_SYSTEM */

#ifdef AW_COM_BLOCK_DEV
#ifndef AW_BLOCK_DEV_EVT_CNT
#define AW_BLOCK_DEV_EVT_CNT 4
#endif
    aw_blk_dev_lib_init(AW_BLOCK_DEV_EVT_CNT);    /* block device lib initialization */
#endif  /* AW_DRV_BLOCK_DEV */

#ifdef AW_COM_FS_ROOTFS
    aw_root_fs_init();
#endif  /* AW_COM_FS_ROOTFS */

#ifdef AW_COM_FS_FATFS
    aw_fatfs_lib_init();
#endif  /* AW_COM_FS_FATFS */

#ifdef AW_COM_MTD_DEV
    aw_mtd_lib_init();
#endif

#ifdef AW_COM_FS_LFFS
    aw_lffs_lib_init();
#endif  /* AW_COM_FS_LFFS */

#ifdef AW_COM_FS_YAFFS
    aw_yaffs_lib_init();
#endif

#ifdef AW_COM_MOUNT
    aw_mount_lib_init();
//   (void)aw_mount_table_add("/sd", "/dev/sd0", "vfat", 0);
#endif  /* AW_COM_MOUNT */

#if defined(AW_COM_USBH) || defined(AW_COM_USBD)
    extern void awbl_usb_cfg (void);
    awbl_usb_cfg();
#endif

#ifdef AW_COM_WDT
    awbl_wdt_init();            /* AWBus WDT service up */
#endif  /* AW_COM_WDT */

    /* system tick initialization */
    systick_init(AW_CFG_TICKS_PER_SECOND);

    /* AWBus init phase 2 */
    awbl_dev_init2();

#ifdef AW_COM_RTC
    awbl_rtc_init(); /* AWBus RTC service up */
#endif  /* AW_COM_RTC */

    aw_time_lib_init(aw_sys_clkrate_get(),0);

//    /* AWBus init phase 3 */
//    awbl_dev_connect();

#ifdef AW_COM_SERIAL
    aw_serial_init();
#endif  /* AW_COM_SERIAL */

#ifdef AW_COM_SHELL_SERIAL
    extern aw_err_t aw_serial_shell_cfg();
    aw_serial_shell_cfg();

#ifdef AW_SHELL_SYS_CMD
    extern void aw_io_shell_init (void);
    aw_io_shell_init();

    extern void rtk_cpu_usage_shell_init (void);
    rtk_cpu_usage_shell_init();

    extern void rtk_stk_chk_shell_init (void);
    rtk_stk_chk_shell_init();
#endif  /* AW_SHELL_SYS_CMD */
#endif  /* AW_COM_SERIAL */

#ifdef AW_COM_SHELL_TELNET
    aw_telnet_shell_cfg();
#endif

#ifdef AW_COM_FTL
    aw_ftl_lib_init();
#endif

#ifdef AW_COM_LOG
    aw_loglib_cfg_init();
#endif

    /* AW_COM_NETWORK */
#ifdef AW_COM_NETWORK
    aw_net_init();

#if defined(AW_COM_SHELL_SERIAL) || defined(AW_COM_SHELL_TELNET)
#ifdef AW_NET_TOOLS
    aw_net_tools_register();
#endif
#endif
#endif

#ifdef AW_COM_LRNET
    extern void  aw_lrnet_init(void);
    aw_lrnet_init();
#endif

#ifdef AW_COM_GPRS
    extern void awbl_gprs_init (void);
    awbl_gprs_init();
    extern void sio_list_init(void);
    sio_list_init();
#endif

#ifdef AW_DRV_IMX1050_SAI
    awsa_cfg_init();
#endif

    /* AWBus init phase 3 */
    awbl_dev_connect();

#if defined (__CC_ARM)
//    void aw_cplusplus_runtime_init(void);
//    aw_cplusplus_runtime_init();
#elif defined (__GNUC__)
    void aw_cplusplus_runtime_init(void);
    aw_cplusplus_runtime_init();
#endif

}


/* end of file */
