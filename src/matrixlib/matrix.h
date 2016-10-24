#ifndef MATRIX_H_
#define MATRIX_H_

#define POOL_SIZE 8

struct _matrix{
    double** array;
    unsigned int shape[2];
};

typedef struct _matrix Matrix;


int mdestroy(Matrix*);
Matrix* return_matrix(Matrix*);

Matrix zeros(unsigned int, unsigned int);
Matrix eye(unsigned int);
Matrix random(unsigned int, unsigned int);
Matrix from_array(double*, unsigned int, unsigned int);
Matrix* clear(Matrix*);

double* flat(Matrix);
Matrix reshape(Matrix, unsigned int, unsigned int);
int is_empty(Matrix);
int is_sparse(Matrix, double);

void mprint(Matrix);

Matrix madd(Matrix, Matrix);
Matrix msub(Matrix, Matrix);
Matrix mmul(Matrix, Matrix);
Matrix nmul(Matrix, double);
Matrix pmul(Matrix, Matrix);

Matrix transpose(Matrix);
double det(Matrix);
Matrix inv(Matrix);
double trace(Matrix);

#endif
