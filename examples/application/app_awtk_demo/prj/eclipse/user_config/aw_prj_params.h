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
 * \brief AnyWhere ���̲��������ļ�
 */

#ifndef __AW_PRJ_PARAMS_H
#define __AW_PRJ_PARAMS_H

/**
 * \addtogroup grp_aw_prj_param
 * @{
 */

/*******************************************************************************
  Ӳ������
*******************************************************************************/
/**
 * \addtogroup grp_aw_plfm_params_hwcfg   Ӳ������
 *
 * -# ע�͵�����궨�弴�ɽ��ܶ�Ӧ�����裬��֮����ʹ��;
 * -# ʹ��ĳ������󣬸��������������������ᱻ�Զ����ý�������������������
 *    �����������ġ�������á���
 * -# �жϿ�������GPIO������������裬Ĭ�ϱ�ʹ�ܡ�
 * @{
 */
#define AW_DEV_IMX1050_LPUART1          /**< \brief iMX1050 LPUART1 (����1) */
//#define AW_DEV_IMX1050_LPUART2          /**< \brief iMX1050 LPUART2 (����2) */
//#define AW_DEV_IMX1050_LPUART3          /**< \brief iMX1050 LPUART3 (����3) */
//#define AW_DEV_IMX1050_LPUART4          /**< \brief iMX1050 LPUART4 (����4) */
//#define AW_DEV_IMX1050_LPUART5          /**< \brief iMX1050 LPUART5 (����5) */
//#define AW_DEV_IMX1050_LPUART6          /**< \brief iMX1050 LPUART6 (����6) */
//#define AW_DEV_IMX1050_LPUART7          /**< \brief iMX1050 LPUART7 (����7) */
//#define AW_DEV_IMX1050_LPUART8          /**< \brief iMX1050 LPUART8 (����8) */
//#define AW_DEV_IMX1050_FLEXIO2_UART0      /**< \brief FLEXIO2 UART0(flexio ģ��uart)*/
//#define AW_DEV_IMX1050_LPI2C1           /**< \brief iMX1050 LPI2C1 (I2C1)*/
//#define AW_DEV_IMX1050_LPI2C2           /**< \brief iMX1050 LPI2C2 (I2C2)*/
//#define AW_DEV_IMX1050_LPSPI1           /**< \brief iMX1050 LPSPI1 (SPI1) */
//#define AW_DEV_IMX1050_LPSPI2           /**< \brief iMX1050 LPSPI2 (SPI2) */
//#define AW_DEV_IMX1050_LPSPI3           /**< \brief iMX1050 LPSPI3 (SPI3) */
//#define AW_DEV_IMX1050_LPSPI4           /**< \brief iMX1050 LPSPI4 (SPI4) */
//#define AW_DEV_IMX1050_ENET             /**< \brief iMX1050 ENET (��������) */
#define AW_DEV_IMX1050_EDMA             /**< \brief iMX1050 eDMA */
#define AW_DEV_IMX1050_GPT1             /**< \brief iMX1050 GPT1 (GPT��ʱ��1) */
//#define AW_DEV_IMX1050_GPT2             /**< \brief iMX1050 GPT2 (GPT��ʱ��2) */
//#define AW_DEV_IMX1050_PIT              /**< \brief iMX1050 PIT (PIT��ʱ��) */
//#define AW_DEV_IMX1050_ADC1             /**< \brief iMX1050 ADC */
//#define AW_DEV_IMX1050_ADC2             /**< \brief iMX1050 ADC2 */
//#define AW_DEV_IMX1050_USDHC            /**< \brief iMX1050 USDHC (SD��) */
//#define AW_DEV_IMX1050_SAI1             /**< \brief iMX1050 SAI1 */
//#define AW_DEV_IMX1050_SAI3             /**< \brief iMX1050 SAI3 */
//#define AW_DEV_IMX1050_MQS              /**< \brief iMX1050 MQS */
//#define AW_DEV_IMX1050_OCOTP            /**< \brief iMX1050 OCOTP */
#define AW_DEV_IMX1050_FLEXSPI          /**< \brief iMX1050 FLEXSPI (���ڶ�дSPI Flash)*/
//#define AW_CFG_FLEXSPI_FLASH_MTD        /**< \brief ʹ��Flexspi flash MTD�豸 */
//#define AW_DEV_IMX1050_CAN1             /**< \brief iMX1050 FlexCAN1 */
//#define AW_DEV_IMX1050_CAN2             /**< \brief iMX1050 FlexCAN2 */
//#define AW_DEV_IMX1050_EFLEX_PWM4       /**< \brief iMX1050 eFlexPWM4 */
#define AW_DEV_IMX1050_QTIMER3_PWM        /**< \brief iMX1050 QTimer3 PWM */
//#define AW_DEV_IMX1050_QTIMER3_CAP        /**< \brief iMX1050 QTimer3 CAP */
//#define AW_DEV_IMX1050_ENC1             /**< \brief iMX1050 ������������(�����ڱ���������) */
//#define AW_DEV_IMX1050_TEMPMON          /**< \brief iMX1050 �ڲ��¶ȼ������ */
//#define AW_DEV_IMX1050_ACMP1            /**< \brief iMX1050 �ڲ�ģ��Ƚ������� */
//#define AW_DEV_IMX1050_RTC              /**< \brief iMX1050 �ڲ�SNVS RTC */
//#define AW_DEV_IMX1050_USBH1            /**< \brief USB Host 1 */
//#define AW_DEV_IMX1050_USBH2            /**< \brief USB Host 2 */
//#define AW_DEV_IMX1050_USBD             /**< \brief USB Device */
#define AW_DEV_IMX1050_SEMC             /**< \brief iMX1050 �ⲿ�洢������ */


