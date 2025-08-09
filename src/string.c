#include <string.h>

void *memcpy(void *dest, const void *src, size_t n)
{
        char *d = dest;
        const char *s = src;
        while (n--)
        {
                *d++ = *s++;
        }
        return dest;
}

void *memset(void *s, int c, size_t n)
{
        unsigned char *p = s;
        while (n--)
        {
                *p++ = (unsigned char)c;
        }
        return s;
}

int strcmp(const char *s1, const char *s2)
{
        while (*s1 && (*s1 == *s2))
        {
                s1++;
                s2++;
        }
        return *(unsigned char *)s1 - *(unsigned char *)s2;
}

size_t strlen(const char *s)
{
        const char *p = s;
        while (*p)
        {
                p++;
        }
        return p - s;
}

char *strcpy(char *dest, const char *src)
{
        char *d = dest;
        while ((*d++ = *src++));
        return dest;
}

char *strcat(char *dest, const char *src)
{
        char *d = dest;
        while (*d)
        {
                d++;
        }
        while ((*d++ = *src++));
        return dest;
}
