/*******************************************************************************

*                                 AWorks
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

/**
 * \file
 * \brief AnyWhere 工程参数自动配置文件
 */

#ifndef __AW_PRJ_PARAMS_AUTO_CFG_H
#define __AW_PRJ_PARAMS_AUTO_CFG_H




/**
 * \name 目前系统事件组件默认必须要打开
 * @{
 */
#ifndef AW_COM_EVENT
#define AW_COM_EVENT            /**< \brief 使能事件系统 */
#endif




/*
 * WiFi dependency:
 *     MCU <=> WiFi
 *     MCU <=> SPI FLASH(NVRAM)
 */
#if defined(AW_DEV_CYW43362_WIFI_SPI_0) || defined(AW_DEV_CYW43362_WIFI_SDIO_0)
    #ifndef AW_COM_NETWORK
        #define AW_COM_NETWORK
    #endif

    #ifdef AW_DEV_CYW43362_WIFI_SPI_0
        #define AW_DRV_AWBL_CYW43362_WIFI_SPI
        #define AW_DRV_CYW43362_WIFI_SPI
        /* MCU <=> WiFi */
        #ifndef AW_DEV_IMX1050_LPSPI3
            #define AW_DEV_IMX1050_LPSPI3
        #endif
    #else
        #error "Not support!"
        #define AW_DRV_CYW43362_WIFI_SDIO
        /* MCU <=> WiFi */
        #ifndef AW_DEV_xxx_SDIO1
            #define AW_DEV_xxx_SDIO1
        #endif
        // #ifdef AW_DEV_xxx_SPI1
        //     #error "AW_DEV_xxx_SPI1 AW_DEV_xxx_SDIO1 share the same hw!"
        // #endif
    #endif
#endif




/**
 * \name SHELL 串口依赖串口设备
 * @{
 */
#ifdef AW_COM_SHELL_SERIAL
#ifndef AW_COM_SERIAL
#define AW_COM_SERIAL
#endif

#ifndef AW_DEV_IMX1050_LPUART1
#define AW_DEV_IMX1050_LPUART1
#endif
#endif




/**
 * \name 外部FM175XX mifare读卡模块
 * @{
 */
#ifdef AW_DEV_FM175XX_SPI3_0
#define AW_DRV_FM175XX

#ifndef AW_DEV_IMX1050_LPSPI3
#define AW_DEV_IMX1050_LPSPI3
#endif
#endif
/** @} */




/**
 * \name GPRS设备
 * @{
 */
#if defined(AW_DEV_GPRS_SIM800) || \
    defined(AW_DEV_GPRS_ME909S) || \
    defined(AW_DEV_GPRS_U9300C)
#ifndef AW_COM_NETWORK
#define AW_COM_NETWORK
#endif
#define AW_COM_GPRS
#endif

#if defined(AW_DEV_GPRS_ME909S) || \
    defined(AW_DEV_GPRS_U9300C)
#define AW_DRV_USBH_WIRELESS                   /**< \brief 移动无线网络驱动(anydata、华为、龙尚等系列3G/4G模块) */
#endif
/** @} */




/**
 * \name 外部NandFlash
 * @{
 */
#ifdef AW_DEV_NAND_FLASH
#ifndef AW_COM_NANDBUS
#define AW_COM_NANDBUS
#endif

#ifndef AW_COM_MTD_DEV
#define AW_COM_MTD_DEV
#endif

#define AW_DRV_NANDFLASH

#ifndef AW_DEV_IMX1050_SEMC
#define AW_DEV_IMX1050_SEMC
#endif
#endif
/** @} */




/**
 * \name 外部RTC芯片PCF85063
 * @{
 */
#ifdef AW_DEV_EXTEND_PCF85063
#ifndef AW_COM_RTC
#define AW_COM_RTC
#endif
#define AW_DRV_EXTEND_PCF85063
#define AW_DEV_IMX1050_LPI2C1
#endif
/** @} */


/**
 * \name 外部RTC芯片PCF85263
 * @{
 */
#ifdef AW_DEV_EXTEND_PCF85263
#ifndef AW_COM_RTC
#define AW_COM_RTC
#endif
#define AW_DRV_EXTEND_PCF85263
#define AW_DEV_IMX1050_LPI2C1
#endif
/** @} */


