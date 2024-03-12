/*Matrix math class Header*/
#ifndef MATRIX
#define MATRIX

#include <stddef.h>

typedef struct Matrix
{
    double** data;
    size_t rows, cols;
} Matrix;

void initMatrix(Matrix* mat, size_t rows, size_t cols);
void printMatrix(Matrix* mat);

#endif /* Matrix */