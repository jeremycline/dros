#include <stddef.h>
#include <string.h>

int memcmp(const void *string1, const void *string2, size_t n)
{
    const unsigned char *s1 = (const unsigned char *) string1;
    const unsigned char *s2 = (const unsigned char *) string2;

    for(size_t i = 0; i < n; i++)
    {
        if(s1[i] - s2[i] != 0)
        {
            return s1[i] - s2[i];
        }
    }

    return 0;
}
