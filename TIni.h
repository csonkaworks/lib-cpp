//---------------------------------------------------------------------------
// Szerzõ: Csonka Gábor okl. villamosmérnök, 2005.
// Hierarchia: TObject -- TINIRW
//---------------------------------------------------------------------------

#ifndef TIni_H
#define TIni_H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include <inifiles.hpp>
//---------------------------------------------------------------------------
class TINIRW : public TObject
{
private:	// User declarations
        AnsiString inifile;
public:		// User declarations
        TIniFile *ini;
       	AnsiString msg;
        void __fastcall GetDefaultName(void);  //Reinitialises the object with the applicaton's name.ini
        void __fastcall TestIni(void);
        virtual void __fastcall GetIni(void);
        virtual void __fastcall SaveIni(void);
        virtual void __fastcall AfterConstruction();
        virtual void __fastcall BeforeDestruction();
        virtual __fastcall TINIRW(void);
        virtual __fastcall TINIRW(AnsiString);
        virtual __fastcall TINIRW(char *);
//        virtual __fastcall TINIRW(int);
};
//---------------------------------------------------------------------------
// extern TINIRW *IniRW;       Csak definíció. Nem hozunk létre objektumpéldányt.
//---------------------------------------------------------------------------
#endif
