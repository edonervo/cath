#include "Vector.h"
#include "Matrix.h"
#include "LinSys.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string.h>

void initLinSys(LinearSystem *linsys, Matrix *mat, Vector *vec)
{
    // Check that Matrix and Vector are initialized
    if (vec->data == NULL)
    {
        fprintf(stderr, "Vector is not init!\n");
        exit(EXIT_FAILURE);
    }
    if (mat->data == NULL)
    {
        fprintf(stderr, "Matrix is not init!\n");
        exit(EXIT_FAILURE);
    }

    // Check the compatible size
    if (mat->rows != vec->size)
    {
        fprintf(stderr, "Incompatible size: Matrix rows must match Vector size\n");
        exit(EXIT_FAILURE);
    }

    linsys->mat = mat;
    linsys->vec = vec;
    linsys->size = vec->size;
}

void freeLinSys(LinearSystem *linsys)
{
    if (linsys->mat == NULL || linsys->vec == NULL)
    {
        fprintf(stderr, "LinearSystem is not initialized!\n");
        exit(EXIT_FAILURE);
    }

    freeVector(linsys->vec);
    freeMatrix(linsys->mat);

    linsys->mat = NULL;
    linsys->vec = NULL;
}

void _GaussEliminationMethod(LinearSystem *linsys, Vector *solution)
{
        Vector m; // TODO: what is this?
    if (solution->data == NULL)
    {
        fprintf(stderr, "Solution Vector is not initialized!\n");
        exit(EXIT_FAILURE);
    }
    initVector(&m, linsys->size);

    // Init solution vector
    initVector(solution, linsys->size);

    // Forward sweep of Gaussian elimination
    for (size_t k = 0; k < linsys->size - 1; k++)
    {
        // Decide if pivoting is necessary
        double max = 0.0;
        int row = -1;
        for (size_t i = k; i < linsys->size; i++)
        {
            if (fabs(linsys->mat->data[i][k]) > max)
            {
                row = i;
                max = fabs(linsys->mat->data[i][k]);
            }
        }
        assert(row >= 0);

        // Pivot if necessary
        if (row != k)
        {
            // swap matrix rows k+1 with row+1
            for (size_t i = 0; i < linsys->size; i++)
            {
                double temp = linsys->mat->data[k][i];
                linsys->mat->data[k][i] = linsys->mat->data[row][i];
                linsys->mat->data[row][i] = temp;
            }
            // swap vector entries k+1 with row+1
            double temp = linsys->vec->data[k];
            linsys->vec->data[k] = linsys->vec->data[row];
            linsys->vec->data[row] = temp;
        }

        // create zeros in lower part of column k
        for (size_t i = k + 1; i < linsys->size; i++)
        {
            m.data[i] = linsys->mat->data[i][k] / linsys->mat->data[k][k];
            for (size_t j = k+1; j < linsys->size; j++)
            {
                linsys->mat->data[i][j] -= linsys->mat->data[k][j] * m.data[i];
            }
            linsys->vec->data[i] -= linsys->vec->data[k] * m.data[i];
        }
    }

    // back substitution
    for (int i = linsys->size - 1; i > -1; i--)
    {
        solution->data[i] = linsys->vec->data[i];
        for (size_t j = i + 1; j < linsys->size; j++)
        {
            solution->data[i] -= linsys->mat->data[i][j] * solution->data[j];
        }
        solution->data[i] /= linsys->mat->data[i][i];
    }
}

void _thomasAlgorithm(LinearSystem *linsys, Vector *solution, bool verbose)
{
    // Assume Tridiagonal Matrix
    // Diagonals
    Vector low_diag; // lower diag 
    Vector main_diag; // main diag
    Vector upper_diag; // upper diag
    initVector(&low_diag, linsys->size);
    initVector(&main_diag, linsys->size);
    initVector(&upper_diag, linsys->size);

    // Aux vectors
    Vector alpha;
    Vector beta;
    Vector y;
    initVector(&alpha, linsys->size);
    initVector(&beta, linsys->size);
    initVector(&y, linsys->size);

    // Solution
    initVector(solution, linsys->size);

    // Extract Vectors from matrix
    for (size_t i=0; i<linsys->size; i++)
    {
        if (i == 0)
        {
            // first row
            main_diag.data[i] = linsys->mat->data[i][i];
            upper_diag.data[i] = linsys->mat->data[i][i+1];
        }
        else if ((i > 0) && (i < linsys->size-1))
        {
            main_diag.data[i] = linsys->mat->data[i][i];
            upper_diag.data[i] = linsys->mat->data[i][i+1];
            low_diag.data[i] = linsys->mat->data[i][i-1];
        } else
        {
            main_diag.data[i] = linsys->mat->data[i][i];
            low_diag.data[i] = linsys->mat->data[i][i-1];
        }
    }

    if (verbose)
    {
        // print debug info
        printf("Matrix: \n");
        printMatrix(linsys->mat);
        printf("-------------------------\n\n");

        printf("Known Vector: \n");
        printVector(linsys->vec);
        printf("-------------------------\n\n");

        printf("Low Diag: \n");
        printVector(&low_diag);
        printf("-------------------------\n\n");

        printf("Main diag: \n");
        printVector(&main_diag);
        printf("-------------------------\n\n");

        printf("Upper Diag: \n");
        printVector(&upper_diag);
        printf("-------------------------\n\n");

    }

    // Solve
    alpha.data[0] = main_diag.data[0];
    y.data[0] = linsys->vec->data[0];

    for (size_t i = 1; i<linsys->size; i++)
    {
        // alpha.data[i] = alpha.data[i-1] - ((low_diag.data[i] * upper_diag.data[i-1]) / alpha.data[i-1]);
        beta.data[i] = low_diag.data[i] / alpha.data[i-1];
        alpha.data[i] = main_diag.data[i] - beta.data[i]*upper_diag.data[i-1];
        y.data[i] = linsys->vec->data[i] - beta.data[i]*y.data[i-1];
    }

    solution->data[linsys->size-1] = y.data[linsys->size-1] / alpha.data[linsys->size-1];
    for (size_t i=linsys->size - 2; i=0; i--)
    {
        solution->data[i] = (y.data[i] - upper_diag.data[i]*solution->data[i+1]) / alpha.data[i];
    }

    freeVector(&low_diag);
    freeVector(&main_diag);
    freeVector(&upper_diag);
    freeVector(&alpha);
    freeVector(&beta);
    freeVector(&y);
}

void solveLinSys(LinearSystem *linsys, Vector *solution, char* method, bool verbose)
{
    // TODO: SolveLinSys should be able to identify best alg for the matrix
    if (strcmp(method, "gauss") == 0) 
    {
        _GaussEliminationMethod(linsys, solution);
    } 
    else if (strcmp(method, "thomas") == 0)
    {
        _thomasAlgorithm(linsys, solution, verbose);
    }
    else
    {
        fprintf(stderr, "Method not available, exiting...\n");
        exit(EXIT_FAILURE);
    }
}
