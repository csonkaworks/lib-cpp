// Compares for qsort
#include <string.h>

//---------------------------------------------------------------------------

int qsortstrcmp(const void *a, const void *b)
{
return strcmp((char *)a,(char *)b);
}
//---------------------------------------------------------------------------

int qsortstrcmpr(const void *a, const void *b)
{
return -strcmp((char *)a,(char *)b);
}
