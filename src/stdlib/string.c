#include <stdio.h>


void* memcpy(void* dest, const void* src, size_t n);
void* memset(void* s, int c, size_t n);
char* strcat(char* dest, const char* src);
char* strncat(char *dest, const char *src, size_t n);
char* strchr(const char* str, int ch);
char* strrchr(const char* str,int ch);
int strcmp(const char* str1, const char* str2);
char* strcpy(char* strDest, const char* strSrc);
char* strncpy(char* str1, const char* str2, size_t n);
size_t strlen(const char* strSrc);
size_t strspn(const char* s, const char* strCharSet);
char* strstr(const char *haystack, const char *needle);
// TODO: to complete the rest 


void* memcpy(void* dest, const void* src, size_t n)
{
    char* d = dest;
    const char* s = src;

    for(unsigned int i = 0; n != 0; n--, i++)
        *(d + i) = *(s + i);

    return dest;
}


void* memset(void* s, int c, size_t n)
{
    unsigned char* p = s;

    if (p == NULL)
        return NULL;

    for(; n != 0; n--, p++)
        *p = c;

    return s;
}


char* strcat(char* dest, const char* src)
{
    char* d = dest;
    const char* s = src;

    for(; *d != '\0'; d++)
        ;
    for(; *s != '\0'; s++, d++)
        *d = *s;
    *(d++) = '\0';

    return dest;
}


char* strncat(char *dest, const char *src, size_t n)
{
    char* d = dest;
    const char* s = src;

    for(; *d != '\0'; d++)
        ;
    for(; n != 0; n--, d++, s++)
        *d = *s;
    *(d++) = '\0';

    return dest;
}


char* strchr(const char* str, int ch)
{
    for(unsigned int i = 0; *(str + i) != '\0'; i++)
        if (*(str + i) == ch)
            return (char*)(str + i);

    return NULL;
}


char* strrchr(const char* str, int ch)
{
    const char* h = str;

    while(*(str++) != '\0');
    while(str != h)
        if(*str == ch)
            return (char*)str;
        else
            str--;
    if(*str == ch && str == h)
        return (char*)h;

    return NULL;
}


char* strcpy(char* strDest, const char* strSrc)
{
    if (strDest == strSrc)
        return strDest;

    char* tmpStr = strDest;

    memset(strDest, '\0', strlen(strDest));
    for(unsigned int i = 0; *(strSrc + i) != '\0'; i++)
        *(strDest + i) = *(strSrc + i);

    return tmpStr;
}


char* strncpy(char* strDest, const char* strSrc, size_t n)
{
    char* tmpStr = strDest;

    memset(strDest, '\0', strlen(strDest));
    for(unsigned int i = 0; n != 0; n--, i++)
        *(tmpStr + i) = *(strSrc + i);
    
    return strDest;
}


size_t strlen(const char* strSrc)
{
    unsigned int count = 0;

    for(; *(strSrc + count) != '\0'; count++)
        ;
    return count;
}


size_t strspn(const char* s, const char* strCharSet)
{
    const char* p = s;
    const char* q = strCharSet;
    unsigned int count = 0;

    for(; *p != '\0'; p++)
    {
        for(q = strCharSet; *q != '\0'; q++)
            if(*q == *p)
            {
                count++;
                break;
            }

        if(*q == '\0')
            return count;
    }

    return count;
}


int strcmp(const char* str1, const char* str2)
{
    const char* s1 = str1;
    const char* s2 = str2;

    while (*s1 == *s2) {
        if (*s1 == '\0' || *s2 == '\0')
            return 0;
        s1++, s2++;
    }

    if ((*s1 - *s2) > 0)
        return 1;
    else
        return -1;
}


char* strstr(const char *haystack, const char *needle)
{
    const char* p1 = NULL;
    char* retp = NULL;
    unsigned int i = 0;
    
    for(p1 = needle; *haystack != '\0'; haystack++)
    {
        if(needle != p1)
            needle = p1;

        i = 0;
        while(*needle != '\0')
        {
            if(*needle != *(haystack+i))
                break;
            needle++, i++;
        }
        retp = (char*)haystack;
        if(*needle == '\0' && retp != NULL)
            break;
    }

    return retp;
}
