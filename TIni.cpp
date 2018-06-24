//---------------------------------------------------------------------------
// Szerzõ: Csonka Gábor okl. villamosmérnök, 2005. Általános cucc,
// származtass belõle objectet, ezt ne írd át!!!
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <stdio.h>
#include <string.h>
#include <inifiles.hpp>
#include "TIni.h"


//---------------------------------------------------------------------------
#pragma package(smart_init)
// TINIRW *IniRW;      Ez csak definiál. Nem hozunk létre objektumpéldányt.

//---------------------------------------------------------------------------

__fastcall TINIRW::TINIRW(AnsiString FileName)
:TObject()
{
msg="";
if (FileName.IsEmpty()) GetDefaultName();
   else                 inifile=FileName;
ini=new TIniFile(inifile);
}
//---------------------------------------------------------------------------

__fastcall TINIRW::TINIRW(char *FileName)
:TObject()
{
AnsiString s=FileName;
msg="";
if (s.IsEmpty()) GetDefaultName();
   else          inifile=s;
ini=new TIniFile(inifile);
}
//---------------------------------------------------------------------------

__fastcall TINIRW::TINIRW()
:TObject()
{
msg="";
GetDefaultName();
ini=new TIniFile(inifile);
}
//---------------------------------------------------------------------------

void __fastcall TINIRW::AfterConstruction()
{
// Innen lett kivéve, ami a konstruktorban van.
}
//---------------------------------------------------------------------------

void __fastcall TINIRW::BeforeDestruction()
{
delete ini;
}
//---------------------------------------------------------------------------

void __fastcall TINIRW::GetDefaultName(void)
{
inifile=ChangeFileExt(Application->ExeName,".ini");
if (fclose(fopen(inifile.c_str(),"rt"))) msg=msg.sprintf("%s not found. Exiting.",inifile);
}
//---------------------------------------------------------------------------

void __fastcall TINIRW::TestIni(void)
{
Application->MessageBox("In window","Title",MB_OK | MB_TASKMODAL);
}
//---------------------------------------------------------------------------

void __fastcall TINIRW::GetIni(void)
{
// Felül kell definiálni azzal, amit az adott formon fel akarunk húzni. Példák:
//_MainForm_->OutputFileName->Text=ini->ReadString("Measue","Datafile","f:\\adc32");
//_MainForm_->OwriteAttn->Checked=!ini->ReadBool("Measue","Overwrite",true);
return;
}
//---------------------------------------------------------------------------

void __fastcall TINIRW::SaveIni(void)
{
// Felül kell definiálni azzal, amit az adott formról ki akarunk menteni. Példák:
//ini->WriteString("Measue","Datafile",_MainForm_->OutputFileName->Text);
//ini->WriteBool("Measue","Overwrite",!_MainForm_->OwriteAttn->Checked);
return;
}
//---------------------------------------------------------------------------