#define AW_DEV_GPIO_LED                 /**< \brief LED */
//#define AW_DEV_GPIO_KEY                 /**< \brief ���� */
#define AW_DEV_PWM_BUZZER               /**< \brief PWM Buzzer(����������Ҫ����PWM) */
#define AW_DEV_GPIO_WDT                 /**< \brief GPIO���Ź� */
//#define AW_DEV_GPIO_I2C_0               /**< \brief GPIO ģ�� I2C */

//#define AW_DEV_SPI_FLASH0               /**< \brief ��׼ SPI FLASH0�豸(��Ҫ���ױ�׼SPI����, Ŀǰֱ��ʹ�� AW_DEV_IMX1050_FLEXSPI ����) */
//#define AW_CFG_SPI_FLASH_MTD           /* SPI flash ʹ�� ��׼ SPI FLASH MTD �ӿڲ��� */
//#define AW_CFG_SPI_FLASH_NVRAM         /* SPI flash ʹ�� ��׼ SPI FLASH NVRAM �ӿڲ��� */

#define AW_DEV_EXTEND_PCF85063          /**< \brief PCF85063ʵʱʱ��(��Ҫ����I2C����) */
//#define AW_DEV_EXTEND_PCF85263          /**< \brief PCF85263ʵʱʱ��(��Ҫ����I2C����) */
//#define AW_DEV_CYW43362_WIFI_SPI_0      /**< CYW43362 WiFiģ��(������SPI����) */

#define AW_DEV_HW480272F                /**< \brief 480 X 272 TFT��ʾ�� */
//#define AW_DEV_HW800480F                /**< \brief 800 X 480 TFT��ʾ�� */
//#define AW_DEV_HWCAP480272F             /**< \brief 480 X 272 TFT������ʾ�� */
//#define AW_DEV_HW1280720F                 /**< \brief 1280 X 720 mipi��ʾ�� */
#define AW_DEV_BU21029MUV               /**< \brief i2c���败����(��ҪI2C����) */
//#define AW_DEV_FT5X06                   /**< \brief i2c���ݴ�����(��ҪI2C����) */
//#define AW_DEV_IMX1050_TS               /**< \brief ���败���� */

