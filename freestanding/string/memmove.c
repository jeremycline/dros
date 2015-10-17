#include <stddef.h>
#include <string.h>

/** Copies n bytes from the source memory to the destination.
 * The memory area is allowed to overlap, unlike memcpy.
 * 
 * @param destination_pointer pointer to the start of the destination
 * @param source_pointer pointer the start of the source
 * @param n number of the bytes to copy.
 * @see memcpy
 */
void * memmove(void *destination_pointer, const void *source_pointer, size_t n)
{
   char *destination = (char *) destination_pointer;
   char *source = (char *) source_pointer;

   if (source > destination)
   {
       for(size_t i = 0; i < n; i++)
       {
           destination[i] = source[i];
       }
   } else if (destination > source)
   {
       for(size_t i = n; i > 0; i--)
       {
           destination[i - 1] = source[i - 1];
       }
   }

   return destination_pointer;
}

