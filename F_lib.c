//-----------

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//----------- Checked fopen().
// If succeed returns a pointer to the opened file otherwise returns NULL and
// writes the error string to stdio.
FILE *cfopen(char *filename,char *mode,char *errorstring)
{
FILE *f=NULL;
if ((f=fopen(filename,mode))==NULL)
   printf("%s\n",errorstring);
return f;
}


//----------- Extension change
// If succeed returns a pointer to the new filename. If unsuccessful returns
// NULL. newext must be a DOS standard maximum of 3 characters long string.
char *ChangeFileExt(char *fname,char *newext)
{
char *newname;
unsigned int i,len;
for(i=0;fname[i] && (i<65535);i++);     //Goes to end of string.
if (i==65535) return NULL;
for(;fname[i]!='.';i--) if (!i) return NULL;   //Goes back to the last '.' of the filename
if ((newname=(char *)calloc(i+4,sizeof(char)))==NULL) return NULL;
strcpy(newname,fname);
strcpy(newname+i+1,newext);
return newname;
}