#define AW_DEV_NAND_FLASH             /**< \brief NAND FLASH(��Ҫ SEMC ����)  */
//#define AW_DEV_FM175XX_SPI3_0         /**< \brief Mifare������(��ҪSPI����) */

//#define AW_DEV_SX127X                 /**< \brief LoRa sx127x  */
//#define AW_DEV_IMX1050_CSI
//#define AW_DEV_OV7725

//#define AW_DEV_GPRS_SIM800
//#define AW_DEV_GPRS_ME909S
//#define AW_DEV_GPRS_U9300C



/** @} grp_aw_plfm_params_hwcfg */




/*******************************************************************************
  �������
*******************************************************************************/
/**
 * \addtogroup grp_aw_plfm_params_sftcfg   �������
 *
 * -# ע�͵�����궨�弴�ɽ��ܶ�Ӧ���������֮����ʹ��;
 * -# ʹ��ĳ������󣬸��������������������ᱻ�Զ����ý���;
 * -# ��ĳ��Ӳ������������������������Ӳ������ʹ��ʱ��������Щ�����������
 *    �Ƿ�ʹ�ܣ��������Զ����ý�����
 * -# ע���д���(����)�������ģ���ʾ��������뱻ʹ�ܣ�ע���д���(�Զ�����)��������
 *    ��ʾ������ǿ��Ա��Զ����õģ�ͨ������Щ������ֽ��ܾͺã�
 *    �������������Լ�����Ҫ�������Ҫ�õ���ʹ�ܣ�δʹ�þͿ��Խ��ܡ�
 * @{
 */
#define AW_COM_CONSOLE          /**< \brief ����̨��������� aw_kprintf ���ʹ�ܣ�������AW_INFOF,AW_ERRF,AW_LOGF��  */
#define AW_COM_SERIAL           /**< \brief ͨ�ô������(����) */
#define AW_COM_SHELL_SERIAL       /**< \brief ʹ�ܴ���shell */
//#define AW_COM_SHELL_TELNET     /**< \brief ʹ��telentԶ������shell */
#define AW_COM_SDCARD
//#define AW_COM_NETWORK          /**< \brief ʹ������Э��ջ */
//#define AW_COM_FTPD             /**< \brief ftp server ��� */
#define AW_COM_BLOCK_DEV        /**< \brief ʹ�ܿ��豸������� */
#define AW_COM_MTD_DEV          /**< \brief ʹ�� MTD(Flash)�豸������� */

#define AW_COM_IO_SYSTEM        /**< \brief ʹ�� I/O ��ϵͳ */
#define AW_COM_FS_ROOTFS        /**< \brief ʹ�ܸ��ļ�ϵͳ */
//#define AW_COM_FS_RAWFS         /**< \brief ʹ�� RAW �ļ�ϵͳ */
#define AW_COM_FS_FATFS         /**< \brief ʹ�� FAT �ļ�ϵͳ */
#define AW_COM_FS_LFFS          /**< \brief ʹ�� LFFS �ļ�ϵͳ */
//#define AW_COM_FS_TXFS          /**< \brief ʹ���������ļ�ϵͳ */
#define AW_COM_FS_YAFFS         /**< \brief ʹ�� YAFFS �ļ�ϵͳ */
#define AW_COM_MOUNT            /**< \brief �洢����ص���� */

#define AW_COM_USBH             /**< \brief USBЭ��ջ��(Host)��� */
#define AW_COM_USBD             /**< \brief USBЭ��ջ��(Device)��� */

//#define AW_COM_FTL              /**< \brief FLASH ����㣬����MTD�豸�ľ���ĥ�𡢻������� */
//#define AW_COM_LOG              /**< \brief ϵͳ��־��� */

/** @} grp_aw_plfm_params_sftcfg */


/**
 * \name ����Զ����úͼ��
 * @{
 */
#include "aw_prj_param_auto_cfg.h"
/** @} */


