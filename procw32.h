//---------------------------------------------------------------------------
// Szerzõ: Csonka Gábor okl. villamosmérnök, 1998-2007.
// Author: Gábor Csonka M.Sc. EE., 1998-2007.
//---------------------------------------------------------------------------

// Processing utitlites for win32

#ifdef __cplusplus
extern "C" {
#endif

// Makes the data in buf human readable hex 2digit format. For example if buf
// contains "Hello World!", the output will be "48 65 6C 6C 6F 20 57 6F 72 6C
// 64 21\0". It is the user's responsibility to free the result's space by
// calling free().)
// !!! Does not work if AnsiString is not defined.
char *Bin2HexA(void *buf,int length);

// Creates a pointer to a string contains date and time in yyyy. mm. dd. hh:mm:ss
// format. User is responsible to free the space this pointer points to.
// !!! Does not work if TDateTime is not defined.
char *StrNow();

#ifdef __cplusplus
}
#endif


