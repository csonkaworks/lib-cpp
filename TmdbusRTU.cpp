//---------------------------------------------------------------------------
//                  ModBUS RTU Master communication routines
//
// Szerzõ: Csonka Gábor okl. villamosmérnök, 2005-2012. Általános cucc,
// származtass belõle objectet, ezt ne írd át!!!
// A származtatott objectben kell megírni az adatforrás szerinti
// void MBWriteChar(unsigned __int8) 1 karaktert a buszra küldõ, és a
// int OnMBDataArrived (unsigned __int8 *) adat jött eseményt kezelõ
// függvényeket. (Ez utóbbi visszatérési értéke a vett byte-ok száma.)
//
// Author: Gábor Csonka M.Sc., 2005-2012. General object class, please derive
// your own class from it. Please don't modify this class.
// You must overload the following two empty functions:
// void MBWriteChar(unsigned __int8) sends a character to the physical bus.
// int OnMBDataArrived (unsigned __int8 *) is an event handler: this fills up
// the input buffer and returns the size of it.
//
// Hierarchia: TObject -- TCustomModbusRTU
// Hierarchy: TObject -- TCustomModbusRTU
//---------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "crc16.h"
#include "proc.h"
#include "procw32.h"
#include "TmdbusRTU.h"

#pragma link "proc"
#pragma link "procw32"
#pragma link "crc16"

//---------------------------------------------------------------------------

__fastcall TCustomModbusRTU::TCustomModbusRTU(void)
:TObject()
{
}
//---------------------------------------------------------------------------

void __fastcall TCustomModbusRTU::SendGen(unsigned __int16 length,unsigned __int8 *buf)
{
unsigned __int16 i,crc=0xffff;
for (i=0;i<length;i++) {
                       crc16(&crc,buf[i]);
                       MBWriteChar(buf[i]);
                       }
MBWriteChar(lo(crc));
MBWriteChar(hi(crc));
}
//---------------------------------------------------------------------------

void __fastcall TCustomModbusRTU::SendRead(unsigned __int16 RemoteAddress,unsigned __int16 startreg,unsigned __int16 regs)
{
unsigned __int16 crc=0xffff;
unsigned __int8 b;
MBWriteChar(RemoteAddress);
crc16(&crc,RemoteAddress);
MBWriteChar(0x03);
crc16(&crc,0x03);
b=hi(startreg);
MBWriteChar(b);
crc16(&crc,b);
b=lo(startreg);
MBWriteChar(b);
crc16(&crc,b);
b=hi(regs);
MBWriteChar(b);
crc16(&crc,b);
b=lo(regs);
MBWriteChar(b);
crc16(&crc,b);
MBWriteChar(lo(crc));
MBWriteChar(hi(crc));
return;
}
//---------------------------------------------------------------------------

void __fastcall TCustomModbusRTU::SendCustomRead(struct mbrec frame)
{
unsigned __int16 crc=0xffff;
int i;
unsigned __int8 b;
MBWriteChar(frame.address);
crc16(&crc,frame.address);
MBWriteChar(frame.command);
crc16(&crc,frame.command);
b=hi(frame.startreg);
MBWriteChar(b);
crc16(&crc,b);
b=lo(frame.startreg);
MBWriteChar(b);
crc16(&crc,b);
b=hi(frame.regs);
MBWriteChar(b);
crc16(&crc,b);
b=lo(frame.regs);
MBWriteChar(b);
crc16(&crc,b);
MBWriteChar(lo(crc));
MBWriteChar(hi(crc));
return;
}
//---------------------------------------------------------------------------

