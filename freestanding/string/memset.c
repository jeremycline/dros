#include <stddef.h>
#include <string.h>

void * memset(void *destination_pointer, int constant, size_t n)
{
    char *destination = (char *) destination_pointer;
    for(size_t i = 0; i < n; i++)
    {
        destination[i] = constant;
    }
    return destination_pointer;
}