/*******************************************************************************
  ��Դ����
*******************************************************************************/
/**
 * \addtogroup grp_aw_plfm_params_rescfg   ��Դ����
 * @{
 */
/**
 * \name ����̨�����Դ����
 * @{
 */
#ifdef AW_COM_CONSOLE
#define AW_CFG_CONSOLE_SHOW_BANNER      1                        /** \brief ����̨����ʱ���Ƿ���ʾ��ӭ��ʶ��0-����ʾ 1-��ʾ */
#define AW_CFG_CONSOLE_COMID            IMX1050_LPUART1_COMID    /** \brief ����̨���ں� */
#define AW_CFG_CONSOLE_BAUD_RATE        115200                   /** \brief ����̨������ */
#endif
/** @} */


/**
 * \name shell�����Դ����
 * @{
 */
#ifdef AW_COM_SHELL_SERIAL
#define AW_CFG_SHELL_THREAD_PRIO        6u                       /**< \brief serial shell �߳����ȼ� */
#define AW_CFG_SHELL_THREAD_STK_SIZ     (10 * 1024)              /**< \brief serial shell �̶߳�ջ��С */
#define AW_CFG_SHELL_SERIAL_COMID       IMX1050_LPUART1_COMID    /**< \brief serial shell ʹ�õĴ����豸�� */
#define AW_SHELL_SYS_CMD                                         /**< \brief ʹ��shell IO��������:"ls" "cd" "mkdir"������ */
#endif

#ifdef AW_COM_SHELL_TELNET
#define AW_CFG_TELNET_TASK_PRIO         1       /**< \brief telent shell �߳����ȼ�  */
#define AW_CFG_TELNET_TASK_STACK_SIZE   8192    /**< \brief telent shell �̶߳�ջ��С */
#define AW_CFG_TELNET_MAX_SESSION       2       /**< \brief telent shell ���ͬʱ������Ŀ */
#define AW_CFG_TELNET_LISTEN_PORT       23      /**< \brief telent shell ����˿ں� */
#define AW_CFG_TELNET_USER_NAME         "admin" /**< \brief telent shell �û������� */
#define AW_CFG_TELNET_USER_PSW          "123456" /**< \brief telent shell �û��������� */
#endif
/** @} */

/**
 * \name net tools
 * @{
 */
#define AW_NET_TOOLS                    /**< \brief ʹ���������������ù��� */
/** @} */


/** \name �¼�ϵͳ��Դ����
 * @{
 */
#ifdef AW_COM_EVENT
#define AW_CFG_EVENT_TASK_STK_SIZE  4096    /**< \brief �¼���ܴ��������ջ��С */
#define AW_CFG_EVENT_TASK_PRIO      8       /**< \brief �¼���ܴ����������ȼ� */
#define AW_CFG_EVENT_MSG_NUM        16      /**< \brief �¼������󲢷���Ϣ���� */

//#define AW_COM_INPUT_EV                /**< \brief ʹ�������¼����� */
//#define AW_COM_INPUT_EV_KEY            /**< \brief ʹ�ܰ����¼� */
//#define AW_COM_INPUT_EV_ABS            /**< \brief ʹ�ܾ����¼����������¼���������� */
#endif
/** @} */


/**
 * \name FTP �����Դ����
 * FTP �����Ҫ�ļ�ϵͳ֧�֣������Ҫ���ļ�ϵͳ��������Ҫ�����ļ�ϵͳ��mount�ӿڣ�
 * ����һ���ļ����ڵ�
 * @{
 */
#ifdef AW_COM_FTPD
#define FTPD_MAX_SESSIONS            10         /**< \brief FTPD ���ͬʱ������Ŀ */
#define FTPD_LISTEN_TASK_PRIO        6          /**< \brief FTPD �������ȼ� */
#define FTPD_LISTEN_TASK_STK_SIZE    4096       /**< \brief FTPD ջ��С */
#define FTPD_CMD_BUF_SIZE            0x10000    /**< \brief FTPD ����buffer ��С */
#endif
/** @} */


