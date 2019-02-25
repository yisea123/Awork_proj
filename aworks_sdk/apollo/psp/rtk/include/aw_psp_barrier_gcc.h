#ifndef         __AW_PSP_BARRIER_GCC_H__
#define         __AW_PSP_BARRIER_GCC_H__

#if defined(AW_ARMV7) || \
    defined (AW_CORTEX_M7)
#include "aw_cpu_barrier_armv7_gcc.h"
#elif defined (AW_CORTEX_M4)
#include "aw_cpu_barrier_armv7_gcc.h"
#else
aw_psp_static_inline void aw_barrier_mb()
{
    asm volatile("" : : : "memory");
}

aw_psp_static_inline void aw_barrier_wmb()
{
    asm volatile("" : : : "memory");
}

aw_psp_static_inline void aw_barrier_rmb()
{
    asm volatile("" : : : "memory");
}

aw_psp_static_inline void aw_barrier_isb()
{
    asm volatile("" : : : "memory");
}
#endif

#endif