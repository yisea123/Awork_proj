/**
 * \file
 * \brief systick function for armv7m arch.
 *
 * \internal
 * \par History
 * - 1.00 17-07-11  sni, first implementation.
 * \endinternal
 */

#ifndef __ARMV7M_SYSTICK_H /* { */
#define __ARMV7M_SYSTICK_H

#include <aw_types.h>

/** \brief  Structure type to access the System Timer (SysTick).
 */
typedef struct
{
    volatile uint32_t CTRL;                     /*!< Offset: 0x000 (R/W)  SysTick Control and Status Register */
    volatile uint32_t LOAD;                     /*!< Offset: 0x004 (R/W)  SysTick Reload Value Register       */
    volatile uint32_t VAL;                      /*!< Offset: 0x008 (R/W)  SysTick Current Value Register      */
    volatile uint32_t CALIB;                    /*!< Offset: 0x00C (R/ )  SysTick Calibration Register        */
} SysTick_Type;

#define SYS_TICK        ((SysTick_Type *)0xE000E010UL)

void armv7m_systick_init(
            unsigned int systick_freq,
            unsigned int cpu_freq,
            int tick_per_second,
            int use_cpu_core_clk);

#endif /* } __ARMV7M_SYSTICK_H */

/* end of file */
