#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "matrix.h"
#include "utility.h"

Matrix* mat_pool[POOL_SIZE] = {NULL};

Matrix _transform(Matrix, int, int*);
Matrix get_matrix();


Matrix get_matrix()
{
    for(unsigned int i = 0; i < POOL_SIZE; i++)
        if(mat_pool[i] != NULL)
        {
            Matrix* p = mat_pool[i];
            mat_pool[i] = NULL;
            return *p;
        }
    Matrix* p = (Matrix*)calloc(sizeof(Matrix), 1);
    return *p;
}


Matrix* return_matrix(Matrix* pmat)
{
    for(unsigned int i = 0; i < POOL_SIZE; i++)
        if(mat_pool[i] == NULL)
        {
            mdestroy(pmat);
            mat_pool[i] = pmat;
            return pmat;
        }
    mdestroy(pmat);
    free(pmat);
    return NULL;
}

int mdestroy(Matrix* pmat)
{
    pmat = clear(pmat);
    free(pmat->array[0]);
    free(pmat->array);
    return 0;
}


Matrix* initialize()
{
    Matrix mat;
    Matrix* pmat = &mat;
    mat = get_matrix();
    if(pmat == NULL)
    {
        printf("failed to initialize a matrix\n");
        exit(-1);
    }
    else
    {
        pmat->shape[0] = 0;
        pmat->shape[1] = 0;
    }
    return pmat;
}


Matrix zeros(unsigned int row, unsigned int col)
{
    Matrix mat;
    mat = *initialize();

    mat.array = (double**)calloc(sizeof(double*), row);
    double* tmp = (double*)calloc(sizeof(double), row*col);
    if(mat.array == NULL || tmp == NULL)
    {
        printf("failed to allocate memory\n");
        exit(-1);
    }
    for(unsigned int i = 0; i < row; i++)
        mat.array[i] = tmp + i*col;
    mat.shape[0] = row;
    mat.shape[1] = col;
    return mat;
}


Matrix eye(unsigned int n)
{   
    Matrix mat = zeros(n, n);

    for(unsigned int i = 0; i < n; i++)
        mat.array[i][i] = 1;
    return mat;
}


Matrix random(unsigned int row, unsigned int col)
{
    Matrix mat = zeros(row, col);

    srand(time(NULL));
    for(unsigned int i = 0; i < mat.shape[0]; i++)
        for(unsigned int j = 0; j < mat.shape[1]; j++)
            mat.array[i][j] = (double)rand()/RAND_MAX;
    return mat;
}


Matrix from_array(double* arr, unsigned int row, unsigned int col)
{
    Matrix mat = zeros(row, col);

    for(unsigned int i = 0; i < row*col; i++)
        mat.array[i/col][i%col] = *(arr + i);
    return mat;
}


Matrix* clear(Matrix* pmat)
{
    size_t size = sizeof(double);
    for(unsigned int i = 0; i < pmat->shape[0]; i++)
        memset(pmat->array[i], 0.0, pmat->shape[1]*size);
    return pmat;
}


Matrix fill(Matrix* pmat, double value)
{
    for(unsigned int i = 0; i < pmat->shape[0]; i++)
        for(unsigned int j = 0; j < pmat->shape[1]; j++)
            pmat->array[i][j] = value;
    return *pmat;
}


double* flat(Matrix mat)
{
    double* ret = NULL;
    ret = (double*)calloc(sizeof(double), mat.shape[0]*mat.shape[1]);
    if(ret == NULL)
        exit(-1);

    for(unsigned int i = 0; i < mat.shape[0]*mat.shape[1]; i++)
        ret[i] = mat.array[i/mat.shape[1]][i%mat.shape[1]];
    return ret;
}


Matrix reshape(Matrix* pmat, unsigned int row, unsigned int col)
{
    if(pmat->shape[0]*pmat->shape[1] != row*col)
    {
        printf("the scale of new mat is not equal to the orginal one\n");
        exit(-1);
    }

    double* arr = flat(*pmat);
    mdestroy(pmat);
    *pmat = from_array(arr, row, col);
    return *pmat;
}

int is_empty(Matrix mat)
{
    if(mat.shape[0] == 0 && mat.shape[1] == 0 && mat.array == NULL)
        return 1;
    else
        return 0;
}