void __fastcall TCustomModbusRTU::SendWrite(unsigned __int16 RemoteAddress,unsigned __int16 startreg,unsigned __int16 regs,unsigned __int8 count,unsigned __int8 *buf)
{
unsigned __int16 crc=0xffff;
int i;
unsigned __int8 b;
MBWriteChar(RemoteAddress);
crc16(&crc,RemoteAddress);
MBWriteChar(0x10);
crc16(&crc,0x10);
b=hi(startreg);
MBWriteChar(b);
crc16(&crc,b);
b=lo(startreg);
MBWriteChar(b);
crc16(&crc,b);
b=hi(regs);
MBWriteChar(b);
crc16(&crc,b);
b=lo(regs);
MBWriteChar(b);
crc16(&crc,b);
MBWriteChar(count);
crc16(&crc,count);
for (i=0;i<count;i++) {
                      MBWriteChar(buf[i]);
                      crc16(&crc,buf[i]);
                      }
MBWriteChar(lo(crc));
MBWriteChar(hi(crc));
return;
}
//---------------------------------------------------------------------------

void __fastcall TCustomModbusRTU::SendCustomWrite(struct mbrec frame)
{
unsigned __int16 crc=0xffff;
int i;
unsigned __int8 b;
MBWriteChar(frame.address);
crc16(&crc,frame.address);
MBWriteChar(frame.command);
crc16(&crc,frame.command);
b=hi(frame.startreg);
MBWriteChar(b);
crc16(&crc,b);
b=lo(frame.startreg);
MBWriteChar(b);
crc16(&crc,b);
b=hi(frame.regs);
MBWriteChar(b);
crc16(&crc,b);
b=lo(frame.regs);
MBWriteChar(b);
crc16(&crc,b);
MBWriteChar(frame.count);
crc16(&crc,frame.count);
for (i=0;i<frame.count;i++)
    {
    MBWriteChar(frame.buffer[i]);
    crc16(&crc,frame.buffer[i]);
    }
MBWriteChar(lo(crc));
MBWriteChar(hi(crc));
return;
}
//---------------------------------------------------------------------------

void __fastcall TCustomModbusRTU::AnswerCustomRead(struct mbrec frame)
{
unsigned __int16 crc=0xffff;
int i;
MBWriteChar(frame.address);
crc16(&crc,frame.address);
MBWriteChar(frame.command);
crc16(&crc,frame.command);
MBWriteChar(frame.count);
crc16(&crc,frame.count);
for (i=0;i<frame.count;i++) {
    MBWriteChar(frame.buffer[i]);
    crc16(&crc,frame.buffer[i]);
    }
MBWriteChar(lo(crc));
MBWriteChar(hi(crc));
return;
}
//---------------------------------------------------------------------------

void __fastcall TCustomModbusRTU::AnswerCustomWrite(struct mbrec frame)
{
unsigned __int16 crc=0xffff;
int i;
unsigned __int8 b;
MBWriteChar(frame.address);
crc16(&crc,frame.address);
MBWriteChar(frame.command);
crc16(&crc,frame.command);
b=hi(frame.startreg);
MBWriteChar(b);
crc16(&crc,b);
b=lo(frame.startreg);
MBWriteChar(b);
crc16(&crc,b);
b=hi(frame.regs);
MBWriteChar(b);
crc16(&crc,b);
b=lo(frame.regs);
MBWriteChar(b);
crc16(&crc,b);
MBWriteChar(lo(crc));
MBWriteChar(hi(crc));
return;
}
//---------------------------------------------------------------------------