/**
 * \name 内部 SNVS RTC
 * @{
 */
#ifdef AW_DEV_IMX1050_RTC
#ifndef AW_COM_RTC
#define AW_COM_RTC
#endif
#define AW_DRV_IMX1050_RTC
#endif
/** @} */


/**
 * \name 外部电阻触摸屏(I2C接口)
 * @{
 */
#ifdef  AW_DEV_BU21029MUV
#define AW_DRV_BU21029MUV_TS
#define AW_DEV_IMX1050_LPI2C1
#endif
/** @} */




/**
 * \name 外部电容触摸屏(I2C接口)
 * @{
 */
#ifdef  AW_DEV_FT5X06
#define AW_DRV_FT5X06_TS
#define AW_DEV_IMX1050_LPI2C1
#endif
/** @} */





/**
 * \name LPUART
 * @{
 */
#if defined AW_DEV_IMX1050_LPUART1  || \
    defined AW_DEV_IMX1050_LPUART2  || \
    defined AW_DEV_IMX1050_LPUART3  || \
    defined AW_DEV_IMX1050_LPUART4  || \
    defined AW_DEV_IMX1050_LPUART5  || \
    defined AW_DEV_IMX1050_LPUART6  || \
    defined AW_DEV_IMX1050_LPUART7  || \
    defined AW_DEV_IMX1050_LPUART8

#ifndef AW_COM_SERIAL
#define AW_COM_SERIAL
#endif

#define AW_DRV_IMX1050_LPUART

#endif
/** @} */




/**
 * \name I2C
 * @{
 */
#if defined AW_DEV_IMX1050_LPI2C1  || \
    defined AW_DEV_IMX1050_LPI2C2  || \
    defined AW_DEV_IMX1050_LPI2C3  || \
    defined AW_DEV_IMX1050_LPI2C4

#ifndef AW_COM_I2C
#define AW_COM_I2C
#endif

#define AW_DRV_IMX1050_LPI2C

#endif
/** @} */




/**
 * \name SPI
 * @{
 */
#if defined AW_DEV_IMX1050_LPSPI1  || \
    defined AW_DEV_IMX1050_LPSPI2  || \
    defined AW_DEV_IMX1050_LPSPI3  || \
    defined AW_DEV_IMX1050_LPSPI4

#ifndef AW_COM_SPI
#define AW_COM_SPI
#endif

#define AW_DRV_IMX1050_LPSPI

#endif
/** @} */





/**
 * \name 以太网
 * @{
 */
#ifdef AW_DEV_IMX1050_ENET

#ifndef AW_COM_NETWORK
#define AW_COM_NETWORK
#endif

#define AW_DRV_IMX1050_ENET

#define AW_DEV_KSZ8081_PHY0
#define AW_DEV_GENERIC_PHY0
#endif
/** @} */




/**
 * \name 内部独立看门狗
 * @{
 */
#if defined AW_DEV_IMX1050_WDT1

#ifndef AW_COM_WDT
#define AW_COM_WDT
#endif

#define AW_DRV_IMX1050_WDT
#endif
/** @} */




/**
 * \name 内部窗口看门狗
 * @{
 */
#if defined AW_DEV_IMX1050_RTWDT

#ifndef AW_COM_WDT
#define AW_COM_WDT
#endif

#define AW_DRV_IMX1050_RTWDT
#endif
/** @} */




/**
 * \name DMA
 * @{
 */
#ifdef AW_DEV_IMX1050_EDMA
#define AW_DRV_IMX1050_EDMA
#endif
/** @} */




/**
 * \name GPT(定时器)
 * @{
 */
#if defined AW_DEV_IMX1050_GPT1  || \
    defined AW_DEV_IMX1050_GPT2
#define AW_DRV_IMX1050_GPT
#endif
/** @} */




/**
 * \name PIT(定时器)
 * @{
 */
#ifdef AW_DEV_IMX1050_PIT
#define AW_DRV_IMX1050_PIT
#endif
/** @} */




/**
 * \name 内部ADC
 * @{
 */