int is_sparse(Matrix mat, double threshold)
{
    unsigned int count = 0;
    for(unsigned int i = 0; i < mat.shape[0]; i++)
        for(unsigned int j = 0; j < mat.shape[0]; j++)
            if(mat.array[i][j] == 0)
                count++;
    if(count*1.0/mat.shape[0]/mat.shape[1] >= threshold)
        return 1;
    else
        return 0;
}


int is_equal(Matrix* a, Matrix* b)
{
    if(a->shape[0] != b->shape[0] || a->shape[1] != b->shape[1])
        return 0;

    for(unsigned int i = 0; i < a->shape[0]; i++)
        for(unsigned int j = 0; j < a->shape[0]; j++)
            if(a->array[i][j] != b->array[i][j])
                return 0;
    return 1;
}


Matrix mcopy(Matrix new_mat, Matrix mat)
{
    for(unsigned int i = 0; i < mat.shape[0]; i++)
        memmove(new_mat.array[i], mat.array[i], sizeof(double)*mat.shape[1]);
    return new_mat;
}


void mprint(Matrix mat)
{   
    printf("[");
    for(unsigned int i = 0; i < mat.shape[0]; i++)
    {
        if(i != 0)
            printf(" [");
        else
            printf("[");
        for(unsigned int j = 0; j < mat.shape[1]; j++)
        {
            printf("%lf ", mat.array[i][j]);
            if(j + 1 == mat.shape[1] && (i + 1) != mat.shape[0])
                printf("\b]\n");
            if(j + 1 == mat.shape[1] && (i + 1) == mat.shape[0])
                printf("\b]]");
        }
    }
    printf("\n");
}


Matrix madd(Matrix a, Matrix b)
{
    if(a.shape[0] != b.shape[0] || a.shape[1] != b.shape[1])
    {
        printf("cannot add two given matrixes\n");
        exit(-1);
    }

    Matrix c = zeros(a.shape[0], b.shape[1]);
    for(unsigned int i = 0; i < a.shape[0]; i++)
        for(unsigned int j = 0; j < a.shape[1]; j++)
            c.array[i][j] = a.array[i][j] + b.array[i][j];
    return c;
}


Matrix msub(Matrix a, Matrix b)
{
    if(a.shape[0] != b.shape[0] || a.shape[1] != b.shape[1])
    {
        printf("cannot sub two given matrixes\n");
        exit(-1);
    }

    Matrix c = zeros(a.shape[0], b.shape[1]);
    for(unsigned int i = 0; i < a.shape[0]; i++)
        for(unsigned int j = 0; j < a.shape[1]; j++)
            c.array[i][j] = a.array[i][j] - b.array[i][j];
    return c;
}

double _mul(double* a, double* b, unsigned int length)
{
    double ret = 0;

    for(unsigned int i = 0; i < length; i++)
        ret += a[i]*b[i];
    return ret;
}

Matrix mmul(Matrix a, Matrix b)
{
    if(a.shape[1] != b.shape[0])
    {
        printf("cannot mul two given matrixes\n");
        exit(-1);
    }

    Matrix c = zeros(a.shape[0], b.shape[1]);
    Matrix _b = transpose(b);
    
    for(unsigned int i = 0; i < a.shape[0]; i++)
        for(unsigned int j = 0; j < _b.shape[0]; j++)
            c.array[i][j] = _mul(a.array[i], _b.array[j], a.shape[1]);
    return c;
}


Matrix nmul(Matrix mat, double k)
{
    Matrix ret = zeros(mat.shape[0], mat.shape[1]);
    for(unsigned int i = 0; i < mat.shape[0]; i++)
        for(unsigned int j = 0; j < mat.shape[1]; j++)
            ret.array[i][j] = mat.array[i][j]*k;
    return ret;
}


Matrix pmul(Matrix a, Matrix b)
{
    if(a.shape[0] != b.shape[0] || a.shape[1] != b.shape[1])
    {
        printf("cannot pmul two given matrixes\n");
        exit(-1);
    }

    Matrix c = zeros(a.shape[0], b.shape[1]);
    for(unsigned int i = 0; i < a.shape[0]; i++)
        for(unsigned int j = 0; j < a.shape[1]; j++)
            c.array[i][j] = a.array[i][j]*b.array[i][j];
    return c;
}


