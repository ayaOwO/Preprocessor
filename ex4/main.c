#define A 4
#include "arch.h"
#include <stdio.h>

#ifdef x64
#define NAME "X64"
#else
#define NAME "X86"
#endif

int mein(void) {
	printf(NAME);
	return 0;
}