/**
 * \name ���豸�������ͳ��Դ����
 * @{
 */
#ifdef AW_COM_BLOCK_DEV
#define AW_BLOCK_DEV_EVT_CNT   5
#endif
/** @} */


/** \name I/O ϵͳ�ü�����
 * @{
 */
#ifdef AW_COM_IO_SYSTEM
#define AW_CFG_IO_OPEN_FILES_MAX    10
#endif
/** @} */


/** \name I/O ϵͳ�洢����ص�ü�����
 * @{
 */
#ifdef AW_COM_MOUNT
#define AW_CFG_MOUNT_POINTS         5
#endif
/** @} */


/** \name RAW�ļ�ϵͳ��Դ����
 * @{
 */
#ifdef AW_COM_FS_RAWFS
#define AW_CFG_RAWFS_VOLUMES    1   /**< \brief RAW �ļ�ϵͳ����� */
#define AW_CFG_RAWFS_FILES      1   /**< \brief RAW �ļ�ϵͳͬʱ���ļ���*/
#define AW_CFG_RAWFS_BLOCK_SIZE 512 /**< \brief RAW �ļ�ϵͳ�����С */
#endif
/** @} */


/** \name FAT�ļ�ϵͳ��Դ����
 * @{
 */
#ifdef AW_COM_FS_FATFS
#define AW_CFG_FATFS_VOLUMES    3    /**< \brief FAT �ļ�ϵͳ����� */
#define AW_CFG_FATFS_FILES      10    /**< \brief FAT �ļ�ϵͳͬʱ���ļ��� */
#define AW_CFG_FATFS_BLOCK_SIZE 4096 /**< \brief FAT �ļ�ϵͳ�����С */
#endif
/** @} */


/** \name LFFS�ļ�ϵͳ��Դ����
 * @{
 */
#ifdef AW_COM_FS_LFFS
#define AW_CFG_LFFS_VOLUMES     2   /**< \brief LFFS �ļ�ϵͳ����� */
#define AW_CFG_LFFS_FILES       10   /**< \brief LFFS �ļ�ϵͳͬʱ���ļ���*/
#endif
/** @} */


/** \name TFFS�ļ�ϵͳ��Դ����
 * @{
 */
#ifdef AW_COM_FS_TXFS
#define AW_CFG_TXFS_VOLUMES     2   /**< \brief TXFS �ļ�ϵͳ����� */
#define AW_CFG_TXFS_FILES       10   /**< \brief TXFS �ļ�ϵͳͬʱ���ļ���*/
#define AW_CFG_TXFS_BUF_CNT     50  /** \brief TXFS �ļ�ϵͳ���������ֵԽ���дԽ�죬�������ʧ����Խ�� */
#endif
/** @} */


/** \name YAFFS�ļ�ϵͳ��Դ����
 * @{
 */
#ifdef AW_COM_FS_YAFFS
#define AW_CFG_YAFFS_VOLUMES     2   /**< \brief YAFFS �ļ�ϵͳ����� */
#define AW_CFG_YAFFS_FILES       10   /**< \brief YAFFS �ļ�ϵͳͬʱ���ļ���*/
#endif
/** @} */


/** \name USBЭ��ջ�ü�����
 * @{
 */
#ifdef AW_COM_USBH
#define AW_DRV_USBH_MASS_STORAGE               /**< \brief �������洢����(U��&Ӳ��) */
#endif
#if defined(AW_COM_USBH) || defined(AW_COM_USBD)
#define AW_CFG_USB_MEM_SIZE          (128 * 1024)  /**< \brief USBЭ��ջ�ڴ�ʹ�ÿռ��С */
#endif
#ifdef AW_DRV_USBH_MASS_STORAGE
#define AW_CFG_USB_MS_BUF_SIZE       (16 * 1024)  /**< \brief U�����ݽ������棬ռ��AW_CFG_USB_MEM_SIZE�ռ䣬Ӱ��U�̶�д���ܣ��Ƽ�16k */
#endif
/** @} */


