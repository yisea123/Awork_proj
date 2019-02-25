/*******************************************************************************
*                                 AWorks
*                       ---------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2016 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

#ifndef __AWBL_HWCONF_HW1280720F_H
#define __AWBL_HWCONF_HW1280720F_H

#ifdef AW_DEV_HW1280720F

/*******************************************************************************
  HW1280720 配置信息
*******************************************************************************/
#include "driver/display/awbl_imx1050_tft_panel.h"


#define __HW1280720_X_RES        720
#define __HW1280720_Y_RES        1280

#define __HW1280720_BPP          16

/* 注：由于频率较高, 建议使用高质量,尽可能短的排线连接屏和底板 */
#define __HW1280720_DCLK_F       48000000

#define DOTCLK_H_ACTIVE         __HW1280720_X_RES
#define DOTCLK_H_PULSE_WIDTH    1
#define DOTCLK_HF_PORCH         20
#define DOTCLK_HB_PORCH         10
#define DOTCLK_H_WAIT_CNT       (DOTCLK_H_PULSE_WIDTH + (3 * DOTCLK_HB_PORCH))
#define DOTCLK_H_PERIOD         (DOTCLK_H_WAIT_CNT + DOTCLK_HF_PORCH + DOTCLK_H_ACTIVE)

#define DOTCLK_V_ACTIVE         __HW1280720_Y_RES
#define DOTCLK_V_PULSE_WIDTH    1
#define DOTCLK_VF_PORCH         30
#define DOTCLK_VB_PORCH         10
#define DOTCLK_V_WAIT_CNT       (DOTCLK_VF_PORCH + DOTCLK_VB_PORCH)
#define DOTCLK_V_PERIOD         (DOTCLK_VF_PORCH + DOTCLK_V_ACTIVE + DOTCLK_V_WAIT_CNT)

#define SSD2828_RST_SET()       aw_gpio_set(GPIO1_8, 1)
#define SSD2828_RST_CLR()       aw_gpio_set(GPIO1_8, 0)

#define SSD2828_CS_SET()        aw_gpio_set(GPIO1_28, 1U)
#define SSD2828_CS_CLR()        aw_gpio_set(GPIO1_28, 0U)

#define SSD2828_SCK_SET()       aw_gpio_set(GPIO1_31, 1U)
#define SSD2828_SCK_CLR()       aw_gpio_set(GPIO1_31, 0U)

#define SSD2828_MOSI_SET()      aw_gpio_set(GPIO1_30, 1U)
#define SSD2828_MOSI_CLR()      aw_gpio_set(GPIO1_30, 0U)

#define HBPD                    60
#define HFPD                    72
#define HSPW                    20
#define VBPD                    27
#define VFPD                    20
#define VSPW                    4

typedef enum ssd2828_send_flg {
    SSD2828_SEND_CMD = 0,
    SSD2828_SEND_DATA = 1,
} ssd2828_send_flg_t;


typedef struct __hw1280720f_gpio_cfg {
    int         gpio;
    uint32_t    func;

} __hw1280720f_gpio_cfg_t;


