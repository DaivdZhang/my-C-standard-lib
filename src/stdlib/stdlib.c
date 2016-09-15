#include <stdio.h>
#include <string.h>
#include <math.h>


double _atof(const char*);
int _atoi(char*);
long _atol(char*);
long long _atoll(char*);

int _rand(void);
void _srand(unsigned int);


static int seed = 0;

double _atof(const char* s)
{
    const char* p = s;
    const char* cset = ".";
    double ret = 0;
    unsigned int length = 0;
    double tmp = 0;
    int pos = 1;

    if(*s == '-')
        pos = -1;
    for(length = strcspn(s, cset); *p != '.'; p++, length--)
        {   
            if(*p >= '0' && *p <= '9')
            {
                tmp = (double)((int)(*p) - 48);
                ret += tmp*pow(10.0, length-1);
            }
        }
    for(unsigned int i = 0; *p != '\0'; p++, i++)
        {   
            if(*p >= '0' && *p <= '9')
            {
                tmp = (double)((int)(*p) - 48);
                ret += tmp*pow(0.1, i);
            }
        }

    return ret*pos;
}


int _atoi(char* s)
{
    char* p = s;
    int ret = 0;
    unsigned int length = 0;
    int tmp = 0;
    int pos = 1;

    if(*s == '-')
        pos = -1;
    for(length = strlen(s); *p != '\0'; p++, length--)
    {   
        if(*p >= '0' && *p <= '9')
        {
            tmp = *p - 48;
            ret += tmp*(int)pow(10.0, length-1);
        }
    }

    return ret*pos;
}


long _atol(char* s)
{
    if(sizeof(long) == sizeof(int))
        return _atoi(s);

    char* p = s;
    long ret = 0;
    unsigned long length = 0;
    long tmp = 0;
    int pos = 1;

    if(*s == '-')
        pos = -1;
    for(length = strlen(s); *p != '\0'; p++, length--)
    {   
        if(*p >= '0' && *p <= '9')
        {
            tmp = *p - 48;
            ret += tmp*(long)pow(10.0, length-1);
        }
    }

    return ret*pos;
}


long long _atoll(char* s)
{
    char* p = s;
    long long ret = 0;
    unsigned long length = 0;
    long long tmp = 0;
    int pos = 1;

    if(*s == '-')
        pos = -1;
    for(length = strlen(s); *p != '\0'; p++, length--)
    {   
        if(*p >= '0' && *p <= '9')
        {
            tmp = *p - 48;
            ret += tmp*(long long)pow(10.0, length-1);
        }
    }

    return ret*pos;
}


int _rand()
{
    int r_num = seed;

    r_num = (r_num*32763 + 2)%4869;
    seed = r_num;
    return r_num;
}


void _srand(unsigned int s)
{
    if(s != 0)
        seed = s;
}
