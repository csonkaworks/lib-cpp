

#ifndef _F_LIB_H_
#define _F_LIB_H_


#ifdef __cplusplus
extern "C" {
#endif

//----------- Checked fopen().
// If succeed returns a pointer to the opened file otherwise returns NULL and
// writes the error string to stdio.
FILE *cfopen(char *filename,char *mode,char *errorstring);


//----------- Extension change
// If succeed returns a pointer to the new filename. If unsuccessful returns
// NULL. newext must be a DOS standard maximum of 3 characters long string.
char *ChangeFileExt(char *fname,char *newext);


#ifdef __cplusplus
}
#endif

#endif