#if defined  AW_DEV_IMX1050_ADC1 || \
    defined  AW_DEV_IMX1050_ADC2

#ifndef AW_COM_ADC
#define AW_COM_ADC
#endif

#define AW_DRV_IMX1050_ADC
#endif
/** @} */



/**
 * \name SDIO外设
 * @{
 */
#ifdef AW_DEV_IMX1050_USDHC
#ifndef AW_COM_SDIOBUS
#define AW_COM_SDIOBUS
#endif

#define AW_DRV_IMX1050_USDHC
#endif
/** @} */




/**
 * \name SAI
 * @{
 */
#if defined AW_DEV_IMX1050_SAI1 || \
    defined AW_DEV_IMX1050_SAI2 || \
    defined AW_DEV_IMX1050_SAI3
#define AW_DRV_IMX1050_SAI
#endif
/** @} */




/**
 * \name MQS
 * @{
 */
#ifdef AW_DEV_IMX1050_MQS
#define AW_DRV_IMX1050_MQS
#endif
/** @} */




/**
 * \name 内部OTP存储器
 * @{
 */
#ifdef AW_DEV_IMX1050_OCOTP
#define AW_DRV_IMX1050_OCOTP
#endif
/** @} */




/**
 * \name FlexSPI
 * @{
 */
#ifdef AW_DEV_IMX1050_FLEXSPI
#define AW_DRV_IMX1050_FLEXSPI

#ifdef AW_CFG_FLEXSPI_FLASH_MTD
#define  AW_COM_MTD_DEV
#endif
#endif
/** @} */




/**
 * \name 内部CAN控制器
 * @{
 */
#if defined AW_DEV_IMX1050_CAN1 || \
    defined AW_DEV_IMX1050_CAN2

#define AW_DRV_IMX1050_CAN

#endif
/** @} */




/**
 * \name 内部触摸屏接口
 * @{
 */
#ifdef AW_DEV_IMX1050_TS
#define AW_DRV_IMX1050_TS
#endif
/** @} */




/**
 * \name 内部eFlexPWM
 * @{
 */
#ifdef AW_DEV_IMX1050_EFLEX_PWM4
#ifndef AW_COM_PWM
#define AW_COM_PWM
#endif

#define AW_DRV_IMX1050_EFLEX_PWM
#endif
/** @} */




/**
 * \name 内部QTIMER PWM
 * @{
 */
#ifdef AW_DEV_IMX1050_QTIMER3_PWM
#ifndef AW_COM_PWM
#define AW_COM_PWM
#endif

#define AW_DRV_IMX1050_QTIMER_PWM
#endif
/** @} */


/**
 * \name 内部QTIMER CAP
 * @{
 */
#ifdef AW_DEV_IMX1050_QTIMER3_CAP
#ifndef AW_COM_CAP
#define AW_COM_CAP
#endif

#define AW_DRV_IMX1050_QTIMER_CAP
#endif
/** @} */



/**
 * \name 内部ENC(正交解码器)设备
 * @{
 */
#ifdef AW_DEV_IMX1050_ENC1
#define AW_DRV_IMX1050_ENC1
#endif
/** @} */




/**
 * \name 内部温度传感器
 * @{
 */
#ifdef AW_DEV_IMX1050_TEMPMON
#ifndef AW_COM_TEMPMON
#define AW_COM_TEMPMON
#endif
#define AW_DRV_IMX1050_TEMPMON
#endif
/** @} */




/**
 * \name 内部ACMP模拟比较器
 * @{
 */
#ifdef AW_DEV_IMX1050_ACMP1
#define AW_DRV_IMX1050_ACMP1
#endif
/** @} */




/**
 * \name 内部USB host控制器
 * @{
 */
#if defined AW_DEV_IMX1050_USBH1 || \
    defined AW_DEV_IMX1050_USBH2
#ifndef AW_COM_USBH
#define AW_COM_USBH
#endif
#define AW_DRV_IMX1050_USBH
#endif
/** @} */




/**
 * \name 内部USB Device控制器
 * @{
 */
#ifdef AW_DEV_IMX1050_USBD
#ifndef AW_COM_USBD
#define AW_COM_USBD
#endif
#define AW_DRV_IMX1050_USBD
#endif
/** @} */




