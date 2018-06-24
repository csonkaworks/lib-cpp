//---------------------------------------------------------------------------
//                  Logging functionality to a TMemo control
//
// Author: Csonka Gábor okl. villamosmérnök, 2005-2018. Általános cucc,
// származtass belõle objectet, ezt ne írd át!!!
//
// Author: Gábor Csonka M.Sc., 2005-2018. General object class, please derive
// your own class from it. Please don't modify this class.
// ToDo: writing a component derived from TMemo with this functionality.
//
// Hierarchia: TObject -- TCustomLogToMemo
// Hierarchy: TObject -- TCustomLogToMemo
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

//#include <vcl.h>
//#pragma hdrstop

#include <dos.h>
#include <stdarg.h>
#include <stdio.h>
#include "TLog.h"

__fastcall TCustomLogToMemo::TCustomLogToMemo(void)
:TObject()
{
     //
}
//---------------------------------------------------------------------------

void TCustomLogToMemo::logClear(TMemo *log)
{
     log->Clear();
}
//---------------------------------------------------------------------------

void TCustomLogToMemo::logPrintf(TMemo *log, const char *format, ...)
{
     struct time t;
     uint16_t i;
     va_list arg;
     AnsiString timestamp = "", data = "";
     gettime(&t);
     timestamp = timestamp.sprintf("%2d:%02d:%02d.%02d :: ",t.ti_hour, t.ti_min, t.ti_sec, t.ti_hund);
     va_start(arg, format);
     data.vprintf(format, arg);
     va_end(arg);
     log->Lines->Add(timestamp + data);
}
//---------------------------------------------------------------------------