aw_local aw_const  __hw1280720f_gpio_cfg_t __g_hw1280720f_gpios_list[] = {

    {GPIO1_10, AW_GPIO_OUTPUT_INIT_HIGH_VAL},  /* 背光控制,当使用PWM时将这句注释掉 */
    {GPIO2_0,  GPIO2_0_LCD_CLK},         /* LCD clk */
    {GPIO2_1,  GPIO2_1_LCD_ENABLE},      /* LCD enable */
    {GPIO2_2,  GPIO2_2_LCD_HSYNC},       /* LCD hsync */
    {GPIO2_3,  GPIO2_3_LCD_VSYNC},       /* LCD vsync */

    {GPIO2_4,  GPIO2_4_LCD_DATA00},      /* LCD data0 */
    {GPIO2_5,  GPIO2_5_LCD_DATA01},      /* LCD data1 */
    {GPIO2_6,  GPIO2_6_LCD_DATA02},      /* LCD data2 */
    {GPIO2_7,  GPIO2_7_LCD_DATA03},      /* LCD data3 */
    {GPIO2_8,  GPIO2_8_LCD_DATA04},      /* LCD data4 */
    {GPIO2_9,  GPIO2_9_LCD_DATA05},      /* LCD data5 */
    {GPIO2_10, GPIO2_10_LCD_DATA06},     /* LCD data6 */
    {GPIO2_11, GPIO2_11_LCD_DATA07},     /* LCD data7 */
    {GPIO2_12, GPIO2_12_LCD_DATA08},     /* LCD data8 */
    {GPIO2_13, GPIO2_13_LCD_DATA09},     /* LCD data9 */
    {GPIO2_14, GPIO2_14_LCD_DATA10},     /* LCD data10 */
    {GPIO2_15, GPIO2_15_LCD_DATA11},     /* LCD data11 */
    {GPIO2_16, GPIO2_16_LCD_DATA12},     /* LCD data12 */
    {GPIO2_17, GPIO2_17_LCD_DATA13},     /* LCD data13 */
    {GPIO2_18, GPIO2_18_LCD_DATA14},     /* LCD data14 */
    {GPIO2_19, GPIO2_19_LCD_DATA15},     /* LCD data15 */

    /* LCD复位引脚 注意:评估板(M105x-EV-Board Rev.C)的LCD复位引脚是硬件复位，未引出至IO，
     * 所以需要自己手动将LCD复位引脚飞线至一个IO口，这里选择GPIO1_8
     */
    {GPIO1_8, (AW_GPIO_PULL_UP | AW_GPIO_OUTPUT_INIT_LOW)},

    /* ssd2828 SPI控制引脚 注意：评估板上需要将R113、R114、R115、R119去掉并用0欧电阻短接
     * R40、R45、R49、R77
     */
    {GPIO1_28, (AW_GPIO_PULL_UP | AW_GPIO_OUTPUT_INIT_LOW)},
    {GPIO1_30, (AW_GPIO_PULL_UP | AW_GPIO_OUTPUT_INIT_LOW)},
    {GPIO1_31, (AW_GPIO_PULL_UP | AW_GPIO_OUTPUT_INIT_LOW)},
};


aw_local void delay_ms(uint32_t ms)
{
    volatile uint32_t i, j;
    for (i = 0; i < ms; ++i) {
        for (j = 0; j < 10000; j++) {
            __asm("NOP");
        }
    }
}

aw_local void ssd2828_write_byte (uint8_t data, ssd2828_send_flg_t data_flg)
{

    volatile int i = 0;
    SSD2828_CS_CLR();

    if (data_flg == SSD2828_SEND_CMD) {
        SSD2828_MOSI_CLR();
    } else {
        SSD2828_MOSI_SET();
    }

    SSD2828_SCK_CLR();
    SSD2828_SCK_SET();

    for (i = 0; i < 8; i++) {
        if (data & 0x80) {
            SSD2828_MOSI_SET();
        } else {
            SSD2828_MOSI_CLR();
        }

        SSD2828_SCK_CLR();
        SSD2828_SCK_SET();

        data <<= 1;
    }

    SSD2828_CS_SET();
}


aw_local void __send_packet(const uint8_t *p_buf)
{
    uint32_t i = 0;

    ssd2828_write_byte(0xB7, SSD2828_SEND_CMD);
    ssd2828_write_byte(0x50, SSD2828_SEND_DATA);
    ssd2828_write_byte(0x02, SSD2828_SEND_DATA);

    ssd2828_write_byte(0xBD, SSD2828_SEND_CMD);
    ssd2828_write_byte(0x00, SSD2828_SEND_DATA);
    ssd2828_write_byte(0x00, SSD2828_SEND_DATA);

    ssd2828_write_byte(0xBC, SSD2828_SEND_CMD);
    ssd2828_write_byte(*p_buf,SSD2828_SEND_DATA);
    ssd2828_write_byte(0x00, SSD2828_SEND_DATA);

    ssd2828_write_byte(0xbf, SSD2828_SEND_CMD);

    for (i = 0;i < (*p_buf); i++) {
        ssd2828_write_byte(*(p_buf + i + 1), SSD2828_SEND_DATA);
    }
}