/**
 * \name 外部存储总线控制器
 * @{
 */
#ifdef AW_DEV_IMX1050_SEMC
#define AW_DRV_IMX1050_SEMC
#endif
/** @} */




/**
 * \name FLEXIO2 to UART
 * @{
 */
#if defined AW_DEV_IMX1050_FLEXIO2_UART0 || \
    defined AW_DEV_IMX1050_FLEXIO2_UART1
#ifndef AW_COM_SERIAL
#define AW_COM_SERIAL
#endif
#define AW_DRV_IMX1050_FLEXIO_UART
#endif
/** @} */




/**
 * \name LED设备
 * @{
 */
#ifdef AW_DEV_GPIO_LED
#ifndef AW_COM_LED
#define AW_COM_LED
#endif
#define AW_DRV_GPIO_LED
#endif
/** @} */




/**
 * \name 外部GPIO 看门狗
 * @{
 */
#ifdef AW_DEV_GPIO_WDT
#ifndef AW_COM_WDT
#define AW_COM_WDT
#endif
#define AW_DRV_GPIO_WDT
#endif
/** @} */




/**
 * \name 无源蜂鸣器(PWM)
 * @{
 */
#ifdef AW_DEV_PWM_BUZZER
#define AW_DRV_PWM_BUZZER
#endif
/** @} */




/**
 * \name 独立按键
 * @{
 */
#ifdef AW_DEV_GPIO_KEY
#define AW_DRV_GPIO_KEY
#define AW_COM_EVENT
#define AW_COM_INPUT_EV                /**< \brief 使能输入事件管理 */
#define AW_COM_INPUT_EV_KEY            /**< \brief 使能按键事件 */
#endif
/** @} */




/**
 * \name I2C(GPIO模拟)
 * @{
 */
#ifdef AW_DEV_GPIO_I2C_0
#ifndef AW_COM_I2C
#define AW_COM_I2C
#endif
#define AW_DRV_GPIO_I2C_0
#endif
/** @} */


/**
 * \name OV7725设备
 * @{
 */
#ifdef AW_DEV_OV7725
#define AW_DRV_OV7725
#ifndef AW_DEV_CAMERA
#define AW_DEV_CAMERA
#endif
#endif
/** @} */


/**
 * \name CSI控制器
 * @{
 */
#ifdef AW_DEV_IMX1050_CSI
#define AW_DRV_IMX1050_CSI
#endif
/** @} */

/**
 * \name SPI Flash(标准SPI接口)
 * @{
 */
#if defined (AW_DEV_SPI_FLASH1) || \
    defined (AW_DEV_SPI_FLASH0)
#define AW_DRV_SPI_FLASH
#endif
/** @} */



/**
 * \name LoRa sx127x
 * @{
 */
#ifdef AW_DEV_SX127X
#define AW_DRV_AWBL_SX127X
#define AW_COM_LRNET
#endif
/** @} */




/**
 * \name 显示面板
 * @{
 */
#if defined  AW_DEV_HW480272F || \
    defined  AW_DEV_HWCAP480272F || \
    defined  AW_DEV_HW800480F || \
    defined  AW_DEV_HW1280720F
#define AW_DRV_TFT_PANEL
#define AW_DRV_EMWIN_FB
#define AW_DEV_EMWIN_FB
#endif
/** @} */




/**
 * \name 华为ME909S
 * @{
 */
#ifdef AW_DEV_GPRS_ME909S
#define AW_DRV_GPRS_ME909S
#endif
/** @} */




/**
 * \name SIM800 GPRS
 * @{
 */
#ifdef AW_DEV_GPRS_SIM800
#define AW_DRV_GPRS_SIM800
#endif
/** @} */




/**
 * \name 龙尚U9300
 * @{
 */
#ifdef AW_DEV_GPRS_U9300C
#define AW_DRV_GPRS_U9300C
#endif
/** @} */




/**
 * \name 文件系统依赖与IO子系统
 * @{
 */
#if defined AW_COM_FS_RAWFS || \
    defined AW_COM_FS_FATFS || \
    defined AW_COM_FS_LFFS || \
    defined AW_COM_FS_TXFS