/* Ez egy példa a comm port felhúzásra. Ilyennel is lehet bõvíteni az objectet.
bool __fastcall TINIRW::GetComm(void)
{
char hiba[1024]="";
int tmp;
TIniFile *ini=new TIniFile(inifile);
// ------- Config read.Port num
if (!(tmp=ini->ReadInteger("Serial","Port",0)))
             {
             sprintf(hiba,"Nincs, vagy hibás a COM port információ.\nA %s file szerkesztendõ.\n[Serial]\nPort=[1..4]",inifile);
             Application->MessageBox(hiba,"Végzetes hiba",MB_OK | MB_TASKMODAL | MB_ICONSTOP);
             delete ini;
             return false;
             }
_MainForm_->VaComm1->PortNum=tmp;
// ------- Config read.Bits/byte
switch (ini->ReadInteger("Serial","Bits",0))
            {
            case 4: _MainForm_->VaComm1->Databits=db4; break;
            case 5: _MainForm_->VaComm1->Databits=db5; break;
            case 6: _MainForm_->VaComm1->Databits=db6; break;
            case 7: _MainForm_->VaComm1->Databits=db7; break;
            case 8: _MainForm_->VaComm1->Databits=db8; break;
            default: sprintf(hiba,"Nincs, vagy hibás a COM port bits/byte információ.\nA %s file szerkesztendõ.\n[Serial]\nBits=[4..8]",inifile);
                     Application->MessageBox(hiba,"Végzetes hiba",MB_OK | MB_TASKMODAL | MB_ICONSTOP);
                     delete ini;
                     return false;
            }
// ------- Config read.Flow control
switch (ini->ReadInteger("Serial","FlowCntl",-1))
            {
            case 0: _MainForm_->VaComm1->FlowControl->OutCtsFlow=false;
                    _MainForm_->VaComm1->FlowControl->OutDsrFlow=false;
                    _MainForm_->VaComm1->FlowControl->ControlDtr=dtrDisabled;
                    _MainForm_->VaComm1->FlowControl->ControlRts=rtsDisabled;
                    _MainForm_->VaComm1->FlowControl->XonXoffOut=false;
                    _MainForm_->VaComm1->FlowControl->XonXoffIn=false;
                    break;
            case 1: _MainForm_->VaComm1->FlowControl->OutCtsFlow=true;
                    _MainForm_->VaComm1->FlowControl->OutDsrFlow=false;
                    _MainForm_->VaComm1->FlowControl->ControlDtr=dtrDisabled;
                    _MainForm_->VaComm1->FlowControl->ControlRts=rtsHandshake;
                    _MainForm_->VaComm1->FlowControl->XonXoffOut=false;
                    _MainForm_->VaComm1->FlowControl->XonXoffIn=false;
                    break;
            case 2: _MainForm_->VaComm1->FlowControl->OutCtsFlow=false;
                    _MainForm_->VaComm1->FlowControl->OutDsrFlow=false;
                    _MainForm_->VaComm1->FlowControl->ControlDtr=dtrDisabled;
                    _MainForm_->VaComm1->FlowControl->ControlRts=rtsDisabled;
                    _MainForm_->VaComm1->FlowControl->XonXoffOut=true;
                    _MainForm_->VaComm1->FlowControl->XonXoffIn=true;
                    break;
            default: sprintf(hiba,"Nincs, vagy hibás a COM port flow control információ.\nA %s file szerkesztendõ.\n[Serial]\nFlowCntl=[0..2]\n0: nincs, 1: RTS-CTS, 2: XON-XOFF",inifile);
                     Application->MessageBox(hiba,"Végzetes hiba",MB_OK | MB_TASKMODAL | MB_ICONSTOP);
                     delete ini;
                     return false;
            }
// ------- Config read.Stop bits
strcpy(hiba,ini->ReadString("Serial","StopBits","?").c_str());
if (!strcmp(hiba,"1")) _MainForm_->VaComm1->Stopbits=sb1;
   else if (!strcmp(hiba,"1.5")) _MainForm_->VaComm1->Stopbits=sb15;
        else if (!strcmp(hiba,"2")) _MainForm_->VaComm1->Stopbits=sb2;
             else {
                  sprintf(hiba,"Nincs, vagy hibás a COM port stopbit információ.\nA %s file szerkesztendõ.\n[Serial]\nStopBits=[1 | 1.5 | 2]",inifile);
                  Application->MessageBox(hiba,"Végzetes hiba",MB_OK | MB_TASKMODAL | MB_ICONSTOP);
                  delete ini;
                  return false;
                  }
// ------- Config read.Parity
strcpy(hiba,ini->ReadString("Serial","Parity","?").c_str());
if (!strcmp(hiba,"None")) _MainForm_->VaComm1->Parity=paNone;
   else if (!strcmp(hiba,"Odd")) _MainForm_->VaComm1->Parity=paOdd;
        else if (!strcmp(hiba,"Even")) _MainForm_->VaComm1->Parity=paEven;
             else if (!strcmp(hiba,"Mark")) _MainForm_->VaComm1->Parity=paMark;
                  else if (!strcmp(hiba,"Space")) _MainForm_->VaComm1->Parity=paSpace;
                       else {
                            sprintf(hiba,"Nincs, vagy hibás a COM port paritás információ.\nA %s file szerkesztendõ.\n[Serial]\nParity=[None | Even | Odd | Mark | Space]",inifile);
                            Application->MessageBox(hiba,"Végzetes hiba",MB_OK | MB_TASKMODAL | MB_ICONSTOP);
                            delete ini;
                            return false;
                            }
// ------- Config read.BaudRate
if (!(tmp=ini->ReadInteger("Serial","BaudRate",0)))
                            {
                            sprintf(hiba,"Nincs, vagy hibás a COM port adatátviteli sebesség információ.\nA %s file szerkesztendõ.\n[Serial]\nBaudRate=[300..115200]",inifile);
                            Application->MessageBox(hiba,"Végzetes hiba",MB_OK | MB_TASKMODAL | MB_ICONSTOP);
                            delete ini;
                            return false;
                            }
_MainForm_->VaComm1->UserBaudrate=tmp;
delete ini;
return true;
}
*/
//---------------------------------------------------------------------------

