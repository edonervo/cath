#include "Matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"

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

bool _checkInitMatrix(Matrix* mat)
{
    for (size_t i=0; i<mat->rows; i++)
    {
        if (mat->data[i] == NULL)
        {
            return false;
        }
    }
    if (mat->data == NULL)
    {
        return false;
    }
    return true;
}

void printMatrix(const Matrix *mat)
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

void printMatrixtoFile(const Matrix* mat, char* filePath)
{
    if (!_checkInitMatrix(mat))
    {
        fprintf(stderr, "Matrix is not initialized! Exiting...");
        exit(EXIT_FAILURE);
    }
    FILE* fp = fopen(filePath, "w");
    if (fp == NULL) 
    {
        perror("Error: ");
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < mat->rows; i++)
    {
        for (size_t j = 0; j < mat->cols; j++)
        {
            if (j < mat->cols - 1)
            {
                fprintf(fp, "%f ", mat->data[i][j]);
            }
            else
            {
                fprintf(fp, "%f\n", mat->data[i][j]);
            }
        }
    }
    fclose(fp);
}

bool _checkMatrixFileFormat(char* filePath, int* rows, int* cols)
{
    FILE* fp = fopen(filePath, "r");
    if (fp == NULL)
    {
        perror("Error Opening File: ");
        return false;
    }

    *rows = 0;
    *cols = 0;

    // Read the file until EOF is reached
    int c;
    bool previousWasSpace = false;
    bool previousWasDouble = false;
    size_t maxCols = 0; // Keep track the matrix is uniform
    while ((c = fgetc(fp)) != EOF)      
    {
        if (c == '\n')
        {
            // Previous char must be part of a double and not a space
            if (!previousWasDouble || previousWasSpace)
            {
                fclose(fp);
                return false;
            }
            // check columns consistency
            if (*rows == 0)
            {
                maxCols = *cols;
            } else if ((*rows>0) && (*cols != maxCols))
            {
                fclose(fp);
                return false;
            }
            previousWasDouble = false;
            previousWasSpace = false;
            *rows = *rows + 1;
            *cols = 0;
        } else if (c == ' ')
        {
            if (previousWasSpace || !previousWasDouble)
            {
                fclose(fp);
                return false;
            }
            previousWasSpace = true;
            *cols = *cols+1;
        } else if ((c >= '0' && c <= '9') || c == '.' || c == '-')
        {
            previousWasDouble = true;
            previousWasSpace = false;
        } else {
            // Non-double char is found
            fclose(fp);
            return false;
        }
    }
    *cols = maxCols+1;
    return true;
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

void readMatrixFromFile(Matrix* mat, char* filePath)
{
    int rows = 0;
    int cols = 0;
    if (!_checkMatrixFileFormat(filePath, &rows, &cols))
    {
        fprintf(stderr, "File %s is not in correct format!", filePath);
        exit(EXIT_FAILURE);
    }

    FILE* fp = fopen(filePath, "r");
    if (fp == NULL) {
        fprintf(stderr, "Failed to open file %s! Exiting...\n", filePath);
        exit(EXIT_FAILURE);
    }

    // Assign file to Matrix
    initMatrix(mat, rows, cols);
    // double num;
    for (size_t i=0; i<mat->rows; i++)
    {
        for (size_t j=0; j<mat->cols; j++)
        {
            fscanf(fp, "%lf", &mat->data[i][j]);
        }
    }    
    fclose(fp);
}

void randomMatrix(Matrix* mat, int rows, int cols, double min, double max)
{
    initMatrix(mat, rows, cols);
    for (size_t i=0; i<rows; i++)
    {
        for (size_t j=0; j<cols; j++)
        {
            mat->data[i][j] = randomDouble(min, max);
        }
    }
}

double calcDeterminant(const Matrix *mat)
{
    // Matrix determinant is only defined for square matrices
    if (mat->rows != mat->cols)
    {
        fprintf(stderr, "Matrix is not square");
    }

    double determinant = 0.0;

    if (mat->rows == 1)
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
