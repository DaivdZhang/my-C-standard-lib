#ifndef MATRIX_H_
#define MATRIX_H_

struct _matrix{
    double** array;
    unsigned int shape[2];
};

typedef struct _matrix Matrix;

Matrix zeros(unsigned int, unsigned int);
Matrix eye(unsigned int);
Matrix random(unsigned int, unsigned int);
void mprint(Matrix);

Matrix madd(Matrix, Matrix);
Matrix msub(Matrix, Matrix);
Matrix mmul(Matrix, Matrix);
Matrix nmul(Matrix, double);

Matrix transpose(Matrix);

#endif
