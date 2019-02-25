/**
 * \file
 * \brief MMU function for ARMv4 arch.
 *
 * \internal
 * \par History
 * - 1.00 14-09-23  liuweiyun, first implementation.
 * \endinternal
 */

    .syntax unified
    .thumb
    .text

    .set MPU_CTL_ADDR               ,0xe000ed94
    .set __BIT_MPU_CTL_ENABLE       , (1 << 0) /* enable */



/******************************************************************************/
#define __FUNC_DECL(name)           .global name; .type name, %function; .func name
#define __LOCAL_FUNC_DECL(name)     .type name, %function; .func name
#define __FUNC_END                  .endfunc

/*******************************************************************************
   global functions
*******************************************************************************/
    __FUNC_DECL(excute_subto_zero)
excute_subto_zero:
    cmp     r0,#0
    beq     2f
1:
    add     r1,r1,#1
    add     r2,r2,#1
    add     r3,r3,#1
    add     r1,r1,#1
    add     r2,r2,#1
    add     r3,r3,#1
    subs    r0,r0,#1
    bne     1b
2:
    bx      lr
    __FUNC_END


    .end

/* end of file */
