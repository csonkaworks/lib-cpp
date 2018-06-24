//---------------------------------------------------------------------------
// Szerzõ: Csonka Gábor okl. villamosmérnök, 1998-2015.
// via http://stackoverflow.com/questions/15114140/writing-binary-number-system-in-c-code
//---------------------------------------------------------------------------

// Just include and use as (int) i=B(11010110); (No quotation marks needed.)


#ifndef _bin_cnv_h
#define _bin_cnv_h

#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define B(x) S_to_binary_(#x)

static inline unsigned long S_to_binary_(const char *s)
{
    unsigned long i = 0;
    while (*s) {
        i <<= 1;
        i += *s++ - '0';
    }
    return i;
}

#endif