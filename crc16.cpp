//---------------------------------------------------------------------------
// Author of the original crc16: Calta Computer, Ltd., USA
// Author of the lrc8 function: Modbus.org
//---------------------------------------------------------------------------

/* Here is a routine which calculates the CRC 16 used by MODBUS RTU protocol */

/*****************************************************************************/
/* Function Name:  crc                                                       */
/* Purpose:        To calculate the 16 bit CRC remainder                     */
/* Parameters:     count, buffer addr.                                       */
/* Returns:        remainder                                                 */
/* Compatible with ANSI C, Kernighan & Ritchie and UNIX V in Turbo C++ V1.01 */
/*****************************************************************************/


void crc16(unsigned __int16 *crc_rem, unsigned __int8 nvalue)
{
unsigned int inner;
unsigned int mod;
(*crc_rem)^=nvalue;
for (inner=0;inner<8;inner++)
    {
    mod=(*crc_rem)&0x0001;
    (*crc_rem)>>=1;
    if (mod) (*crc_rem)^=0xa001;
    }
return;
}



void genCRC16(unsigned __int16 poly, unsigned __int16 *crc_rem, unsigned __int8 nvalue)
{
unsigned int inner;
unsigned int mod;
(*crc_rem)^=nvalue;
for (inner=0;inner<8;inner++)
    {
    mod=(*crc_rem)&0x0001;
    (*crc_rem)>>=1;
    if (mod) (*crc_rem)^=poly;
    }
return;
}



// This calculates the LRC of the MODBUS ASCII protocol. It must be performed
// on 8bit bytes not on the encoded nibbles.

static unsigned char lrc8(unsigned char *auchMsg, unsigned short usDataLen) /* the function returns the LRC as a type unsigned char */
//unsigned char *auchMsg ; /* message to calculate LRC upon */
//unsigned short usDataLen ; /* quantity of bytes in message */
{
unsigned char uchLRC = 0 ; /* LRC char initialized */
while (usDataLen--) /* pass through message buffer */
uchLRC += *auchMsg++ ; /* add buffer byte without carry */
return ((unsigned char)(-((char)uchLRC))) ; /* return twos complement */
}