#include <stdio.h>

#define M_PI 3.14159265358979323846
#define M_E 2.71828182845904523536

unsigned long long fac(unsigned int n);

double sin (double);
double cos (double);
double tan (double);
double asin (double);
double acos (double);
double atan (double);
double atan2(double, double);
double sinh(double);
double cosh(double);
double tanh(double);

double exp(double);
double sqrt(double);
double log(double);
double log10(double);
double _pow(double, unsigned int);
double pow(double, double);

double ceil (double);
double floor (double);

int abs(int x);
double fabs(double);

double frexp (double f, int *p);
double ldexp (double x, int p);

double modf (double, double*);
double fmod (double, double);

unsigned long long fac(unsigned int n)
{
    unsigned long long t = 1;

    while(n != 0)
    {
        t *= n;
        n--;
    }

    return t;
}


double sin(double x)
{
    double y = 0;

    x *= M_PI/180;
    for(unsigned int i = 0; i != 8; i++)
        y += pow(-1.0, i)/fac(2*i+1)*pow(x, 2*i+1);

    return y;
}


double cos(double x)
{
    double y = 0;

    x *= M_PI/180;
    for(unsigned int i = 0; i != 8; i++)
        y += _pow(-1.0, i)/fac(2*i)*_pow(x, 2*i);

    return y;
}


double tan(double x)
{
    if(x == 90)
        return 4294967296.0;
    else if(x==-90)
        return -4294967296.0;

    return sin(x)/cos(x);
}


double asin(double x)
{
    double y = 0;

    for(unsigned int i = 0; i != 8; i++)
        y += fac(2*i)/(_pow(4.0, i)*_pow(fac(i), 2)*(2*i+1))*_pow(x, 2*i+1);

    return y;
}


double acos(double x)
{
    double y;

    y = M_PI/2 - asin(x);
    return y;
}


double atan(double x)
{
    double y = 0;

    for(unsigned int i = 0; i != 8; i++)
        y += _pow(-1, i)/(2*i+1)*_pow(x, 2*i+1);

    return y;
}


double atan2(double y, double x)
{
    if(!x && y > 0)
        return M_PI/2;
    else if(!x && y > 0)
        return -M_PI/2;

    double z = atan(y/x);

    if(z < 0)
        return z + 2*M_PI;
    else
        return z;
}


double sinh(double x)
{
    double y = 0;

    y = (exp(x) - exp(-x))/2;
    return y;
}


double cosh(double x)
{
    double y = 0;

    y = (exp(x) + exp(-x))/2;
    return y;
}


double tanh(double x)
{
    return sinh(x)/cosh(x);
}


double exp(double x)
{
    double y = 0;

    for(unsigned int i = 0; i != 8; i++)
        y += _pow(x, i)/fac(i);

    return y;
}


double sqrt(double a)
{
    double cx = 1;
    double px = cx;
    double eps = 1e-8;

    while(1)
    {
        px = cx;
        cx -= cx/2 + a/2/cx;
        if(fabs(cx - px) < eps)
            break;
    }
    return cx;
}


double log(double x)
{
    double y = 0;
    double u = 0;

    u = (x-1)/(x+1);
    for(unsigned int i = 0; i != 16; i++)
        y += _pow(u, 2*i)/(2*i+1);

    return 2*u*y;
}


double log10(double x)
{
    double y = 0;

    y = log(x)/log(10);
    return y;
}


double _pow(double x, unsigned int y)
{
    double t = 1;

    for(; y != 0; y--)
        t *= x;

    return t;
}


double pow(double x, double y)
{
    double p = 0;

    p = y*log(x);
    return exp(p);
}


double ceil(double x)
{
    int y = (int)x;
    y++;
    return (double)y;
}


double floor(double x)
{
    return (double)(int)x;
}


int abs(int x)
{
    if(x > 0)
        return x;
    else if(x == 0)
        return 0;
    else
        return -x;
}


double fabs(double x)
{
    if(x > 0)
        return x;
    else if(x == 0)
        return 0;
    else
        return -x;
}


double frexp (double f, int* p)
{
    double b = ceil(log(f)/log(2));
    double ret = 0;

    ret = f/_pow(2, b);
    *p = (int)b;

    return ret;
}


double ldexp (double x, int p)
{
    return x*_pow(2, p);
}


double modf (double x, double* ipart)
{
    double y = 0;

    y = floor(x);
    *ipart = x - y;
    return y;
}


double fmod (double x, double y)
{
    double r = 0;
    double p = 0;

    r = x/y;
    modf(r, &p);
    return p*y;
}
