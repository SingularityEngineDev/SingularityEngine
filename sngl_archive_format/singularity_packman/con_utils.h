#ifndef _SNGL_PACKMAN_CON_UTILS_H_INCLUDED_
#define _SNGL_PACKMAN_CON_UTILS_H_INCLUDED_

#include <stdint.h>

struct ConSize
{
	uint32_t w;
	uint32_t h;
};

ConSize GetConsoleSize();

#endif