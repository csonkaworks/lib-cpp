//---------------------------------------------------------------------------
// Author: Gabor Csonka MSc. EE. 1992-2017.
// Suggestions and donations are welcome. gabor.csonka@gmail.com, my PayPal
// account as well.
//---------------------------------------------------------------------------

// Purpose: serial port enumeration to double zero terminated string array
// or Borland CPP Builder ComboBox object.

#ifndef serPortEnumH
#define serPortEnumH
//---------------------------------------------------------------------------
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <winbase.h>
#include <winreg.h>
#include "nulltstr.h"
#include <StdCtrls.hpp>   //Because of ComboBox
//---------------------------------------------------------------------------
using namespace std;

class serPortEnum {

public:
        serPortEnum(void);
        virtual char **enumeratePortsSimpleStr(void);
        virtual char **enumeratePortsDetailedStr(void);
        virtual unsigned long int freeStrList(char **);
        virtual void enumeratePortsSimpleComboBox(TComboBox *);
        virtual void enumeratePortsDetailedComboBox(TComboBox *);
private:
        bool regEnumKey(HANDLE *key, char *value, AnsiString *friendlyName);

};
#endif