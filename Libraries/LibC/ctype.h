#pragma once

#include "sys/cdefs.h"

__BEGIN_DECLS

#define _U 01
#define _L 02
#define _N 04
#define _S 010
#define _P 020
#define _C 040
#define _X 0100
#define _B 0200

extern const char _ctype_[256];

int tolower(int c);
int toupper(int c);

static inline int isalnum(int c)
{
	return (_ctype_[(unsigned char)(c)] & (_U | _L | _N));
}

static inline int isalpha(int c)
{
	return (_ctype_[(unsigned char)(c)] & (_U | _L));
}

static inline int iscntrl(int c)
{
	return (_ctype_[(unsigned char)(c)] & (_C));
}

static inline int isdigit(int c)
{
	return (_ctype_[(unsigned char)(c)] & (_N));
}

static inline int isxdigit(int c)
{
	return (_ctype_[(unsigned char)(c)] & (_N | _X));
}

static inline int isspace(int c)
{
	return (_ctype_[(unsigned char)(c)] & (_S));
}

static inline int ispunct(int c)
{
	return (_ctype_[(unsigned char)(c)] & (_P));
}

static inline int isprint(int c)
{
	return (_ctype_[(unsigned char)(c)] & (_P | _U | _L | _N | _B));
}

static inline int isgraph(int c)
{
	return (_ctype_[(unsigned char)(c)] & (_P | _U | _L | _N));
}

static inline int islower(int c)
{
	return ((_ctype_[(unsigned char)(c)] & (_U | _L)) == _L);
}

static inline int isupper(int c)
{
	return ((_ctype_[(unsigned char)(c)] & (_U | _L)) == _U);
}

#define isascii(c) ((unsigned)c <= 127)
#define toascii(c) ((c)&127)

__END_DECLS