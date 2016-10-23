#ifndef MATRIX_H_
#define MATRIX_H_

struct _matrix{
    double** array;
    unsigned int shape[2];
};

typedef struct _matrix Matrix;

int mdestroy(Matrix*);
Matrix zeros(unsigned int, unsigned int);
Matrix eye(unsigned int);
Matrix random(unsigned int, unsigned int);
Matrix from_array(double*, unsigned int, unsigned int);

void mprint(Matrix);

Matrix madd(Matrix, Matrix);
Matrix msub(Matrix, Matrix);
Matrix mmul(Matrix, Matrix);
Matrix nmul(Matrix, double);
Matrix pmul(Matrix, Matrix);

Matrix transpose(Matrix);
Matrix _transform(Matrix, int*);
double det(Matrix);

#endif
