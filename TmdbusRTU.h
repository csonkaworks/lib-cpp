//---------------------------------------------------------------------------
//            ModBUS communication routines -- header
//
// Szerzõ: Csonka Gábor okl. villamosmérnök, 2005-2007. Általános cucc,
// származtass belõle objectet, ezt ne írd át!!!
// A származtatott objectben kell megírni az adatforrás szerinti
// void MBWriteChar(unsigned __int8) 1 karaktert a buszra küldõ, és a
// void OnMBDataArrived (unsigned __int8 *) adat jött eseményt kezelõ
// függvényeket.
//
// Author: Gábor Csonka M.Sc., 2005-2007. General object class, please inherit
// your own type from it. Please don't modify this class.
// You must overload two empty functions:
// void MBWriteChar(unsigned __int8) sends a character to the physical bus.
// void OnMBDataArrived (unsigned __int8 *) is an event handler: this fills up
// the input buffer.
//
// Hierarchia: TObject -- TCustomModbusRTU
// Hierarchy: TObject -- TCustomModbusRTU
//---------------------------------------------------------------------------

#ifndef TmdbusRTU_H
#define TmdbusRTU_H
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------

class TCustomModbusRTU : public TObject
{
private:	// User declarations
        // Actually, this is an empty function. It must be overloaded with a
        // function what sends a character to the physical bus or initiates a
        // function what does it.
        // (It must be declared virtual because there are TCustomModbusRTU
        // member functions call it.)
        virtual void __fastcall MBWriteChar(unsigned __int8 c);

public:		// User declarations
        enum {mdbIdle,mdbReadReg,mdbWriteReg} CurrentFunction;
        struct mbrec {
                     unsigned __int8 address;
                     unsigned __int8 command;
                     unsigned __int16 startreg;
                     unsigned __int16 regs;
                     unsigned __int8 count;
                     unsigned __int8 *buffer;
                     };

        // Actually, this is an empty function. It must be overloaded with a
        // function what reads the received bytes from the physical bus or
        // initiates a function to do it. It can return the length of buf and
        // returns 0 actually.
        // (Not need to declare it virtual because no TCustomModbusRTU member
        // function calls it but we declare it virtual anyway.)
        virtual int __fastcall OnMBDataArrived(unsigned __int8 *inbuffer);

        // Sends a byte frame with modbus-style CRC.
        void __fastcall SendGen(unsigned __int16 length,unsigned __int8 *buf);

        // Sends a read (0x03) frame to selected address reading from startreg
        // a number of regs registers.
        void __fastcall SendRead(unsigned __int16 RemoteAddress,
                                 unsigned __int16 startreg,
                                 unsigned __int16 regs);

        // Sends a write (0x10) frame to selected address to write from startreg
        // a number of regs registers. Sum of count bytes. The array to write is
        // in buf.
        void __fastcall SendWrite(unsigned __int16 RemoteAddress,
                                  unsigned __int16 startreg,
                                  unsigned __int16 regs,
                                  unsigned __int8 count,unsigned __int8 *buf);

        // Sends a custom read modbus frame. See struct mbrec for the details.
        void __fastcall SendCustomRead(struct mbrec frame);

        // Sends a custom write modbus frame. See struct mbrec for the details.
        void __fastcall SendCustomWrite(struct mbrec frame);

        // Sends back an answer frame to a Read (0x03) request.
        void __fastcall AnswerCustomRead(struct mbrec frame);

        // Sends back an answer frame to a Write (0x10) request.
        void __fastcall AnswerCustomWrite(struct mbrec frame);

        // Analizes a frame and fills up the mbrec structure. It is not protected
        // against out-indexing. Never try to send some data other than a valid
        // modbus frame! It returns code at .command:
        // .command         meaning
        //    0xF0        Not a read or write frame
        //    0x03        Read frame  (.count is the length of .buf. .buf must
        //                be freed after using.)
        //    0xFF        Bad CRC
        //    0xFA        Not enough memory to allocate .buf
        //    0xF3        The buffer length is smaller than the amount of data have indicated.
        //    0x10        Write frame (.count==0 and .buf==NULL)
        // This is for a master node got an answer from a slave.
        void __fastcall ProcessM(unsigned __int8 *inbuffer,int length,struct mbrec *temp);

        // Analizes a frame and fills up the mbrec structure. It is not protected
        // against out-indexing. Never try to send some data other than a valid
        // modbus frame! It returns code at .command:
        // .command         meaning
        //    0xF0        Not a read or write frame
        //    0x03        Read frame  (.count is the length of .buf. .buf must
        //                be freed after using.)
        //    0xFF        Bad CRC
        //    0xFA        Not enough memory to allocate .buf
        //    0xF3        The buffer length is smaller than the amount of data have indicated.
        //    0x10        Write frame (.count==0 and .buf==NULL)
        // This is for a slave node got a query from the master.
        void __fastcall ProcessS(unsigned __int8 *inbuffer,int length,struct mbrec *temp);

        // Standard constructor
        __fastcall TCustomModbusRTU(void);
};
#endif