aw_local void ssd2828_init(void)
{
    /* 复位 */
    SSD2828_RST_SET();
    delay_ms(10);
    SSD2828_RST_CLR();
    delay_ms(100);
    SSD2828_RST_SET();
    delay_ms(100);

    /* SSD2828_Initial */
    ssd2828_write_byte(0xb7, SSD2828_SEND_CMD);

    ssd2828_write_byte(0x50, SSD2828_SEND_DATA);   /* 50=TX_CLK 70=PCLK */

    ssd2828_write_byte(0x00, SSD2828_SEND_DATA);   /* Configuration Register */

    ssd2828_write_byte(0xb8, SSD2828_SEND_CMD);
    ssd2828_write_byte(0x00, SSD2828_SEND_DATA);
    ssd2828_write_byte(0x00, SSD2828_SEND_DATA);   /* VC(Virtual ChannelID) Control Register */

    ssd2828_write_byte(0xb9, SSD2828_SEND_CMD);
    ssd2828_write_byte(0x00, SSD2828_SEND_DATA);   /* 1=PLL disable */
    ssd2828_write_byte(0x00, SSD2828_SEND_DATA);

    /* TX_CLK/MS should be between 5Mhz to100Mhz */
    ssd2828_write_byte(0xBA, SSD2828_SEND_CMD);  /* PLL=(TX_CLK/MS)*NS 8228=480M 4428=240M  061E=120M 4214=240M 821E=360M 8219=300M */
    ssd2828_write_byte(0x1E, SSD2828_SEND_DATA); /* D7-0=NS(0x01 : NS=1) */
    ssd2828_write_byte(0x82, SSD2828_SEND_DATA); /* D15-14=PLL范围 00=62.5-125 01=126-250 10=251-500 11=501-1000  DB12-8=MS(01:MS=1)*/

    ssd2828_write_byte(0xBB, SSD2828_SEND_CMD);  /* LP Clock Divider LP clock = 400MHz / LPD / 8 = 240 / 8 / 4 = 7.5MHz*/
    ssd2828_write_byte(0x06, SSD2828_SEND_DATA); /* D5-0=LPD=0x1 – Divide by 2*/

    ssd2828_write_byte(0x00, SSD2828_SEND_DATA);

    ssd2828_write_byte(0xb9, SSD2828_SEND_CMD);
    ssd2828_write_byte(0x01, SSD2828_SEND_DATA); /* 1=PLL enable */
    ssd2828_write_byte(0x00, SSD2828_SEND_DATA);
    delay_ms(100);

    /* MIPI lane configuration */
    ssd2828_write_byte(0xDE, SSD2828_SEND_CMD);  /* 通道数 */
    ssd2828_write_byte(0x03, SSD2828_SEND_DATA); /* 11=4LANE 10=3LANE 01=2LANE 00=1LANE */
    ssd2828_write_byte(0x00, SSD2828_SEND_DATA);

    const uint8_t tab1[]={4,0xB9,0xFF,0x83,0x94};
    const uint8_t tab2[]={11,0xB1,0x48,0x14,0x74,0x09,0x33,0x54,0x71,0x31,0x57,0x2F};
    const uint8_t tab3[]={7,0xBA,0x63,0x03,0x68,0x6B,0xB2,0xC0};
    const uint8_t tab4[]={7,0xB2,0x00,0x80,0x64,0x06,0x0E,0x2F};
    const uint8_t tab5[]={22,0xB4,0x01,0x70,0x01,0x70,0x01,0x70,0x01,0x05,0x86,0x35,0x00,0x3F,0x1C,0x70,0x01,0x70,0x01,0x70,0x01,0x05,0x86};
    const uint8_t tab6[]={34,0xD3,0x00,0x00,0x00,0x00,0x08,0x08,0x10,0x10,0x32,0x10,0x03,0x00,0x03,0x32,0x15,0x07,0x05,0x07,0x32,0x10,0x08,0x00,0x00,0x17,0x01,0x07,0x07,0x17,0x05,0x05,0x17,0x06,0x40};
    const uint8_t tab7[]={45,0xD5,0x18,0x18,0x18,0x18,0x26,0x27,0x24,0x25,0x06,0x07,0x04,0x05,0x02,0x03,0x00,0x01,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x20,0x21,0x22,0x23,0x18,0x18,0x18,0x18};
    const uint8_t tab8[]={45,0xD6,0x18,0x18,0x18,0x18,0x21,0x20,0x23,0x22,0x01,0x00,0x03,0x02,0x05,0x04,0x07,0x06,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x27,0x26,0x25,0x24,0x18,0x18,0x18,0x18};
    const uint8_t tab9[]={59,0xE0,0x00,0x02,0x06,0x0A,0x0C,0x0E,0x10,0x0D,0x1A,0x28,0x38,0x36,0x3F,0x50,0x59,0x61,0x72,0x7B,0x7D,0x93,0xAC,0x56,0x56,0x5C,0x62,0x67,0x71,0x7A,0x7F,0x00,0x02,0x06,0x0A,0x0B,0x0E,0x10,0x0D,0x1A,0x28,0x38,0x36,0x3F,0x50,0x59,0x61,0x73,0x7C,0x7D,0x94,0xAC,0x57,0x56,0x5C,0x62,0x67,0x71,0x7A,0x7F};
    const uint8_t tab10[]={2,0xCC,0x0b};
    const uint8_t tab11[]={3,0xC0,0x1F,0x73};
    const uint8_t tab12[]={3,0xB6,0x3C,0x3C};
    const uint8_t tab13[]={2,0xD4,0x02};
    const uint8_t tab14[]={2,0xBD,0x01};
    const uint8_t tab15[]={2,0x36,0x00};
    const uint8_t tab16[]={2,0xB1,0x00};
    const uint8_t tab17[]={2,0xBD,0x00};
    const uint8_t tab18[]={2,0xC6,0xEF};
    const uint8_t tab19[]={1,0x11};
    const uint8_t tab20[]={1,0x29};

    __send_packet(tab1);
    __send_packet(tab2);
    __send_packet(tab3);
    __send_packet(tab4);
    __send_packet(tab5);
    __send_packet(tab6);
    __send_packet(tab7);
    __send_packet(tab8);
    __send_packet(tab9);
    __send_packet(tab10);

    __send_packet(tab11);
    __send_packet(tab12);
    __send_packet(tab13);
    __send_packet(tab14);
    __send_packet(tab15);
    __send_packet(tab16);
    __send_packet(tab17);
    __send_packet(tab18);
    __send_packet(tab19);
    delay_ms(20);
    __send_packet(tab20);
    delay_ms(20);

    /* SSD2828_Initial */
    ssd2828_write_byte(0xc9, SSD2828_SEND_CMD);
    ssd2828_write_byte(0x02, SSD2828_SEND_DATA);
    ssd2828_write_byte(0x23, SSD2828_SEND_DATA);   /* p1: HS-Data-zero  p2: HS-Data- prepare  --> 8031 issue */

    ssd2828_write_byte(0xCA, SSD2828_SEND_CMD);
    ssd2828_write_byte(0x02, SSD2828_SEND_DATA);  /* CLK Prepare */
    ssd2828_write_byte(0x23, SSD2828_SEND_DATA);  /* Clk Zero */

    ssd2828_write_byte(0xCB, SSD2828_SEND_CMD);   /* local_write_reg(addr=0xCB,data=0x0510)  */
    ssd2828_write_byte(0x02, SSD2828_SEND_DATA);  /* Clk Post */
    ssd2828_write_byte(0x23, SSD2828_SEND_DATA);  /* Clk Per */

    ssd2828_write_byte(0xCC, SSD2828_SEND_CMD);   /* local_write_reg(addr=0xCC,data=0x100A) */
    ssd2828_write_byte(0x05, SSD2828_SEND_DATA);  /* HS Trail */
    ssd2828_write_byte(0x10, SSD2828_SEND_DATA);  /* Clk Trail */

    ssd2828_write_byte(0xD0, SSD2828_SEND_CMD);
    ssd2828_write_byte(0x00, SSD2828_SEND_DATA);
    ssd2828_write_byte(0x00, SSD2828_SEND_DATA);

    /* RGB interface configuration */
    ssd2828_write_byte(0xB1, SSD2828_SEND_CMD);
    ssd2828_write_byte(HSPW, SSD2828_SEND_DATA);
    ssd2828_write_byte(VSPW, SSD2828_SEND_DATA);

    ssd2828_write_byte(0xB2, SSD2828_SEND_CMD);
    ssd2828_write_byte(HBPD, SSD2828_SEND_DATA);
    ssd2828_write_byte(VBPD, SSD2828_SEND_DATA);

    ssd2828_write_byte(0xB3, SSD2828_SEND_CMD);
    ssd2828_write_byte(HFPD, SSD2828_SEND_DATA);
    ssd2828_write_byte(VFPD, SSD2828_SEND_DATA);

    ssd2828_write_byte(0xB4, SSD2828_SEND_CMD);  /* Horizontal active period 720=02D0 */
    ssd2828_write_byte(0xD0, SSD2828_SEND_DATA); /* 013F=319 02D0=720*/
    ssd2828_write_byte(0x02, SSD2828_SEND_DATA); /* HACT=0x01E0=480,0x021c=540 */

    ssd2828_write_byte(0xB5, SSD2828_SEND_CMD);  /* Vertical active period 1280=0500 */
    ssd2828_write_byte(0x00, SSD2828_SEND_DATA); /* 01DF=479 0500=1280 */
    ssd2828_write_byte(0x05, SSD2828_SEND_DATA); /* VACT=0x0320=800,0x03c0=960,0x0356=854 */

    ssd2828_write_byte(0xB6, SSD2828_SEND_CMD);  /* RGB CLK  16BPP=00 18BPP=01 */
    ssd2828_write_byte(0x24, SSD2828_SEND_DATA); /* D7=0 D6=0 D5=0  D1-0=11 – 24bpp */
    ssd2828_write_byte(0x21, SSD2828_SEND_DATA); /* D15=VS D14=HS D13=CLK D12-9=NC D8=0=Video with blanking packet. 00-F0 */

    /* MIPI lane configuration */
    ssd2828_write_byte(0xDE, SSD2828_SEND_CMD);  /* 通道数 */
    ssd2828_write_byte(0x03, SSD2828_SEND_DATA); /* 11=4LANE 10=3LANE 01=2LANE 00=1LANE */

    ssd2828_write_byte(0x00, SSD2828_SEND_DATA);

    ssd2828_write_byte(0xD6, SSD2828_SEND_CMD);  /* 05=BGR  04=RGB */
    ssd2828_write_byte(0x04, SSD2828_SEND_DATA); /* D0=0=RGB 1:BGR D1=1=Most significant byte sent first */
    ssd2828_write_byte(0x00, SSD2828_SEND_DATA);

    ssd2828_write_byte(0xB7, SSD2828_SEND_CMD);
    ssd2828_write_byte(0x6b, SSD2828_SEND_DATA);
    ssd2828_write_byte(0x03, SSD2828_SEND_DATA);

    ssd2828_write_byte(0x2C, SSD2828_SEND_CMD);
}


