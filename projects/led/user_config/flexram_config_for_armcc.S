                PRESERVE8
                THUMB

REG_IOMUXC_GPR14                    EQU     0x400AC038
REG_IOMUXC_GPR16                    EQU     0x400AC040
REG_IOMUXC_GPR17                    EQU     0x400AC044
BIT_GPR16_ITCM_EN                   EQU     (1<<0)
BIT_GPR16_DTCM_EN                   EQU     (1<<1)
BIT_GPR16_FLEX_RAM_BANK_CFG_SEL     EQU     (1<<2)
MASK_GPR14_DTCM_SZ                  EQU     (0xF << 20)
MASK_GPR14_ITCM_SZ                  EQU     (0xF << 16)


                AREA  |.text.flex_ram_config|, CODE, READONLY
                EXPORT  flex_ram_config

;此函数用于提供了一个可以将FlexRAM全部配置为DTCM，ITCM，或OCRAM的机会,
;它只会在代码运行在SDRAM或者Flexspi Flash上时才会被调用。

flex_ram_config     PROC
; 首先将DTCM和ITCM都停用
                ldr     r0, = REG_IOMUXC_GPR16;
                ldr     r1,[r0];
                bic     r1,#BIT_GPR16_ITCM_EN
                bic     r1,#BIT_GPR16_DTCM_EN;
                str     r1,[r0];
                dsb

; 选择fuse来配置FlexRam
                ldr     r0, = REG_IOMUXC_GPR16;
                ldr     r1,[r0];
                bic     r1,#BIT_GPR16_FLEX_RAM_BANK_CFG_SEL
                str     r1,[r0];
                dsb


; 配置GPR17中的FLEX RAM,全部为DTCM
                ldr     r1, = 0xAAAAAAAA;
                ldr     r0, = REG_IOMUXC_GPR17;
                str     r1,[r0];
                dsb
                isb

; 使用配置寄存器来配置FLEXRAM
                ldr     r0, = REG_IOMUXC_GPR16;
                ldr     r1,[r0];
                orr     r1,#BIT_GPR16_FLEX_RAM_BANK_CFG_SEL
                str     r1,[r0];
                dsb
                isb

; 配置IOMUXC_GPR_GPR14寄存器，ITCM大小为0, DTCM大小为512KB
                ldr     r0, = REG_IOMUXC_GPR14;
                ldr     r1, [r0]
                bic     r1,#MASK_GPR14_ITCM_SZ

                bic     r1,#MASK_GPR14_DTCM_SZ
                orr     r1,#(0xA << 20);
                str     r1,[r0];
                dsb

; GPR16 中使能DTCM
                ldr     r0, = REG_IOMUXC_GPR16;
                ldr     r1,[r0];
                orr     r1,#BIT_GPR16_DTCM_EN;
                str     r1,[r0];
                dsb
                isb
                bx  lr
                ENDP

                END