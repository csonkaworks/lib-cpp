//---------------------------------------------------------------------------
//
// reWritten by Csonka Gabor (Gabor Csonka in English convention name order), 2009.
// Comments, suggestions and donations are welcome. My e-mail address is
// g.csonka@freemail.hu This is my PayPal account too.
//
//---------------------------------------------------------------------------
//
// It is a pure class but can be VCL compatible if _VCL_COMPATIBILITY_NEEDS
// have defined. But it results about 600,000 more lines to compile. :-P
//
// This is an OOP version of the code written by the author described below.
//

/*
******************************************************************
**       Advanced Encryption Standard implementation in C.      **
**       By Niyaz PK                                            **
**       E-mail: niyazlife@gmail.com                            **
**       Downloaded from Website: www.hoozi.com                 **
******************************************************************
This is the source code for encryption using the latest AES algorithm.
AES algorithm is also called Rijndael algorithm. AES algorithm is
recommended for non-classified by the National Institute of Standards
and Technology(NIST), USA. Now-a-days AES is being used for almost
all encryption applications all around the world.

THE MAIN FEATURE OF THIS AES ENCRYPTION PROGRAM IS NOT EFFICIENCY; IT
IS SIMPLICITY AND READABILITY. THIS SOURCE CODE IS PROVIDED FOR ALL
TO UNDERSTAND THE AES ALGORITHM.

Comments are provided as needed to understand the program. But the
user must read some AES documentation to understand the underlying
theory correctly.

It is not possible to describe the complete AES algorithm in detail
here. For the complete description of the algorithm, point your
browser to:
http://www.csrc.nist.gov/publications/fips/fips197/fips-197.pdf

Find the Wikipedia page of AES at:
http://en.wikipedia.org/wiki/Advanced_Encryption_Standard
******************************************************************
*/

//#define _VCL_COMPATIBILITY_NEEDS


#ifndef AES_H
#define AES_H

#ifdef _VCL_COMPATIBILITY_NEEDS
#include <system.hpp>
#endif

//---------------------------------------------------------------------------
class TAES
#ifdef _VCL_COMPATIBILITY_NEEDS
: public TObject
#endif
{
private:
        int Nr;      // The number of rounds in AES Cipher.
        int Nk;      // The number of 32 bit words in the key.
        unsigned char state[4][4];   // holds the intermediate results during encryption.
        unsigned char RoundKey[240]; // The array that stores the round keys.
        // The round constant word array, Rcon[i], contains the values given by
        // x to th e power (i-1) being powers of x (x is denoted as {02}) in the field GF(28)
        // Note that i starts at 1, not 0). The constructor fills it up.
        int Rcon[255];
        // common and Cipher-specific functions
        int getSBoxValue(int num);
        void KeyExpansion();
        void AddRoundKey(int round);
        void SubBytes();
        void ShiftRows();
        void MixColumns();
        // invCipher-specific functions
        int getSBoxInvert(int num);
        void InvSubBytes();
        void InvShiftRows();
        void InvMixColumns();
public:
        unsigned char in[16];   // holds the plain text to be encrypted.
        unsigned char out[16];  // holds the key for encryption.
        unsigned char Key[32];  // The Key input to the AES Program
        void Cipher(int keylength); // Keylength in bits (128, 192, or 256 only)
        void InvCipher(int keylength); // Keylength in bits (128, 192, or 256 only)
        TAES(void);
};

#endif
