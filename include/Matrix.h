/*Matrix math class Header*/
#ifndef MATRIX
#define MATRIX

#include <stddef.h>
#include <stdbool.h>

typedef struct Matrix
{
    double** data;
    size_t rows, cols;
} Matrix;

// Init
void initMatrix(Matrix* mat, size_t rows, size_t cols);
bool _checkInitMatrix(Matrix* mat);
bool _checkMatrixFileFormat(char* filePath);
void freeMatrix(Matrix* mat);

// IO
void printMatrix(const Matrix* mat);
void printMatrixtoFile(const Matrix* mat, char* filePath);
void readMatrixFromFile(Matrix* mat, char* filePath);

// Math
double calcDeterminant(const Matrix* mat);
//double calcNorm(const Matrix* mat, int p); // TODO: https://mathworld.wolfram.com/MatrixNorm.html
//double calcEigenvalues(const Matrix* mat); // TODO:
#endif /* Matrix */