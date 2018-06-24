//---------------------------------------------------------------------------
//
// Author: Csonka Gabor (Gabor Csonka in English convention name order), 2000-2004.
// Comments, suggestions and donations are welcome. My e-mail address is
// g.csonka@freemail.hu This is my PayPal account too.
//
//---------------------------------------------------------------------------


#ifndef _READLINE_H_
#define _READLINE_H_


#ifdef __cplusplus
extern "C" {
#endif

//----------- Line read from a stream with space allocation
// Character buffer will be allocated and must be freed by the user. It returns
// the read characters. On file error it returns NULL, on empty file it returns
// a pointer to a single 0.
// IT NOT WORKS WELL!!!
char *freadlinea_(FILE *f);

//----------- Another line read from a stream with space allocation
// Character buffer will be allocated and must be freed by the user. It returns
// the read characters. On file error or EOF it returns NULL, on empty file it
// returns a pointer to a single 0 (empty string).
// This may work better than the previous one.
char *freadlinea(FILE **f);

//----------- Line read from a stream.
// If succeed returns number of characters otherwise returns zero. Character
// buffer must have space for the longest line in the stream + 1.
int freadline(FILE *f,char *s);

//----------- Another line read from a stream.
// If succeed returns number of characters otherwise returns zero. Character
// buffer must have space for the longest line in the stream + 1.
int freadline_(FILE *f,char *s);

//----------- Line read from a string.
// If succeed returns number of characters otherwise returns zero. Character
// buffer must have space for the longest line in the stream + 1.
int sreadline(char *buf,char *s);

//----------- Line read from a stream.
// If succeed returns number of characters otherwise returns zero. Character
// buffer must have space for the longest line in the stream + 1. You can vary
// the NewLine character with parameter nl.
int gfreadline(FILE *f,char *s, const char nl);

//----------- Line read from a string.
// If succeed returns number of characters otherwise returns zero. Character
// buffer must have space for the longest line in the stream + 1. You can vary
// the NewLine character with parameter nl.
int gsreadline(char *buf,char *s, const char nl);


//----------- Line read from a string.
// If succeed returns number of characters otherwise returns zero. It allocates
// space for the result so it is the user's responsibility to free it. You can
// vary the NewLine character with parameter nl.
int gsreadlinea(char *buf,char *s, const char nl);


//----------- Line read from a string sequentially.
// If succeed returns number of characters otherwise returns zero. It allocates
// space for the result so it is the user's responsibility to free it. You can
// vary the NewLine character with parameter nl.
char *gsreadlineas(char **buf, const char nl);


//----------- Password read from console
// If succeed returns entered password otherwise returns NULL. The return value
// is an allocated string so the caller is responsible to free it.
// Disptext displayed before starting the read and each character displays as
// dispchar.
char *getpassa(const char *disptext, char dispchar);

#ifdef __cplusplus
}
#endif

#endif
