// Standard Windows INI file reader (c) Sziklay Peter & Csonka Gabor, 2000-
// 2002.
//
// The principles of the INI files
// -------------------------------
//
// A standard INI file contains many descriptors managed to groups. All
// descriptors have a string type value. For example:
// ;Test configuration file
// [MyFirstGroup]
// Beer=GiveMe
// Work=NotMuchPlease
// [My2ndGroup]
// TestDescr=0
// Beer=NotForKids
//
// Calling RdConfig with "[MyFirstGroup]" and "Beer" returns "GiveMe".
// Calling RdConfig with "[My2ndGroup]" and "Beer" returns "NotForKids".
// Calling RdConfig with "[My2ndGroup]" and "Work" returns empty string.
// Calling RdConfig with "[My2ndGroup]" and "TestDescr" returns "0".


// Detailed information on functions.
// ----------------------------------

// Needs complete file path, name and extension. Also needs a group like
// [MyGroup] and a descriptor like MyDescriptor. Returns the value of the
// descriptor if there is any or empty string. If file can not be opened it
// returns NULL. The user is responsible to free the returned pointer.
char *RdConfig(char *configfile,char *group,char *descriptor);

// Converts ASCII 255 (0xff) to 0x20 (space) in the null terminated string.
// Returns the length of the string. Can use for encoding/decoding values
// containing spaces. For example: TestDescr=Hello<0xff>World! where <0xff>
// means character with ASCII 255 will be converted to "Hello World!".
int Convert(char *s);
