//---------------------------------------------------------------------------
// Szerzõ: Csonka Gábor okl. villamosmérnök, 1998-2002.
//---------------------------------------------------------------------------

// Processing utilities for win32

#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <system.hpp>  //Because the AnsiString
#include <sysutils.hpp>  //Because the Now()
//Not needed. #include <systdate.h>  //Because the TDateTime


char *Bin2HexA(void *buf,int length)
{
int i;
AnsiString temp;
unsigned char *result=(unsigned char *)malloc(sizeof(unsigned char)*3*length+sizeof(unsigned char));
memset(result,0,3*length+1);
for (i=0;i<length;i++)
    {
    temp=temp.sprintf("%.2X ",((unsigned char *)buf)[i]);
    strcat(result,temp.c_str());
    }
return result;
}


char *StrNow()
{
char *datetime;
TDateTime DT=Now();
int dtlen=DT.DateString().Length()+DT.TimeString().Length()+2; //The space between date and time and the terminating \0.
datetime=(char *)malloc(sizeof(char)*dtlen);
memset(datetime,0,dtlen);
strcpy(datetime,DT.DateString().c_str());
strcat(datetime," ");
strcat(datetime,DT.TimeString().c_str());
return datetime;
}


