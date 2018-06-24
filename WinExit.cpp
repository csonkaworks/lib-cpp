//---------------------------------------------------------------------------
// Szerzõ: Dombi László, Kanada   ---  2007
// Author: Leslie Dombi, Canada   ---  2007
//---------------------------------------------------------------------------

#include <system.hpp>

void ShutDownComputer(void)
  { OSVERSIONINFO s;
    BOOL b;
    s.dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
    if((b=GetVersionEx(&s))==TRUE)if(s.dwPlatformId!=VER_PLATFORM_WIN32_NT)b=FALSE;
    if(b)
    { HANDLE hToken;
      LUID takeOwnershipValue;
      TOKEN_PRIVILEGES tkp;
      OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY,&hToken);
      LookupPrivilegeValue(NULL,SE_SHUTDOWN_NAME,&takeOwnershipValue);
      tkp.PrivilegeCount=1;
      tkp.Privileges[0].Luid=takeOwnershipValue;
      tkp.Privileges[0].Attributes=SE_PRIVILEGE_ENABLED;
      AdjustTokenPrivileges(hToken,FALSE,&tkp,sizeof(TOKEN_PRIVILEGES),NULL,NULL);
    }
    ExitWindowsEx(EWX_FORCE|EWX_SHUTDOWN|EWX_POWEROFF,0);
  }

void ReBootComputer(void)
  { OSVERSIONINFO s;
    BOOL b;
    s.dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
    if((b=GetVersionEx(&s))==TRUE)if(s.dwPlatformId!=VER_PLATFORM_WIN32_NT)b=FALSE;
    if(b)
    { HANDLE hToken;
      LUID takeOwnershipValue;
      TOKEN_PRIVILEGES tkp;
      OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY,&hToken);
      LookupPrivilegeValue(NULL,SE_SHUTDOWN_NAME,&takeOwnershipValue);
      tkp.PrivilegeCount=1;
      tkp.Privileges[0].Luid=takeOwnershipValue;
      tkp.Privileges[0].Attributes=SE_PRIVILEGE_ENABLED;
      AdjustTokenPrivileges(hToken,FALSE,&tkp,sizeof(TOKEN_PRIVILEGES),NULL,NULL);
    }
    ExitWindowsEx(EWX_FORCE|EWX_REBOOT,0);
  }

