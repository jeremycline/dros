#include <stddef.h>
#include <string.h>

/*
 * Calculate the length of a null terminated string excluding
 * the terminating null character
 */
size_t strlen(const char *string)
{
	size_t size = 0;
	while (string[size] != 0) {
		size++;
	}
	return size;
}