void __fastcall TCustomModbusRTU::ProcessM(unsigned __int8 *inbuffer,int length,struct mbrec *frame)
{
unsigned __int16 crc=0xffff,i,n=0;
memset(frame,0,sizeof(struct mbrec));
if (length<6) return;        //The shortest frame is 6 bytes long with the 2 bytes of CRC.
for (i=0;i<length;i++)
    crc16(&crc,inbuffer[i]);
if (crc) {
         frame->command=0xFF; //If CRC isn't 0 there is a CRC error.
         return;
         }
frame->address=inbuffer[n++]; //Address field is the first ([0])
frame->command=inbuffer[n++]; //Command field is the second ([1])
switch (frame->command)
       {
       case 0x03: // Read
                  frame->count=inbuffer[n++];
                  if (n+frame->count>length) {
                     frame->command=0xF3;        //There are smaller amount of data than needed.
                     return;
                     }
                  frame->buffer=(__int8 *)malloc(frame->count);
                  if (frame->buffer==NULL) {
                     frame->command=0xFA;  //Can not allocate space for data
                     return;
                     }
                  memcpy(frame->buffer,&(inbuffer[n]),frame->count);
                  return;
       case 0x10: // Write
                  frame->startreg=inbuffer[n++]; //StartAddrHi [2]
                  frame->startreg<<=8;
                  frame->startreg|=inbuffer[n++]; //StartAddrLo [3]
                  frame->regs=inbuffer[n++];    //RegsNumHi [4]
                  frame->regs<<=8;
                  frame->regs|=inbuffer[n];     //RegsNumLo [5]
                  frame->count=0;
                  frame->buffer=NULL;
                  return;
       default: frame->command=0xF0;           //Not even write or read so can not process.
       }
return;
}
//---------------------------------------------------------------------------

void __fastcall TCustomModbusRTU::ProcessS(unsigned __int8 *inbuffer,int length,struct mbrec *frame)
{
unsigned __int16 crc=0xffff,i,n=0;
memset(frame,0,sizeof(struct mbrec));
if (length<6) return;        //The shortest frame is 6 bytes long with the 2 bytes of CRC.
for (i=0;i<length;i++)
    crc16(&crc,inbuffer[i]);
if (crc) {
         frame->command=0xFF; //If CRC isn't 0 there is a CRC error.
         return;
         }
frame->address=inbuffer[n++]; //Address field is the first ([0])
frame->command=inbuffer[n++]; //Command field is the second ([1])
switch (frame->command)
       {
       case 0x03: // Read query
                  frame->startreg=inbuffer[n++]; //StartAddrHi [2]
                  frame->startreg<<=8;
                  frame->startreg|=inbuffer[n++]; //StartAddrLo [3]
                  frame->regs=inbuffer[n++];    //RegsNumHi [4]
                  frame->regs<<=8;
                  frame->regs|=inbuffer[n];     //RegsNumLo [5]
                  frame->count=0;
                  frame->buffer=NULL;
                  return;
       case 0x10: // Write query
                  frame->startreg=inbuffer[n++]; //StartAddrHi [2]
                  frame->startreg<<=8;
                  frame->startreg|=inbuffer[n++]; //StartAddrLo [3]
                  frame->regs=inbuffer[n++];    //RegsNumHi [4]
                  frame->regs<<=8;
                  frame->regs|=inbuffer[n++];   //RegsNumLo [5]
                  frame->count=inbuffer[n++];   //Count [6]
                  frame->buffer=(__int8 *)malloc(frame->count);
                  if (frame->buffer==NULL) {
                     frame->command=0xFA;  //Can not allocate space for data
                     return;
                     }
                  memcpy(frame->buffer,&(inbuffer[n]),frame->count);
                  return;
       default: frame->command=0xF0;           //Not even write or read so can not process.
       }
return;
}
//---------------------------------------------------------------------------

void __fastcall TCustomModbusRTU::MBWriteChar(unsigned __int8 c)
{
// Actually, this is an empty function. It must be overloaded with a
// function what sends a character to the physical bus or initiates a
// function what does it.
// (It must be declared virtual because there are TCustomModbusRTU
// member functions call it.)
}
//---------------------------------------------------------------------------

int __fastcall TCustomModbusRTU::OnMBDataArrived (unsigned __int8 *inbuffer)
{
// Actually, this is an empty function. It must be overloaded with a
// function what reads the received bytes from the physical bus or
// initiates a function to do it. It can return the length of buf and
// returns 0 actually.
// (Not need to declare it virtual because no TCustomModbusRTU member
// function calls it.)
return 0;
}
//---------------------------------------------------------------------------

