#include "unity.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "Matrix.h"

// TODO: read from a test config file
double MATRIX_TOLERANCE = 1e-6;
int MATRIX_SQUARE_SIZE = 1000;
int MATRIX_ROWS = 500;
int MATRIX_COLS = 1000;
double MATRIX_MIN = 0.0;
double MATRIX_MAX = 1.0;

void test_matrix_init()
{
    Matrix mat;
    initMatrix(&mat, MATRIX_ROWS, MATRIX_COLS);

    TEST_ASSERT_NOT_NULL_MESSAGE(mat.data, "Matrix pointer is null");
    TEST_ASSERT_EQUAL_INT_MESSAGE(MATRIX_ROWS, mat.rows, "Rows of the Mateix does not correspond to input");
    TEST_ASSERT_EQUAL_INT_MESSAGE(MATRIX_COLS, mat.cols, "Columns of the Mateix does not correspond to input");

    for (size_t i = 0; i < MATRIX_ROWS; i++)
    {
        for(size_t j=0; j<MATRIX_COLS; j++)
        {
            TEST_ASSERT_DOUBLE_WITHIN_MESSAGE(
            MATRIX_TOLERANCE, 0.0,
            mat.data[i][j], "Matrix was not initialized correctly");
        }
        
    }
    freeMatrix(&mat);
}