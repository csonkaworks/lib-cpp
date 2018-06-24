//---------------------------------------------------------------------------
// Author: Gabor Csonka MSc. EE. 1992-2017.
// Suggestions and donations are welcome. gabor.csonka@gmail.com, my PayPal
// account as well.
//---------------------------------------------------------------------------

// Purpose: serial port enumeration to double zero terminated string array
// or Borland CPP Builder ComboBox object.

#include "serPortEnum.h"
#pragma link "nulltstr"

//---------------------------------------------------------------------------
serPortEnum::serPortEnum(void) {
}
//---------------------------------------------------------------------------

bool serPortEnum::regEnumKey(HANDLE *key, char *value, AnsiString *friendlyName) {
HANDLE currentKey;
AnsiString baseName=*friendlyName,temp,searchValue;
DWORD regIndex, valueIndex, bufSize, valueNameSize, valueDataSize, type;
char subkeyName[8192], valueName[512], valueData[8192];
searchValue=searchValue.sprintf("(%s)",value);
for (regIndex=0;;regIndex++) {
    bufSize=8191;
    if (RegEnumKeyEx(*key,regIndex,subkeyName,&bufSize,NULL,NULL,NULL,NULL)!=ERROR_SUCCESS) return false;
    //Memo2->Lines->Add(subkeyName);
    for (valueIndex=0;;valueIndex++) {
        valueNameSize=511;
        valueDataSize=8191;
        type=REG_SZ;
        if (RegEnumValue(*key,valueIndex,valueName,&valueNameSize,NULL,&type,valueData,&valueDataSize)!=ERROR_SUCCESS) break;
        if (strstr(valueData,searchValue.c_str())!=NULL) {
           friendlyName->sprintf("%s ==> %s",baseName.c_str(),valueData);
           return false;
           }
        //temp=temp.sprintf("%s --> %s",valueName,valueData);
        //Memo3->Lines->Add(temp);
        }
    if (RegOpenKeyEx(*key,subkeyName,0,KEY_READ | KEY_EXECUTE,&currentKey)==ERROR_SUCCESS)
       if (!regEnumKey(&currentKey,value,friendlyName)) RegCloseKey(currentKey);
    }
//Both of them works
//friendlyName->printf("Lofasz");
//*friendlyName="Lofasz";
return false;
}
//---------------------------------------------------------------------------

char **serPortEnum::enumeratePortsSimpleStr(void) {
HANDLE f;
char **comArray=NULL;
unsigned __int16 i,n=0;
char genericName[32],comName[32];
for (i=0;i<256;i++) {
    sprintf(genericName,"\\\\.\\COM%d",i);
    sprintf(comName,"COM%d",i);
    f=CreateFile(genericName,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
    if (f!=INVALID_HANDLE_VALUE) {
       comArray=strarray(comArray,comName);
       CloseHandle(f);
       if (comArray==NULL) return NULL;
       n++;
       }
    }
if (!n) comArray=strarray(comArray,"");
return comArray;
}
//---------------------------------------------------------------------------

char **serPortEnum::enumeratePortsDetailedStr(void){
HANDLE f,r;
char *realComName, **comArray=NULL;
unsigned __int16 i,n=0;
DWORD regIndex, valueIndex, bufSize=8191;
char genericName[32],comName[32];
FILETIME writtenAt;
AnsiString comDetailed;
if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,"SYSTEM\\CurrentControlSet\\Enum\\",0,KEY_READ | KEY_EXECUTE,&r)==ERROR_SUCCESS) {
   for (i=0;i<256;i++) {
       sprintf(genericName,"\\\\.\\COM%d",i);
       sprintf(comName,"COM%d",i);
       f=CreateFile(genericName,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
       if (f!=INVALID_HANDLE_VALUE) {
          comDetailed=comName;
          regEnumKey(&r,comName,&comDetailed);
          comArray=strarray(comArray,comDetailed.c_str());
          CloseHandle(f);
          if (comArray==NULL) return NULL;
          n++;
          }
       }
   RegCloseKey(r);
   if (!n) {
      comArray=strarray(comArray,"");
      if (comArray==NULL) return NULL;
      }
   }
   else {
   comArray=strarray(comArray,"Registry Error");
   if (comArray==NULL) return NULL;
   }
return comArray;
}
//---------------------------------------------------------------------------

unsigned long int serPortEnum::freeStrList(char **list){
return freestrarray(list);
}
//---------------------------------------------------------------------------

void serPortEnum::enumeratePortsSimpleComboBox(TComboBox *target) {
HANDLE f;
unsigned __int16 i,n=0;
char genericName[32],comName[32];
target->Clear();
for (i=0;i<256;i++) {
    sprintf(genericName,"\\\\.\\COM%d",i);
    sprintf(comName,"COM%d",i);
    f=CreateFile(genericName,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
    if (f!=INVALID_HANDLE_VALUE) {
       target->Items->Add(comName);
       CloseHandle(f);
       n++;
       }
    }
if (!n) target->Items->Add("No COM ports found");
target->ItemIndex=0;
}
//---------------------------------------------------------------------------

void serPortEnum::enumeratePortsDetailedComboBox(TComboBox *target) {
HANDLE f,r;
unsigned __int16 i,n=0;
DWORD regIndex, valueIndex, bufSize=8191;
char genericName[32],comName[32];
FILETIME writtenAt;
AnsiString comDetailed;
target->Clear();
if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,"SYSTEM\\CurrentControlSet\\Enum\\",0,KEY_READ | KEY_EXECUTE,&r)==ERROR_SUCCESS) {
   for (i=0;i<256;i++) {
       sprintf(genericName,"\\\\.\\COM%d",i);
       sprintf(comName,"COM%d",i);
       f=CreateFile(genericName,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
       if (f!=INVALID_HANDLE_VALUE) {
          comDetailed=comName;
          regEnumKey(&r,comName,&comDetailed);
          target->Items->Add(comDetailed);
          CloseHandle(f);
          n++;
          }
       }
   target->ItemIndex=0;
   RegCloseKey(r);
   if (!n) target->Items->Add("No COM ports found");
   }
   else target->Items->Add("Registry error");
target->ItemIndex=0;
}
//---------------------------------------------------------------------------

