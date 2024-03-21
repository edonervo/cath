#include "unity.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "Matrix.h"

// TODO: read from a test config file
double MATRIX_TOLERANCE = 1e-6;
int MATRIX_SQUARE_SIZE = 4;
int MATRIX_ROWS = 4;
int MATRIX_COLS = 4;
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
        for (size_t j = 0; j < MATRIX_COLS; j++)
        {
            TEST_ASSERT_DOUBLE_WITHIN_MESSAGE(
                MATRIX_TOLERANCE, 0.0,
                mat.data[i][j], "Matrix was not initialized correctly");
        }
    }
    freeMatrix(&mat);
}

void test_matrix_free()
{
    Matrix mat;
    initMatrix(&mat, MATRIX_ROWS, MATRIX_COLS);
    freeMatrix(&mat);
    TEST_ASSERT_NULL_MESSAGE(mat.data, "Matrix pointer is not null");
    TEST_ASSERT_EQUAL_INT(0, mat.rows);
    TEST_ASSERT_EQUAL_INT(0, mat.cols);
}

void test_matrix_files()
{
    /*Case 1 - Correct output and input file*/
    Matrix mat;
    Matrix newMat;
    char *filePath = "/home/edo/dev/cath/tmp/output.txt";

    randomMatrix(&mat, MATRIX_ROWS, MATRIX_COLS, MATRIX_MIN, MATRIX_MAX);
    printMatrixtoFile(&mat, filePath);
    // printMatrix(&mat);
    readMatrixFromFile(&newMat, filePath);
    // printMatrix(&newMat);
    // Matrix must be the same
    TEST_ASSERT_EQUAL_INT_MESSAGE(mat.rows, newMat.rows, "Matrix rows does not correspond to input");
    TEST_ASSERT_EQUAL_INT_MESSAGE(mat.cols, newMat.cols, "Matrix cols does not correspond to input");
    for (size_t i = 0; i < mat.rows; i++)
    {
        for (size_t j = 0; j < mat.rows; j++)
        {
            TEST_ASSERT_DOUBLE_WITHIN_MESSAGE(
                MATRIX_TOLERANCE, mat.data[i][j],
                newMat.data[i][j], "Vector was not initialized correctly");
        }
    }

    /*Case 2 - Matrix in the file is wrong format (no doubles)*/
    int rows = 0;
    int cols = 0;
    TEST_ASSERT_FALSE_MESSAGE(
        _checkMatrixFileFormat("/home/edo/dev/cath/test_files/matrix/wrong_format_matrix_1.txt", &rows, &cols),
        "Correct format file is recognized with correct format");

    /*Case 3 - Matrix in the file is wrong format (inconsistencies)*/
    TEST_ASSERT_FALSE_MESSAGE(
        _checkMatrixFileFormat("/home/edo/dev/cath/test_files/matrix/wrong_format_matrix_2.txt", &rows, &cols),
        "Correct format file is recognized with correct format");
    freeMatrix(&mat);
    freeMatrix(&newMat);
}

void test_matrix_algebra()
{
    // Determinant
    Matrix mat_2x2;
    Matrix mat_3x3;
    Matrix mat_4x4;
    Matrix squareNullMatrix;

    /*Case 1 - simple 2x2 matrix*/
    double expectedDet = -2.0;
    double actualDet = 0.0;
    readMatrixFromFile(&mat_2x2, "/home/edo/dev/cath/test_files/matrix/2x2_matrix.txt");
    actualDet = calcDeterminant(&mat_2x2);
    TEST_ASSERT_DOUBLE_WITHIN_MESSAGE(
        MATRIX_TOLERANCE, expectedDet,
        actualDet, "2x2 Matrix determinant is not correct");

    /*Case 2 - simple 3x3 matrix*/
    expectedDet = 558.0;
    readMatrixFromFile(&mat_3x3, "/home/edo/dev/cath/test_files/matrix/3x3_matrix.txt");
    actualDet = calcDeterminant(&mat_3x3);
    TEST_ASSERT_DOUBLE_WITHIN_MESSAGE(
        MATRIX_TOLERANCE, expectedDet,
        actualDet, "3x3 Matrix determinant is not correct");

    /*Case 3 - simple 4x4 matrix*/
    expectedDet = -376.0;
    readMatrixFromFile(&mat_4x4, "/home/edo/dev/cath/test_files/matrix/4x4_matrix.txt");
    actualDet = calcDeterminant(&mat_4x4);
    TEST_ASSERT_DOUBLE_WITHIN_MESSAGE(
        MATRIX_TOLERANCE, expectedDet,
        actualDet, "4x4 Matrix determinant is not correct");

    /*Case 4 - Square null matrix*/
    expectedDet = 0.0;
    readMatrixFromFile(&squareNullMatrix, "/home/edo/dev/cath/test_files/matrix/square_null_matrix.txt");
    actualDet = calcDeterminant(&squareNullMatrix);
    TEST_ASSERT_DOUBLE_WITHIN_MESSAGE(
        MATRIX_TOLERANCE, expectedDet,
        actualDet, "null Matrix determinant is not correct");

    freeMatrix(&mat_2x2);
    freeMatrix(&mat_3x3);
    freeMatrix(&mat_4x4);
    freeMatrix(&squareNullMatrix);
}