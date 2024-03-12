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
void freeMatrix(Matrix* mat);
size_t getNumRows(Matrix* mat);
size_t getNumCols(Matrix* mat);
double calcDeterminant(const Matrix* mat);

#endif /* Matrix */