//---------------------------------------------------------------------------
//                  Logging functionality to a TMemo control
//
// Author: Csonka G�bor okl. villamosm�rn�k, 2005-2018. �ltal�nos cucc,
// sz�rmaztass bel�le objectet, ezt ne �rd �t!!!
//
// Author: G�bor Csonka M.Sc., 2005-2018. General object class, please derive
// your own class from it. Please don't modify this class.
// ToDo: writing a component derived from TMemo with this functionality.
//
// Hierarchia: TObject -- TCustomLogToMemo
// Hierarchy: TObject -- TCustomLogToMemo
//---------------------------------------------------------------------------


#ifndef TLog_H
#define TLog_H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <stdtypes.h>
//---------------------------------------------------------------------------

class TCustomLogToMemo : public TObject
{
private:	// User declarations

public:		// User declarations
        //Clears the log.
        void logClear(TMemo *log);

        //Like a std printf.
        void logPrintf(TMemo *log, const char *format, ...);

        // Standard constructor
        __fastcall TCustomLogToMemo(void);
};
#endif

