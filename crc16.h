//---------------------------------------------------------------------------
//
// Author: Csonka Gabor (Gabor Csonka in English convention name order), 1999-2003.
// Comments, suggestions and donations are welcome. My e-mail address is
// g.csonka@freemail.hu This is my PayPal account also.
//
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Author of the original crc16: Calta Computer, Ltd., USA
// Author of the lrc8 function: Modbus.org
//---------------------------------------------------------------------------

/* Here is a routine which calculates the CRC 16 used by MODBUS RTU protocol */

// Needs the address of the crc remainder word (crc_rem) and the new value
// byte (nvalue). Modifies the reaminder accordingly. In Modbus RTU,
// crc_rem starts from 0xFFFF.
void crc16(unsigned __int16 *crc_rem, unsigned __int8 nvalue);


// Needs the polynomial with the highest bit, address of the crc remainder word
// (crc_rem) and the new value byte (nvalue). Modifies the reaminder accordingly.
void genCRC16(unsigned __int16 poly,unsigned __int16 *crc_rem, unsigned __int8 nvalue);


// This calculates the LRC of the MODBUS ASCII protocol. It must be performed
// on 8bit bytes not on the encoded nibbles.
// Needs the address of the message to calculate LRC upon (auchMsg) and the
// quantity of bytes in message (usDataLen). Returns the calculated LRC.
static unsigned char lrc8(unsigned char *auchMsg, unsigned short usDataLen);
