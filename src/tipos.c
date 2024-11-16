#include "tipos.h"

size_t hasher(const char *str)
{
	size_t idx = 5381;
	size_t c;

	while ((c = (size_t)*str++)) {
		idx = ((idx << 5) + idx) + c; // hash * 33 + c
	}
	return idx;
}
