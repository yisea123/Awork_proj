#include <stdio.h>
#include "aw_mem.h"


void *malloc (int size)
{
    return aw_mem_alloc(size);
}



void *calloc (size_t nelem, size_t size)
{
    return aw_mem_calloc(nelem, size);
}    


void free(void *ptr)
{
    aw_mem_free(ptr);
}









