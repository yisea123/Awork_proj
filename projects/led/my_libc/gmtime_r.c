/**
 * \file
 * \brief implementation of asctime_r().
 *
 * \internal
 * \par modification history:
 * - 180511 hsg, first implementation.
 * \endinternal
 */

#include <time.h>
#include <stdio.h>

struct tm *gmtime_r(const time_t *t, struct tm *__tm)
{
    return _localtime_r(t, __tm);
}