Matrix transpose(Matrix mat)
{
    Matrix ret = zeros(mat.shape[1], mat.shape[0]);

    for(unsigned int j = 0; j < mat.shape[1]; j++)
        for(unsigned int i = 0; i < mat.shape[0]; i++)
            ret.array[j][i] = mat.array[i][j];
    return ret;
}


Matrix _transform(Matrix mat, int identity, int* flag)
{    
    Matrix _mat = zeros(mat.shape[0], mat.shape[1]);
    mcopy(_mat, mat);
    double k = 0;
    short int count = 1;

    for(unsigned int i = 0; i < _mat.shape[0]; i++)
    {
        if(_mat.array[i][i] == 0)
        {
            for(unsigned int _ = i + 1; _ < _mat.shape[0]; _++)
                if(_mat.array[_][i] != 0)
                {
                    swap(_mat.array[_], _mat.array[i], _mat.shape[1]);
                    count *= -1;
                }
        }
        for(unsigned int _i = i + 1; _i < _mat.shape[0]; _i++)
        {
            if(_mat.array[i][i] == 0)
                break;
            k = _mat.array[_i][i]/_mat.array[i][i];
            if(k == 0)
                continue;
            _mat.array[_i] = array_sub(_mat.array[_i], _mat.array[i], _mat.shape[1], k);
        }
    }
    if(flag != NULL)
        *flag = count;

    if(identity == 0)
        return _mat;
    else
    {
        unsigned int j = _mat.shape[0] - 1;
        unsigned int i = j - 1;
        while(1)
        {   
            while(1)
            {
                if(_mat.array[j][j] == 0)
                {   
                    for(long long _ = i - 1; _ >= 0; _--)
                        if(_mat.array[_][i] != 0)
                            swap(_mat.array[_], _mat.array[i], _mat.shape[1]);
                }
                if(_mat.array[j][j] == 0)
                    break;
                k = _mat.array[i][j]/_mat.array[j][j];
                if(k == 0)
                    continue;
                _mat.array[i] = array_sub(_mat.array[i], _mat.array[j], _mat.shape[1], k);
                if(i == 0)
                    break;
                i--;
            }
            j--;
            if(j == 0)
                break;
            i = j - 1;
        }
        for(unsigned int i = 0; i < mat.shape[0]; i++)
            if(_mat.array[i][i] != 1)
            {
                double tmp[_mat.shape[1]];
                for(unsigned int _ = 0; _ < _mat.shape[1]; _++)
                    tmp[_] = _mat.array[i][i];
                _mat.array[i] = array_div(_mat.array[i], tmp, _mat.shape[1], 1);
            }
        return _mat;
    }
}


double det(Matrix mat)
{
    int* flag = NULL;
    if((flag = (int*)calloc(sizeof(int), 1)) == NULL)
    {
        printf("failed to allocate memory\n");
        exit(-1);
    }

    Matrix _mat = zeros(mat.shape[0], mat.shape[1]);
    double value = 1;
    mcopy(_mat, _transform(mat, 0, flag));

    for(unsigned int i = 0; i < mat.shape[0]; i++)
        value *= _mat.array[i][i];
        
    mdestroy(&_mat);
    return value*(*flag);
}


Matrix inv(Matrix mat)
{
    if(mat.shape[0] != mat.shape[1])
    {
        printf("square matrix expected\n");
        exit(-1);
    }

    Matrix _mat = zeros(mat.shape[0], 2*mat.shape[1]);
    mcopy(_mat, mat);
    for(unsigned int i = 0; i < _mat.shape[0]; i++)
        for(unsigned int j = mat.shape[0]; j < _mat.shape[1]; j++)
            if(i == j%mat.shape[0])
                _mat.array[i][j] = 1;

    _mat = _transform(_mat, 1, NULL);
    Matrix tmp = zeros(_mat.shape[0], _mat.shape[0]);
    for(unsigned int i = 0; i < tmp.shape[0]; i++)
        for(unsigned int j = 0; j < tmp.shape[1]; j++)
            tmp.array[i][j] = _mat.array[i][j+tmp.shape[1]];

    mdestroy(&_mat);
    return tmp;
}


double trace(Matrix mat)
{
    if(mat.shape[0] != mat.shape[1])
    {
        printf("square matrix expected\n");
        exit(-1);
    }

    double value = 0;
    for(unsigned int i = 0; i < mat.shape[0]; i++)
        value += mat.array[i][i];
    return value;
}
