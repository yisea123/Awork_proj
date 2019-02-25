/******************************************************************************
 * @file     flexram_config.S
 * @brief    配置i.MX RT105x的FlexRAM
 * @version  V0.0.1
 * @date     2018-3-8
 ******************************************************************************/


    .syntax  unified
    .thumb

    .global flex_ram_config;

    .set    REG_IOMUXC_GPR14,0x400AC038
    .set    REG_IOMUXC_GPR16,0x400AC040
    .set    REG_IOMUXC_GPR17,0x400AC044

    .set    BIT_GPR16_ITCM_EN, (1<<0)
    .set    BIT_GPR16_DTCM_EN, (1<<1)
    .set    BIT_GPR16_FLEX_RAM_BANK_CFG_SEL, (1<<2)

    .set    MASK_GPR14_DTCM_SZ, (0xF << 20)
    .set    MASK_GPR14_ITCM_SZ, (0xF << 16)
    /**
     * void flex_ram_config(void)
     *
     * @param  None
     * @return None
     *
     * @brief  此函数用于提供了一个可以将FlexRAM全部配置为DTCM，ITCM，或OCRAM的机会，
     *         它只会在代码运行在SDRAM或者Flexspi Flash上时才会被调用。
     *         注意:此函数的实现要求不能使用堆栈，只能使用寄存器和常量。
     */
    .section  .text.flex_ram_config
    .type  flex_ram_config, %function
flex_ram_config:

    // 首先将DTCM和ITCM都停用
    ldr     r0, = REG_IOMUXC_GPR16;
    ldr     r1,[r0];
    bic     r1,BIT_GPR16_ITCM_EN
    bic     r1,BIT_GPR16_DTCM_EN;
    str     r1,[r0];
    dsb

    // 选择fuse来配置FlexRam
    ldr     r0, = REG_IOMUXC_GPR16;
    ldr     r1,[r0];
    bic     r1,BIT_GPR16_FLEX_RAM_BANK_CFG_SEL
    str     r1,[r0];
    dsb

    //配置GPR17中的FLEX RAM,全部为DTCM
    ldr     r1, = 0xAAAAAAAA;
    ldr     r0, = REG_IOMUXC_GPR17;
    str     r1,[r0];
    dsb
    isb

    // 使用配置寄存器来配置FLEXRAM
    ldr     r0, = REG_IOMUXC_GPR16;
    ldr     r1,[r0];
    orr     r1,BIT_GPR16_FLEX_RAM_BANK_CFG_SEL
    str     r1,[r0];
    dsb
    isb

    //配置IOMUXC_GPR_GPR14寄存器，ITCM大小为0, DTCM大小为512KB
    ldr     r0, = REG_IOMUXC_GPR14;
    ldr     r1, [r0]
    bic     r1,MASK_GPR14_ITCM_SZ

    bic     r1,MASK_GPR14_DTCM_SZ
    orr     r1,(0xA << 20);
    str     r1,[r0];
    dsb

    // GPR16 中使能DTCM
    ldr     r0, = REG_IOMUXC_GPR16;
    ldr     r1,[r0];
    orr     r1,BIT_GPR16_DTCM_EN;
    str     r1,[r0];
    dsb
    isb
    bx  lr
    .size  flex_ram_config, . - flex_ram_config