/** \name ϵͳCOM����Դ����(���������USBת�����豸)
 * @{
 */
#define AW_CFG_NUM_COM              10  /**< \brief ϵͳCOM�˿ڸ���, ��ǰ֧�ֵ����˿ڸ���Ϊ10����Ӧ�ø���ʵ�ʵ�Ӳ�������޸� */

/**< \brief ���õĴ��ж˿ڣ���ų���AW_CFG_NUM_COM�������ò������á� */
#define AW_CFG_COM0_TX_BUF_SIZE     128     /**< \brief COM0 ���ͻ����С */
#define AW_CFG_COM0_RX_BUF_SIZE     128     /**< \brief COM0 ���ջ����С */

#define AW_CFG_COM1_TX_BUF_SIZE     128     /**< \brief COM1 ���ͻ����С */
#define AW_CFG_COM1_RX_BUF_SIZE     128     /**< \brief COM1 ���ջ����С */

#define AW_CFG_COM2_TX_BUF_SIZE     128     /**< \brief COM2 ���ͻ����С */
#define AW_CFG_COM2_RX_BUF_SIZE     128     /**< \brief COM2 ���ջ����С */

#define AW_CFG_COM3_TX_BUF_SIZE     128     /**< \brief COM3 ���ͻ����С */
#define AW_CFG_COM3_RX_BUF_SIZE     128     /**< \brief COM3 ���ջ����С */

#define AW_CFG_COM4_TX_BUF_SIZE     128     /**< \brief COM4 ���ͻ����С */
#define AW_CFG_COM4_RX_BUF_SIZE     128     /**< \brief COM4 ���ջ����С */

#define AW_CFG_COM5_TX_BUF_SIZE     128     /**< \brief COM5 ���ͻ����С */
#define AW_CFG_COM5_RX_BUF_SIZE     128     /**< \brief COM5 ���ջ����С */

#define AW_CFG_COM6_TX_BUF_SIZE     128     /**< \brief COM6 ���ͻ����С */
#define AW_CFG_COM6_RX_BUF_SIZE     128     /**< \brief COM6 ���ջ����С */

#define AW_CFG_COM7_TX_BUF_SIZE     128     /**< \brief COM7 ���ͻ����С */
#define AW_CFG_COM7_RX_BUF_SIZE     128     /**< \brief COM7 ���ջ����С */

#define AW_CFG_COM8_TX_BUF_SIZE     128     /**< \brief COM8 ���ͻ����С */
#define AW_CFG_COM8_RX_BUF_SIZE     128     /**< \brief COM8 ���ջ����С */

#define AW_CFG_COM9_TX_BUF_SIZE     128     /**< \brief COM9 ���ͻ����С */
#define AW_CFG_COM9_RX_BUF_SIZE     128     /**< \brief COM9 ���ջ����С */
/** @} */


/** \name system��Դ����
 * @{
 */
#define AW_CFG_TICKS_PER_SECOND             1000                    /** \brief ϵͳʱ�ӽ���Ƶ������ */
#define AW_CFG_MAIN_TASK_STACK_SIZE         (1024 * 10)              /** \brief main�����ջ��С���Ƽ� >= 512 */
#define AW_CFG_MAIN_TASK_PRIO               1                       /** \brief main�������ȼ� */

#define AW_CFG_ISR_DEFER_TASK_PRIO          AW_TASK_SYS_PRIORITY(0) /** \brief ISR defer(ϵͳ��������ȼ��ӳ���ҵ) ���� */
#define AW_CFG_ISR_DEFER_TASK_CNT           3                       /** \brief ������������ */
#define AW_CFG_ISR_DEFER_TASK_STACK_SIZE    (1024 * 10)             /** \brief ÿ������ջ��С */

#define AW_CFG_NOR_DEFER_TASK_PRIO          7                       /** \brief Normal defer(ϵͳ������ͨ���ȼ��ӳ���ҵ) ���� */
#define AW_CFG_NOR_DEFER_TASK_CNT           3                       /** \brief ������������ */
#define AW_CFG_NOR_DEFER_TASK_STACK_SIZE    (1024 * 10)             /** \brief ÿ������ջ��С */

