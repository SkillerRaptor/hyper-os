#include <LibC/ctype.h>

__BEGIN_DECLS

const char _ctype_[256] = {
	_C, _C, _C, _C, _C, _C, _C, _C,
	_C, _C | _S, _C | _S, _C | _S, _C | _S, _C | _S, _C, _C,
	_C, _C, _C, _C, _C, _C, _C, _C,
	_C, _C, _C, _C, _C, _C, _C, _C,
	(char)(_S | _B), _P, _P, _P, _P, _P, _P, _P,
	_P, _P, _P, _P, _P, _P, _P, _P,
	_N, _N, _N, _N, _N, _N, _N, _N,
	_N, _N, _P, _P, _P, _P, _P, _P,
	_P, _U | _X, _U | _X, _U | _X, _U | _X, _U | _X, _U | _X, _U,
	_U, _U, _U, _U, _U, _U, _U, _U,
	_U, _U, _U, _U, _U, _U, _U, _U,
	_U, _U, _U, _P, _P, _P, _P, _P,
	_P, _L | _X, _L | _X, _L | _X, _L | _X, _L | _X, _L | _X, _L,
	_L, _L, _L, _L, _L, _L, _L, _L,
	_L, _L, _L, _L, _L, _L, _L, _L,
	_L, _L, _L, _P, _P, _P, _P, _C
};

int tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return c | 0x20;
	return c;
}

int toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return c & ~0x20;
	return c;
}

__END_DECLS