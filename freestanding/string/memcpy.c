#include <stddef.h>
#include <string.h>

/**Copy n bytes from the source memory location to the destination.
 * The memory areas must not overlap.
 *
 * @param destination_pointer   A pointer to the the destination memory location.
 * @param source_pointer        A pointer to the source memory location.
 * @param n                     The number of bytes to copy.
 * @return                      A pointer to the destination memory location.
 * @see memmove
 */
void * memcpy(void * destination_pointer, const void * source_pointer, size_t n)
{
    char *dest = (char *) destination_pointer;
    char *src = (char *) source_pointer;

    for(size_t i = 0; i < n; i++)
    {
        dest[i] = src[i];
    }

    return destination_pointer;
}

