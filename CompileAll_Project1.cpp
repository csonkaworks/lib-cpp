//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("CompileAll_Project1.res");
USEUNIT("crc16.cpp");
USEUNIT("WinExit.cpp");
USEUNIT("readline.c");
USEUNIT("compares.c");
USEUNIT("F_lib.c");
USEUNIT("RDCONFIG.C");
USEUNIT("proc.c");
USEUNIT("procw32.cpp");
USEUNIT("NULLTSTR.C");
USEUNIT("TAES.cpp");
USEUNIT("sha2.c");
USEUNIT("TIni.cpp");
USEUNIT("TmdbusRTU.cpp");
USEUNIT("serPortEnum.cpp");
USEUNIT("TLog.cpp");
USEUNIT("\\vmware-host\Shared Folders\U\design\PROJECTS\lib-cpp\csvparser.c");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
//                 Application->Initialize();
//                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
