//---------------------------------------------------------------------------
// Szerzõ: Csonka Gábor okl. villamosmérnök, 1998-2002.
//---------------------------------------------------------------------------

// Processing utilities

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "proc.h"

char UpCase(char c)
     {
     if ((c>='a') && (c<='z'))
        c=c-'a'+'A';
     return(c);
     }

char LowCase(char c)
     {
     if ((c>='A') && (c<='Z'))
        c=c-'A'+'a';
     return(c);
     }


unsigned __int8 hi(unsigned __int16 w)
{
   return hi8(w);
}

unsigned __int8 lo(unsigned __int16 w)
{
   return lo8(w);
}

unsigned __int8 hi8(unsigned __int16 w)
{
   return(w>>8);
}

unsigned __int8 lo8(unsigned __int16 w)
{
   return((unsigned __int8) w);
}

unsigned __int16 hi16(unsigned __int32 dw)
{
  return (dw>>16);
}

unsigned __int16 lo16(unsigned __int32 dw)
{
  return ((unsigned __int16) dw);
}

unsigned __int32 hi32(unsigned __int64 qw)
{
  return (qw>>32);
}

unsigned __int32 lo32(unsigned __int64 qw)
{
  return ((unsigned __int32) qw);
}

void mirror16(unsigned __int16 *w)
{
   unsigned __int8 tmp = hi8(*w);
   *w = lo8(*w) << 8;
   *w += tmp;
}

void mirror32(unsigned __int32 *dw)
{
   unsigned __int8 tmp, *n = (unsigned __int8 *) dw, i;
   const unsigned __int8 s = sizeof(unsigned __int32);
   for (i = 0; i < s / 2; i++) {
      tmp = n[i];
      n[i] = n[s-1-i];
      n[s-1-i] = tmp;
   }
}

void mirror64(unsigned __int64 *qw)
{
   unsigned __int8 tmp, *n = (unsigned __int8 *) qw, i;
   const unsigned __int8 s = sizeof(unsigned __int64);
   for (i = 0; i < s / 2; i++) {
      tmp = n[i];
      n[i] = n[s-1-i];
      n[s-1-i] = tmp;
   }
}

char *s_int(long int n, const char *s)
{
   return (n - 1) ? s : "";
}

char *s_dbl(long double n, const char *s)
{
   return ((n - 1.0) == 0.0) ? s : "";
}

int strastr(char **array,char *str,int a_length)
    {
    int i;
    for (i=0;i<a_length;i++)
        if (!strcmp(array[i],str)) break;
    return i;
}


char *allocstr(size_t n)
{
return (char *)calloc(n+1,sizeof(char));
}


char *GetPass(const char *message)
{
char *pass,*tmp,c;
int i=0;
printf("%s",message);
pass=(char *)calloc(1,sizeof (char));
c=getch();
while (c!='\n' && c!='\r')
      {
      pass[i++]=c;
      tmp=(char *)realloc(pass,(i+2)*sizeof (char));
      tmp[i]=0;
      pass=tmp;
      c=getch();
      }
printf("\n");
return pass;
}