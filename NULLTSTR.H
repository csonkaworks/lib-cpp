//---------------------------------------------------------------------------
//
// Author: Csonka Gabor MSc. EE. (Gabor Csonka in English convention name
// order), 1998-2017.
// Comments, suggestions and donations are welcome. My e-mail address is
// gabor.csonka@gmail.com This is my PayPal account as well.
//
//---------------------------------------------------------------------------

// Purpose: Null terminated string utils


#ifndef _NULLTSTR_H_
#define _NULLTSTR_H_

#ifdef __cplusplus
extern "C" {
#endif

// For example returns 'A' if c=='a'. If c is not a letter or it is a big
// letter it remains unchanged.
char UpCase(char c);

// For example returns 'a' if c=='A'. If c is not a letter or it is a small
// letter it remains unchanged.
char LowCase(char c);

// Searches a string in a string array. Returns the index of the first
// occurrence if found otherwise returns a_length. The a_length is
// the length of the array. (array[0]..array[a_length-1] are available.)
int strastr(char **array,char *str,int a_length);

// Same as before but case-insensitive.
int straistr(char **array,char *str,int a_length);

// Allocates a null terminated string and fills it with 0x00's. (Allocates
// n+1 bytes.) When fails returns NULL. User is responsible to free it.
char *allocstr(size_t n);
#define stralloc(n) (allocstr(n))

// Allocates space for dest and copies source to it. Returns the new string if
// succeed otherwise returns NULL. User is responsible to free it.
char *stracpy(char *source);

// Reallocates space for source and concatenates s to it. Returns the new
// string if succeed otherwise returns NULL. User is responsible to free it.
// Use it only on an initilised source.
char *stracat(char *source, char *s);

// Builds a null terminated string array and returns a pointer to it. 
// The array's last item has a 0 after its terminating 0, other items have
// 0xff. User is responsible to free the array and the items as well.
char **strarray(char **array, char *item);

// Frees a double zero terminated string array and its items as well. Returns
// items have been freed.
unsigned long int freestrarray(char **array);


#ifdef __cplusplus
}
#endif

#endif
