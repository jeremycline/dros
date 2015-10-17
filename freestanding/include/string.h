#ifndef _STRING_H
#define _STRING_H 1


int memcmp(const void *, const void *, size_t);

/**Copy n bytes from the source memory location to the destination.
 * The memory areas must not overlap.
 *
 * @param destination_pointer   A pointer to the the destination memory location.
 * @param source_pointer        A pointer to the source memory location.
 * @param n                     The number of bytes to copy.
 * @return                      A pointer to the destination memory location.
 * @see memmove
 */
void * memcpy(void *, const void *, size_t);

/** Copies n bytes from the source memory to the destination.
 * The memory area is allowed to overlap, unlike memcpy.
 * 
 * @param destination_pointer pointer to the start of the destination
 * @param source_pointer pointer the start of the source
 * @param n number of the bytes to copy.
 * @see memcpy
 */
void * memmove(void *, const void *, size_t);


void * memset(void *, int, size_t);

/*
 * Calculate the length of a null terminated string excluding
 * the terminating null character
 */
size_t strlen(const char*);

#endif
