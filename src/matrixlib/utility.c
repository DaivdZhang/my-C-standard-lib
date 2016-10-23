#include "utility.h"
#include <stdio.h>
#include <stdlib.h>


void _swap(double* a, double* b)
{
    double tmp = 0;
    tmp = *a;
    *a = *b;
    *b = tmp;
}


void swap(double* arr1, double* arr2, unsigned int length)
{
    for(unsigned int i = 0; i <length; i++)
        _swap(&arr1[i], &arr2[i]);
}


double* array_sub(double* arr1, double* arr2, unsigned int length, double k)
{   
    double* ret = (double*)calloc(sizeof(double), length);
    if(ret == NULL)
        exit(202020);
    for(unsigned int i = 0; i < length; i++)
        ret[i] = arr1[i] - k*arr2[i];
    
    return ret;
}


double* array_div(double* arr1, double* arr2, unsigned int length, double k)
{   
    double* ret = (double*)calloc(sizeof(double), length);
    if(ret == NULL)
        exit(202020);
    for(unsigned int i = 0; i < length; i++)
        ret[i] = arr1[i]/arr2[i]*k;
    
    return ret;
}
