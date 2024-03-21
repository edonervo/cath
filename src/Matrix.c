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

bool _checkMatrixFileFormat(char* filePath)
{
    FILE* fp = fopen(filePath, "r");
    if (fp == NULL)
    {
        perror("Error Opening File: ");
        return false;
    }

    // Variables to track format requirements
    bool rowsColsRead = false; // Ensures each row has the same size
    size_t rows = 0;
    size_t cols = 0;

    // Read the file until EOF is reached
    int c;
    bool previousWasSpace = false;
    bool previousWasDouble = false;
    size_t currentCols = 0;
    while ((c = fgetc(fp)) != EOF)      
    {
        if (c == '\n')
        {
            // Previous char must be part of a double
            if (!previousWasDouble || !rowsColsRead)
            {
                fclose(fp);
                return false;
            }
            rowsColsRead = true;
            rows++;
            if (cols == 0)
            {
                cols = currentCols;
            } else if (currentCols != cols)
            {
                fclose(fp);
                return false;
            }
            currentCols = 0;
            previousWasDouble = false;
            previousWasSpace = false;
        } else if (c == ' ')
        {
            if (previousWasSpace || !previousWasDouble || !rowsColsRead)
            {
                fclose(fp);
                return false;
            }
            previousWasSpace = true;
        } else if ((c >= '0' && c <= '9') || c == '.' || c == '-')
        {
            previousWasDouble = true;
            previousWasSpace = false;
            currentCols++;
        } else {
            // Non-double char is found
            fclose(fp);
            return false;
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

void readMatrixFromFile(Matrix* mat, char* filePath)
{
    if (_checkMatrixFileFormat(filePath))
    {
        fprintf(stderr, "File %s is not in correct format!", filePath);
        exit(EXIT_FAILURE);
    }

    FILE* fp = fopen(filePath, "r");
    if (fp == NULL) {
        fprintf(stderr, "Failed to open file %s! Exiting...\n", filePath);
        exit(EXIT_FAILURE);
    }

    // Determine Matrix size before init
    int cols = 0;
    int rows = 0;
    double num;
    while(true) 
    {
        if (fscanf(fp, "%lf", &num) != EOF)
        {
            if (fgetc(fp) == "\n") 
            {
                rows++;
            } else
            {
                cols++;
            }
        } else
        {
            // EOF reached
            break;
        }
    }

    // Assign file to Matrix
    fclose(fp);
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