#define AW_CFG_AWBUS_LITE_DRIVER_MAX        80                      /** \brief AWBus lite ֧�ֵ����������  */
#define AW_CFG_AWBUS_LITE_BUSTYPE_MAX       16                      /** \brief AWBus lite ֧�ֵ��������������  */

#define AW_CFG_ARMCM_NVIC_ISRINFO_COUNT     42                      /** \brief �ж�������  */
/** @} */

/** @} grp_aw_plfm_params_rescfg */





/*******************************************************************************
  ��ԴID
*******************************************************************************/
/**
 * \addtogroup grp_aw_plfm_params_idcfg   ��ԴID����
 * @{
 */
/* ENET ID ���� */
#define IMX1050_MII_BUSID               0

/* LPSPI ID���� */
#define IMX1050_LPSPI1_BUSID            0
#define IMX1050_LPSPI2_BUSID            1
#define IMX1050_LPSPI3_BUSID            2
#define IMX1050_LPSPI4_BUSID            3

/* Timer ID���� */
#define IMX1050_GPT1_BUSID              1
#define IMX1050_GPT2_BUSID              2
/* Timer ID���� */
#define IMX1050_PIT_BUSID               0

/* I2C  ID���� */
#define IMX1050_LPI2C1_BUSID            1
#define IMX1050_LPI2C2_BUSID            2
#define IMX1050_LPI2C3_BUSID            3
#define IMX1050_LPI2C4_BUSID            4
#define IMX1050_GPIO_I2C0_BUSID         5

/* ���� ID ���� */
#define IMX1050_LPUART1_COMID           COM0
#define IMX1050_LPUART2_COMID           COM1
#define IMX1050_LPUART3_COMID           COM2
#define IMX1050_LPUART4_COMID           COM3
#define IMX1050_LPUART5_COMID           COM4
#define IMX1050_LPUART6_COMID           COM5
#define IMX1050_LPUART7_COMID           COM6
#define IMX1050_LPUART8_COMID           COM7
#define IMX1050_FLEXIO2_UART0_COMID     COM8

/* CAN ID���� */
#define IMX1050_FLAX_CAN1_BUSID         0
#define IMX1050_FLAX_CAN2_BUSID         1

/* USB���� ID ���� */
#define IMX1050_USBH1_BUSID             0
#define IMX1050_USBH2_BUSID             1

/* ENC ID ���� */
#define IMX1050_ENC1                    1
#define IMX1050_ENC2                    2
#define IMX1050_ENC3                    3
#define IMX1050_ENC4                    4

/* ACMP ID ���� */
#define IMX1050_ACMP1                   1
#define IMX1050_ACMP2                   2
#define IMX1050_ACMP3                   3
#define IMX1050_ACMP4                   4

/* PWM ID���� */
/* ����eFlex PWM4 */
#define PWM0                            0
#define PWM1                            1
#define PWM2                            2
#define PWM3                            3
#define PWM4                            4
#define PWM5                            5
#define PWM6                            6
#define PWM7                            7

/* NAND���� ID ���� */
#define IMX1050_NAND0_BUSID             0

/* ����QTimer3 PWM*/
#define PWM8                            8
#define PWM9                            9
#define PWM10                           10
#define PWM11                           11

/* RTC ID ���� */
#define RTC_ID0                         0
#define RTC_ID1                         1

/* ����QTimer3 CAP */
#define QTIMER3_CAP0                    0
#define QTIMER3_CAP1                    1
#define QTIMER3_CAP2                    2
#define QTIMER3_CAP3                    3


/** @} grp_aw_plfm_params_idcfg */

/** @} grp_aw_prj_param */

#include "aw_prj_param_auto_cfg.h"
#endif  /* __AW_PRJ_PARAMS_H */

/* end of file */
