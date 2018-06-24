//---------------------------------------------------------------------------
// Szerzõ: Csonka Gábor okl. villamosmérnök, 1998-2009.
//---------------------------------------------------------------------------

// Command line parameter utilities

// These utils are applicable to process a parameter list like
// program.exe -f c:\homedir\filename.ext +q /insert "Hello World!"


#include <string.h>
#include "nulltstr.h"

// This line contains the typical parameter separators
const char *param_separators="/-+";

// This line contains the typical parameter concatenator
const char param_concatenator='"';


int PrmIsDef(int argscount,char **args,char *arg)
{
if (strastr(args,arg,argscount)==argscount) return 0;
   else                                     return 1;
}


char **PrmPrms(int argsc,char **args,char *arg,int *count)
{
int index=strastr(args,arg,argsc),i,n=0;
char **prms=NULL;
if (index<argsc-1)
   {
   printf("%d %s %s\n",index+1,args[index+1],(&(args[index+1]))[0]);
   prms=(&(args[index+1]));
   for (i=index+1;(i<argsc) && (!strspn(args[i],param_separators));i++)
       n++;
   }
*count=n;
return prms;
}


int FreeArray(void **array,int count)
{
int i;
for (i=0;i<count;i++) free(array[i]);
return i;
}