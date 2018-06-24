//---------------------------------------------------------------------------
// Szerzõ/Author: Csonka Gábor okl. villamosmérnök/M.Sc.EE, 2000-2004.
//---------------------------------------------------------------------------

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

//----------- Line read from a stream with space allocation.
char *freadlinea_(FILE *F)
{
long int i=0,current_pos;
char c=0, *s;
current_pos=ftell(F);
while (((c=fgetc(F))!=0x0d) && (c!=0x0a))
      {
      if (feof(F)) break;
      i++;
      }
s=(char *)calloc(i+1,sizeof (char));    //The last \r or \n char will not be added. Just the termination 0.
//fseek(F,current_pos,SEEK_SET);
fseek(F,-i,SEEK_CUR);
if (!s) return NULL;
c=0;
i=0;
while (((c=fgetc(F))!=0x0d) && (c!=0x0a))
      {
      if (feof(F)) break;
      if ((c!=0x0a) && (c!=0x0d)) s[i++]=c;
      }
return s;
}


//----------- Another (working) line read from a stream with space allocation.
char *freadlinea(FILE **F)
{
long int i=0;
char c=0, *s;
s=malloc(sizeof(char));
s[0]=0;
//while (((c=fgetc(*F))!=0x0d) && (c!=0x0a)) {
do    {
      c=fgetc(*F);
      if (feof(*F)) {
         s=realloc(s,(i+1)*sizeof(char));
         s[i]=0;
         break;
         }
      s=realloc(s,(i+2)*sizeof(char));    //RAM operations are faster than file operations. So *alloc are faster than fseek.
      s[i++]=c;
      s[i]=0;                             //Terminating 0 - doesn't need because the last character will be dropped.
      } while ((c!=0x0d) && (c!=0x0a));
if (!i) {
   free(s);
   s=NULL;
   }
   else if ((s[i-1]==0x0a) || (s[i-1]==0x0d)) s[i-1]=0;
return s;
}


//----------- Line read from a stream.
// If succeed returns number of characters otherwise returns zero. Character
// buffer must have space for the longest line in the stream + 1.
int freadline(FILE *f,char *s)
{
int i=0;
char c=0;
while (((c=fgetc(f))!=0x0d) && (c!=0x0a))
//while (((c=buf[i])!='\r') && (c!='\n'))
      {
      s[i]=0;
      if (feof(f)) break;
      if ((c!=0x0a) && (c!=0x0d)) s[i++]=c;
      }
s[i]=0;
return(i);
}


//----------- Another line read from a stream.
// If succeed returns number of characters otherwise returns zero. Character
// buffer must have space for the longest line in the stream + 1.
int freadline_(FILE *f,char *s)
{
int i=0;
char c=0;
//while (((c=fgetc(f))!=0x0d) && (c!=0x0a))
while (((c=fgetc(f))!='\r') && (c!='\n'))
      {
      s[i]=0;
      if (feof(f)) break;
      if ((c!=0x0a) && (c!=0x0d)) s[i++]=c;
      }
s[i]=0;
return(i);
}


//----------- Line read from a string.
// If succeed returns number of characters otherwise returns zero. Character
// buffer must have space for the longest line in the stream + 1.
int sreadline(char *buf,char *s)
{
int i=0;
char c=0;
//while (((c=buf[i])!=0x0d) && (c!=0x0a))
while (((c=buf[i])!='\r') && (c!='\n'))
      {
      s[i]=0;
      if (!c) break;
      if ((c!='\r') && (c!='\n')) s[i++]=c;
      }
s[i]=0;
return(i);
}


int gfreadline(FILE *f,char *s, char nl)
    {
    int i=0;
    char c=0;
    while ((c=fgetc(f))!=nl)
          {
          if (feof(f)) break;
          if (c!=nl) s[i++]=c;
          }
    s[i]=0;
    return(i);
    }

int gsreadline(char *buf,char *s, char nl)
    {
    int i=0;
    char c=0;
    while ((c=buf[i])!=nl)
          {
          if (!c) break;
          if (c!=nl) s[i++]=c;
          }
    s[i]=0;
    return(i);
    }


int gsreadlinea(char *buf,char *s, char nl)
    {
    int i=0;
    char c=0;
    s=malloc(sizeof(char));
    s[0]=0;
    while ((c=buf[i])!=nl)
          {
          if (!c) break;
          if (c!=nl) {
             s=realloc(s,(i+2)*sizeof(char));
             s[i++]=c;
             }
          }
    s[i]=0;
    return(i);
    }


char *gsreadlineas(char **buf, char nl)
    {
    int i=0;
    char c=0, *s;
    s=malloc(sizeof(char));
    s[0]=0;
    while ((c=*buf[0])!=nl)
          {
          if (!c) break;
          if (c!=nl) {
             s=realloc(s,(i+2)*sizeof(char));
             s[i++]=c;
             *buf=&((*buf)[1]);
             }
          }
    if ((*buf[0])==nl) *buf=&((*buf)[1]);
    s[i]=0;
    return(s);
    }


char *getpassa(const char *disptext, char dispchar)
{
char *password=NULL;
int i=0;
unsigned int c=0;
printf("%s",disptext);
while ((c!='\r') && (c!='\a') && (c!='\n'))
      {
      c=getch();
      password=(char *)realloc(password,++i+1);
      if (password==NULL) {
                          printf("Insufficient memory");
                          return NULL;
                          }
      if ((c!='\r') && (c!='\a') && (c!='\n'))
         {
         password[i-1]=c;
         putc(dispchar,stdout);
         }
         else password[i-1]=0;
      }
printf("\n");
return password;
}

