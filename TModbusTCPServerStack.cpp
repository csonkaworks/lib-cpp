//---------------------------------------------------------------------------
//                  ModBUS communication routines
//
// Szerzõ: Csonka Gábor okl. villamosmérnök, 2005-2008.
//
// Author: Gábor Csonka M.Sc., 2005-2008.
//
// Hierarchia: TObject -- TModbusTCPServerStack
// Hierarchy: TObject -- TModbusTCPServerStack
//---------------------------------------------------------------------------

//#include <Forms.hpp>
#include <stdio.h>
#include <stdlib.h>
#include "TModbusTCPServerStack.h"
#include "crc16.h"
#include "csgproc.h"
#include "ModbusSrvUnit1.h"

#pragma link "csgproc"
#pragma link "crc16"

__fastcall TModbusTCPServerStack::TModbusTCPServerStack(void)
{
long unsigned int i;
//char s[34];
for (i=0;i<65536;i++) {
//                      itoa(i,s,10);
//                      Application->MessageBox(s,"item",MB_OK);
                      RegLength[i]=0;
                      }
RegMap=NULL;
memset(&Coils,0,256*sizeof (__int8));   //Setting all coils to OFF state.
CurrentHeader.as_Header.ConnectionID=0;
Tmr=new TTimer(NULL);
Tmr->Interval=5000;
Tmr->Enabled=true;
Tmr->OnTimer=OnTmrExpires;
}
//---------------------------------------------------------------------------

__fastcall TModbusTCPServerStack::~TModbusTCPServerStack(void)
{
if (RegMap!=NULL) free(RegMap);
delete Tmr;
Tmr=NULL;
Application->MessageBox("Jól kitöröltem egy ModbusServerStack object példányt :)","Inf to lammer users",MB_OK);
}
//---------------------------------------------------------------------------

// This uses the variable Socket to read the buffer from the TCP/IP
// connection. That's why it does not need any parameters.
int __fastcall TModbusTCPServerStack::OnMBDataArrived(void)
{
unsigned __int8 *rcvbuf;
long unsigned int n=Socket->ReceiveLength(),i;
AnsiString a;
char *hex;
if ((rcvbuf=(__int8 *)calloc(n+1,sizeof (__int8)))==NULL) return 0;
Socket->ReceiveBuf(rcvbuf,n);
if (n<8) {
         hex=Bin2HexA(rcvbuf,n);
//         a.printf("(Non-modbus frame) ID: %d Hex: %s Char: %s",((TMbSrv::TSocketMetaData *)Socket->Data)->ID,hex,rcvbuf);
         a.printf("(Non-modbus frame) FCID: %d Hex: %s Char: %s",FCID,hex,rcvbuf);
         free(rcvbuf);
         MbSrv->ReadLog->Lines->Add(a);
         return 0; //Header: 7bytes, function code:1 byte. So minimum of 8 bytes.
         }
for (i=0;i<8;i+=2)
    {
    CurrentHeader.as_byte[i]=rcvbuf[i+1];
    CurrentHeader.as_byte[i+1]=rcvbuf[i];
    }
//memcpy(CurrentHeader.as_byte,rcvbuf,sizeof (__int8)*8);
free(rcvbuf);
//a.printf("ID: %d, Len: %d, CID: 0x%.4X, DLen: %d, AD: 0x%.2X, FC: 0x%.2X",
//              ((TMbSrv::TSocketMetaData *)Socket->Data)->ID,n,CurrentHeader.as_Header.ConnectionID,
//              CurrentHeader.as_Header.DatagramLength,CurrentHeader.as_Header.DevAddress,
//              CurrentHeader.as_Header.FunctionCode);
a.printf("FCID: %d, Len: %d, CID: 0x%.4X, DLen: %d, AD: 0x%.2X, FC: 0x%.2X",
              FCID,n,CurrentHeader.as_Header.ConnectionID,
              CurrentHeader.as_Header.DatagramLength,CurrentHeader.as_Header.DevAddress,
              CurrentHeader.as_Header.FunctionCode);
MbSrv->ReadLog->Lines->Add(a);
Tmr->Enabled=false;
Tmr->Enabled=true;
return n;
}
//---------------------------------------------------------------------------

void __fastcall TModbusTCPServerStack::OnTmrExpires(TObject *Sender)
{
if (Tmr!=NULL) Tmr->Enabled=false;
Application->MessageBox("A fasznak indítottad el, ha nem használod...","!Lammer felhasználó!",MB_OK);
if (Tmr!=NULL) Tmr->Enabled=true;
   else        Application->MessageBox("Balfasz, lebontott a TCP kapcsolat, és bedöglött a ModbusTCPServerStack object.","!Lammer felhasználó!",MB_OK);
}
//---------------------------------------------------------------------------

