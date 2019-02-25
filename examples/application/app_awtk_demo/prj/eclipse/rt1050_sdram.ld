MEMORY
{
    data (xrw)             : ORIGIN = 0x20000000, LENGTH = 512K
    flexspi_drv(rx)        : ORIGIN = 0x80000000, LENGTH = 4K
    code (rx)              : ORIGIN = 0x80002000, LENGTH = 6M
    dma_heap (rw)          : ORIGIN = 0x80602000, LENGTH = 1M
    heap (rw)              : ORIGIN = 0x80702000, LENGTH = 8M
}

PROTECT_SIZE = 0x2000;
RAMFUNC_SIZE = 0x2000;
STACK_SIZE = DEFINED(STACK_SIZE) ? STACK_SIZE : 0x2000;
ENTRY(Reset_Handler)

SECTIONS
{
    /* 代码段  LMA == VMA == 0x30000000 */
    /* 具有常量属性段 */
    . = ORIGIN(code);
    . = ALIGN(0x100000);
    __code_start = .;
    .text :
    {
        KEEP(*(.isr_vector))       /* 使用KEEP使.vector段不被移除 */
        aw_backtrace_text_start = .;
        *(.text)
        *(.text.*)              /*  cpp namespace function      */
        *(.romrun)              /*  rom中必须的函数             */
        aw_backtrace_text_end = .;
        *(.rodata)              /*  read-only data (constants)  */
        *(.rodata*)
        *(.glue_7)
        *(.glue_7t)
    }>code

    /* section information for simple shell symbols */
    .text :
    {
        . = ALIGN(4);
        __shellsym_tab_start = .;
        KEEP(*(.shellsymbol))
        __shellsym_tab_end = .;
    }>code

    /* .ARM.exidx is sorted, so has to go in its own output section */
    . = ALIGN(4);
     __exidx_start = .;
     PROVIDE(__exidx_start = __exidx_start);
    .ARM.exidx :
    {
        /* __exidx_start = .; */
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
        /* __exidx_end = .;   */
    }>code
    . = ALIGN(4);
     __exidx_end = .;
     PROVIDE(__exidx_end = __exidx_end);

    /*
     * C++ 全局对象构造与析构函数表
     * 这里放在 .text 和 .ARM.exidx 之后, .data 之前,
     * 这里的  LMA 和 VMA 相同, 如果放在 .data 之后, LMA 与 VMA 不同,
     * 则需要启动程序从装载区搬运到运行区
     */

    . = ALIGN(4);
    .ctors :
    {
        PROVIDE (__AW_CTOR_LIST__ = . );
        KEEP (*(.preinit_array))
        KEEP (*(.init_array))
        KEEP (*(SORT(.ctors.*)))
        KEEP (*(.ctors))
        PROVIDE (__AW_CTOR_END__ = . );
    }>code

    .dtors :
    {
        PROVIDE (__AW_DTOR_LIST__ = . );
        KEEP (*(.fini_array))
        KEEP (*(SORT(.dtors.*)))        
        KEEP (*(.dtors))
        PROVIDE (__AW_DTOR_END__ = . );
    }>code

    . = ORIGIN(code) + LENGTH(code);
    PROVIDE (__code_end = .);

    .stack (NOLOAD) :
    {
        _sstack = . ;
        . = ALIGN(8);
        . = . + STACK_SIZE;
        . = ALIGN(8);
        _estack = . ;
    } > data
    
    _sidata = LOADADDR(.data);

    .data :
    {
        _sdata = . ;
        *(.data .data.*)
        . = ALIGN(8);
        _edata = . ;
    } > data AT > code

    .bss (NOLOAD) :
    {
        . = ALIGN(8);
        _sbss = . ;
        *(.bss .bss.*)
        *(COMMON)
        . = ALIGN(8);
        _ebss = . ;
    } > data
    
    . = ALIGN(8);
    /* 系统堆 */
    PROVIDE (__heap_start__ = ORIGIN(heap) );
    PROVIDE (__heap_end__ = ORIGIN(heap) + LENGTH(heap) );
    
    /* dma 堆 */
    PROVIDE (__heap_dma_start__ = ORIGIN(dma_heap) );
    PROVIDE (__heap_dma_end__ = ORIGIN(dma_heap) + LENGTH(dma_heap) );
    
    /*MPU依赖的关键信息*/
    PROVIDE (__rom_start__ = ORIGIN(code));
    PROVIDE (__rom_end__ = ORIGIN(code) + LENGTH(code) );
    
    PROVIDE (__ram_start__ = ORIGIN(data));
    PROVIDE (__ram_end__ = ORIGIN(data) + LENGTH(data) );

    /* Flexspi驱动(Flexspi Flash XIP执行时保存Flash的读写驱动到该内存) */    
    PROVIDE (__flexspi_drv_start__ = ORIGIN(flexspi_drv));
    PROVIDE (__flexspi_drv_end__ = ORIGIN(flexspi_drv) + LENGTH(flexspi_drv) );
}
