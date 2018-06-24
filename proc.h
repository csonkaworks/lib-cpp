//---------------------------------------------------------------------------
// Szerzõ: Csonka Gábor okl. villamosmérnök, 1998-2007.
// Author: Gábor Csonka M.Sc. EE., 1998-2007.
//---------------------------------------------------------------------------

// Processing utitlites

#ifndef __PROC_H
#define __PROC_H

#ifdef __cplusplus
extern "C" {
#endif

// Returns upper byte of w.
unsigned __int8 hi8(unsigned __int16 w);
unsigned __int8 hi(unsigned __int16 w);  //For backward compatibility

// Returns lower byte of w.
unsigned __int8 lo8(unsigned __int16 w);
unsigned __int8 lo(unsigned __int16 w);  //For backward compatibility

//Returns upper/lower word of a double word respectively
unsigned __int16 hi16(unsigned __int32 dw);
unsigned __int16 lo16(unsigned __int32 dw);

//Returns upper/lower dword of a quad word respectively
unsigned __int32 hi32(unsigned __int64 qw);
unsigned __int32 lo32(unsigned __int64 qw);

//Mirrors the bytes
void mirror16(unsigned __int16 *);
void mirror32(unsigned __int32 *);
void mirror64(unsigned __int64 *);

//Returns s if n != 1, otherwise ""
char *s_int(long int n, const char *s);
char *s_dbl(long double n, const char *s);

// For example returns 'A' if c=='a'. If c is not a letter or it is a big
// letter it remains unchanged.
char UpCase(char c);

// For example returns 'a' if c=='A'. If c is not a letter or it is a small
// letter it remains unchanged.
char LowCase(char c);

// Searches a string in a string array. Returns the index of the first
// occurrence if found otherwise returns a_length. The a_length is
// the length of the array. (array[0]..array[a_length-1] are available.)
int strastr(char **array,char *str,int a_length);

//Allocates a null terminated string and fills it with 0x00's. (Allocates
//n+1 bytes.) When fails returns NULL.
char *allocstr(size_t n);

// Gets unlimited number of characters without echoing them back. (The
// standard getpass stores only 8 characters.) Returns a pointer to the
// character string. The user is responsible to free it. It returns when
// reaches \r or \n character.
char *GetPass(const char *message);

#ifdef __cplusplus
}
#endif

#endif
