#ifndef UTILITY_H_
#define UTILITY_H_

struct _ctuple{
    void** elements;
    unsigned int tsize;
};

typedef struct _ctuple CTuple;

void swap(double*, double*, unsigned int);
double* array_sub(double*, double*, unsigned int, double);
double* array_div(double*, double*, unsigned int, double);

#endif
