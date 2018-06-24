//---------------------------------------------------------------------------
//            ModBUS communication routines -- header
//
// Szerzõ: Csonka Gábor okl. villamosmérnök, 2005-2008.
//
// Author: Gábor Csonka M.Sc., 2005-2008.
//
// Hierarchia: TObject -- TModbusTCPServerStack
// Hierarchy: TObject -- TModbusTCPServerStack
//---------------------------------------------------------------------------

#include <Classes.hpp>
#include <scktcomp.hpp>
#include <ExtCtrls.hpp>

//---------------------------------------------------------------------------
#ifndef Tmdbus_H
#define Tmdbus_H

//---------------------------------------------------------------------------

class TModbusTCPServerStack : public TObject
{
private:
        TTimer *Tmr;
public:		// User declarations
        __fastcall TModbusTCPServerStack(void);
        __fastcall ~TModbusTCPServerStack(void);
        // This points to the socket used by the actual instance of TModbusTCPServerStack class.
        TCustomWinSocket *Socket;
        // Foreign Connection ID - it can use by the application to assign an ID
        // to each instance of TModbusTCPServerStack object.
        unsigned int FCID;
        // This contains coil array (65535 bits)
        unsigned __int8 Coils[256];
        // This contains pointers to registers 0x0000 to 0xFFFF
        void **RegMap;
        // This contains the length information for each registers.
        size_t RegLength[65536];
        struct Header {
                      unsigned __int16 ConnectionID;
                      unsigned __int16 ProtocolID;
                      unsigned __int16 DatagramLength;
                      unsigned __int8 FunctionCode; //This is first because the copy process exchanges low and high bytes.
                      unsigned __int8 DevAddress;
                      };
        union HeaderAsReadable {
                               unsigned __int8 as_byte[8];
                               Header as_Header;
                               } CurrentHeader;

        // This uses the variable Socket to read the buffer from the TCP/IP
        // connection. That's why it does not need any parameters.
        int __fastcall OnMBDataArrived(void);

        // This does something if the timer Tmr expires.
        void __fastcall TModbusTCPServerStack::OnTmrExpires(TObject *Sender);

};
#endif

