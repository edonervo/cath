#include "Matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void initMatrix(Matrix *mat, size_t rows, size_t cols)
{
    if (rows <= 0)
    {
        fprintf(stderr, "Error: rows size must be > 0");
        exit(EXIT_FAILURE);
    }

    if (cols <= 0)
    {
        fprintf(stderr, "Error: cols size must be > 0");
        exit(EXIT_FAILURE);
    }

    mat->data = (double **)malloc(rows * sizeof(double *));
    if (mat->data == NULL)
    {
        perror("Memory Allocation Failed");
        exit(EXIT_FAILURE);
    }

    mat->rows = rows;
    mat->cols = cols;

    for (size_t i = 0; i < rows; i++)
    {
        mat->data[i] = (double *)malloc(cols * sizeof(double));
        if (mat->data[i] == NULL)
        {
            perror("Memory allocation Failed");
            exit(EXIT_FAILURE);
        }

        // Init to 0.0
        for (size_t j = 0; j < cols; j++)
        {
            mat->data[i][j] = 0.0;
        }
    }
}

void printMatrix(Matrix *mat)
{
    if (mat->data == NULL)
    {
        fprintf(stderr, "Matrix has not been initialized");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < mat->rows; i++)
    {
        for (size_t j = 0; j < mat->cols; j++)
        {
            if (j < mat->cols - 1)
            {
                printf("%f ", mat->data[i][j]);
            }
            else
            {
                printf("%f\n", mat->data[i][j]);
            }
        }
    }
}

void freeMatrix(Matrix *mat)
{
    for (size_t i = 0; i < mat->rows; i++)
    {
        free(mat->data[i]);
    }
    free(mat->data);
    mat->data = NULL;
    mat->rows = 0;
    mat->cols = 0;
}

size_t getNumRows(const Matrix *mat)
{
    return mat->rows;
}

size_t getNumCols(const Matrix *mat)
{
    return mat->cols;
}

double calcDeterminant(const Matrix *mat)
{
    // Matrix determinant is only defined for square matrices
    if (getNumCols(mat) != getNumRows(mat))
    {
        fprintf(stderr, "Matrix is not square");
    }

    double determinant = 0.0;

    if (getNumRows(mat) == 1)
    {
        determinant = mat->data[0][0];
    }
    else
    {
        // More than one entry of matrix
        for (size_t i_outer = 0; i_outer < mat->rows; i_outer++)
        {
            Matrix sub_mat;
            initMatrix(&sub_mat, mat->rows - 1, mat->cols - 1);
            for (size_t i = 0; i < mat->rows - 1; i++)
            {
                for (size_t j = 0; j < i_outer; j++)
                {
                    sub_mat.data[i][j] = mat->data[i + 1][j];
                }
                for (size_t j = i_outer; j < mat->rows - 1; j++)
                {
                    sub_mat.data[i][j] = mat->data[i + 1][j + 1];
                }
            }
            double sub_matrix_determinant = calcDeterminant(&sub_mat);
            determinant += pow(-1.0, i_outer) * mat->data[0][i_outer] * sub_matrix_determinant;
        }
    }

    return determinant;
}