aw_local void __hw1280720_plfm_init (void)
{


    int i = 0;
    int lcd_gpios[AW_NELEMENTS(__g_hw1280720f_gpios_list)];

    for (i = 0; i < AW_NELEMENTS(__g_hw1280720f_gpios_list); i++) {
        lcd_gpios[i] = __g_hw1280720f_gpios_list[i].gpio;
    }

    if (aw_gpio_pin_request("lcd_gpios",
                             lcd_gpios,
                             AW_NELEMENTS(lcd_gpios)) == AW_OK) {

        for (i = 0; i < AW_NELEMENTS(__g_hw1280720f_gpios_list); i++) {
            /* 配置功能引脚 */
            aw_gpio_pin_cfg(__g_hw1280720f_gpios_list[i].gpio,
                            __g_hw1280720f_gpios_list[i].func);
        }
    }


    /* 初始化ssd2828 */
    ssd2828_init();
}

/* 设备信息 */
aw_local aw_const awbl_imx1050_tft_panel_devinfo_t  __g_hw1280720f_param = {
    /* panel_info */
    {
        __HW1280720_X_RES,              /* x_res */
        __HW1280720_Y_RES,              /* y_res */
        __HW1280720_BPP,                /* bpp */
        __HW1280720_DCLK_F,             /* dclk_f */
        AWBL_MXS_LCDIF_PANEL_DOTCLK,    /* type */
        99,                             /* default back light intensity */
    },
    /* timing */
    {
        DOTCLK_V_PULSE_WIDTH,           /* v_pulse_width */
        DOTCLK_V_PERIOD,                /* v_period */
        DOTCLK_V_WAIT_CNT,              /* v_wait_cnt */
        DOTCLK_V_ACTIVE,                /* v_active */
        DOTCLK_H_PULSE_WIDTH,           /* h_pulse_width */
        DOTCLK_H_PERIOD,                /* h_period */
        DOTCLK_H_WAIT_CNT,              /* h_wait_cnt */
        DOTCLK_H_ACTIVE,                /* h_active */
        0,                              /* enable_present */
    },
    /* plfm_init */
    __hw1280720_plfm_init
};

/* 设备实例内存静态分配 */
aw_local awbl_imx1050_tft_panel_t __g_hw1280720f;

#define AWBL_HWCONF_HW1280720F       \
    {                                \
        AWBL_IMX1050_TFT_PANEL_NAME, \
        0,                           \
        AWBL_BUSID_PLB,              \
        0,                           \
        &(__g_hw1280720f.dev),       \
        &(__g_hw1280720f_param)      \
    },

#else
#define AWBL_HWCONF_HW1280720F

#endif  /* AW_DEV_HW1280720F */

#endif  /* __AWBL_HWCONF_HW1280720F_H */

/* end of file */
