// Standard Windows INI file reader (c) Sziklay Peter & Csonka Gabor, 2000-
// 2002.
//
// See RDCONFIG.H for details.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *RdConfig(char *configfile,char *group,char *descriptor)
     {
     FILE *f=NULL;
     char *value,temp[64],rd[255];
     if ((f=fopen(configfile,"r"))==NULL) return(NULL);
     rewind(f);
     rd[0]=0;
     while (!feof(f) && (strcmp(rd,group)))
           fscanf(f,"%64s",rd);
     strcpy(temp,descriptor);
     strcat(temp,"=%s\n");
     rd[0]=0;
     value=(char *)calloc(256,sizeof (char));
     while (!feof(f) && (rd[0]!='['))
           {
           fscanf(f,"%255s",rd);
           sscanf(rd,temp,value);
           if (value[0]) break;
           }
     fclose(f);
     return(value);
     }


int Convert(char *s)
     {
     int i;
     for (i=0;s[i];i++) if ((unsigned char)s[i]==255) s[i]=' ';
     return(i);
     }