#include "Vector.h"
#include "Matrix.h"
#include "LinSys.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

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

void solveLinSys(LinearSystem *linsys, Vector *solution)
{
    Vector m; // TODO: what is this?
    if (solution->data == NULL)
    {
        fprintf(stderr, "Solution Vector is not initialized!\n");
        exit(EXIT_FAILURE);
    }
    initVector(&m, linsys->size);

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
            for (size_t j = k; j < linsys->size; j++)
            {
                linsys->mat->data[i][j] -= linsys->mat->data[k][j] * m.data[i];
            }
            linsys->vec->data[i] -= linsys->vec->data[k] * m.data[i];
        }
    }

    // back substitution
    for (size_t i = linsys->size - 1; i > -1; i--)
    {
        solution->data[i] = linsys->vec->data[i];
        for (size_t j = i + 1; j < linsys->size; j++)
        {
            solution->data[i] -= linsys->mat->data[i][j] * solution->data[j];
        }
        solution->data[i] /= linsys->mat->data[i][i];
    }
}
