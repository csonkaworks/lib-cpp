//---------------------------------------------------------------------------
//
// Author: Csonka Gabor MSc. EE. (Gabor Csonka in English convention name
// order), 1998-2017.
// Comments, suggestions and donations are welcome. My e-mail address is
// gabor.csonka@gmail.com This is my PayPal account as well.
//
//---------------------------------------------------------------------------

// Purpose: Null terminated string utils

#include <stdlib.h>
#include <string.h>
#include "nulltstr.h"


char *allocstr(size_t n)
{
//return (char *)calloc(n+1,sizeof(char));
void *s=malloc((n+1)*sizeof(char));
if (s==NULL) return NULL;
memset(s,0,n+1);
return (char *)s;
}

char *stracpy(char *source)
{
char *dest=stralloc(strlen(source)+1);
if (dest==NULL) return NULL;
memset(dest,0,strlen(source)+1);
return strcpy(dest,source);
}


char *stracpy_(char **dest,char *source)
{
if ((*dest=stralloc(strlen(source)+1))==NULL) return NULL;
memset(dest,0,strlen(source)+1);
return strcpy(*dest,source);
}


char *stracat(char *source, char *s) {
if ((source=realloc(source,sizeof(char)*(strlen(source)+strlen(s)+1)))==NULL)
   return NULL;
return strcat(source,s);
}


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


int strastr(char **array,char *str,int a_length)
    {
    int i;
    for (i=0;i<a_length;i++)
        if (!strcmp(array[i],str)) break;
    return i;
    }


int straistr(char **array,char *str,int a_length)
    {
    int i;
    for (i=0;i<a_length;i++)
        if (!stricmp(array[i],str)) break;
    return i;
//return -1;
    }
    

char **strarray(char **array, char *item) {
unsigned long int i,j;
char *insert=malloc(sizeof (char *) * (strlen(item)+2)), **temp=array;
if (insert==NULL) return NULL;
memset(insert,0x00,strlen(item)+2);
strcpy(insert,item);
if (array==NULL) {
   array=(char **)malloc(sizeof (char *) * 1);
   if (array==NULL) return NULL;
   array[0]=insert;
   }
   else {
   for (i=0;array[i][strlen(array[i])+1];i++);
   array=(char **)realloc(array,sizeof (char *) * (i+2));
   if (array==NULL) {
      for (j=0;j<i;j++) {
          free(temp[j]);
          array[j]=NULL;
          }
      free(temp);
      temp=NULL;
      return NULL;
      }
   array[i+1]=insert;
   array[i][strlen(array[i])+1]=0xFF;
   }
return array;
}


unsigned long int freestrarray(char **array) {
unsigned long int i;
if (array==NULL) return 0;
for (i=0;array[i][strlen(array[i])+1];i++) {
    free(array[i]);
    array[i]=NULL;
    }
free(array);
array=NULL;
return i+1;
}