#ifndef AW_COM_IO_SYSTEM
#define AW_COM_IO_SYSTEM
#endif

#ifndef AW_COM_MOUNT
#define AW_COM_MOUNT
#endif

#ifndef AW_COM_FS_ROOTFS
#define AW_COM_FS_ROOTFS
#endif
#endif
/** @} */




/**
 * \name 部分文件系统依赖块设备
 * @{
 */
#if defined AW_COM_FS_RAWFS || \
    defined AW_COM_FS_FATFS || \
    defined AW_COM_FS_TXFS
#ifndef AW_COM_BLOCK_DEV
#define AW_COM_BLOCK_DEV
#endif
#endif
/** @} */




/**
 * \name 部分文件系统依赖mtd设备
 * @{
 */
#if defined AW_COM_FS_LFFS
#ifndef AW_COM_MTD_DEV
#define AW_COM_MTD_DEV
#endif
#endif
/** @} */




/*******************************************************************************
  冲突检测
*******************************************************************************/
/** \cond */
#if defined(AW_DEV_IMX1050_WDT1) && defined(AW_DEV_IMX1050_RTWDT)
#error "AW_DEV_IMX1050_WDT1 and AW_DEV_IMX1050_RTWDT cannot defined at the same time!"
#endif

/* 不能同时使用ADC1和ADC2 */
//#if defined(AW_DEV_IMX1050_ADC1) && defined(AW_DEV_IMX1050_ADC2)
//#error "AW_DEV_IMX1050_ADC1 and AW_DEV_IMX1050_ADC2  cannot defined at the same time!"
//#endif

/* 不能同时使用480 X 272 TFT显示屏和 800 X 480 TFT显示屏 */
#if (defined(AW_DEV_HW480272F) || defined(AW_DEV_HWCAP480272F)) && defined(AW_DEV_HW800480F)
#error "AW_DEV_HW480272F(AW_DEV_HWCAP480272F)and AW_DEV_HW800480F  cannot defined at the same time!"
#endif

/* 不能同时使用USB Device和USB HOST1 */
#if defined(AW_DEV_IMX1050_USBH1) && defined(AW_DEV_IMX1050_USBD)
#error "AW_DEV_IMX1050_USBH1 and AW_DEV_IMX1050_USBD  cannot defined at the same time!"
#endif

/* 不能同时使用USB Device和USB HOST1 */
#if defined(AW_DEV_CYW43362_WIFI_SPI_0) && defined(AW_DEV_CYW43362_WIFI_SDIO_0)
#error "AW_DEV_CYW43362_WIFI_SPI_0 and AW_DEV_CYW43362_WIFI_SDIO_0  cannot defined at the same time!"
#endif

/* 不能同时使用USB Device和USB HOST1 */
#if defined(AW_DEV_CYW43362_WIFI_SPI_0) && defined(AW_DEV_IMX1050_TS)
#error "AW_DEV_CYW43362_WIFI_SPI_0 and AW_DEV_IMX1050_TS  cannot defined at the same time!"
#endif

/* 网络工具必须依赖网络组件 */
#ifndef AW_COM_NETWORK
#warning "AW_NET_TOOLS can not work without AW_COM_NETWORK"
#undef AW_NET_TOOLS
#endif

/* 摄像头引脚与以太网和I2C1冲突 */
#if defined(AW_DEV_OV7725) && (defined(AW_DEV_IMX1050_ENET) || defined(AW_DEV_IMX1050_LPI2C1))
#error "AW_DEV_OV7725 and AW_DEV_IMX1050_ENET or AW_DEV_IMX1050_LPI2C1  cannot defined at the same time!"
#endif

/* QTimer3的PWM和CAP功能不能同时使用 */
#if defined(AW_DEV_IMX1050_QTIMER3_PWM) && defined(AW_DEV_IMX1050_QTIMER3_CAP)
#error "AW_DEV_IMX1050_QTIMER3_PWM and AW_DEV_IMX1050_QTIMER3_CAP cannot defined at the same time!"
#endif


#endif  /* __AW_PRJ_PARAMS_AUTO_CFG_H */

/* end of file */
