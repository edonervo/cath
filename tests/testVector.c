#include "unity.h"
#include "utils.h"
#include "Vector.h"
#include "testVector.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

// TODO: read from a test config file
double VECTOR_TOLERANCE = 1e-6;
int VECTOR_SIZE = 1000;
double VECTOR_MIN = 0.0;
double VECTOR_MAX = 1.0;
char* FILE_TEST_PATH = "/home/edo/dev/cath/tmp/output.txt"; // TODO: Handle Paths in C
char* FILE_WRONG_FORMAT = "/home/edo/dev/cath/test_files/vectors/wrong_vector_format.txt";
char BASE_FILE_TESTS[100] = "/home/edo/dev/cath/test_files";

void test_vector_init()
{
    Vector vector;
    initVector(&vector, VECTOR_SIZE);

    TEST_ASSERT_NOT_NULL_MESSAGE(vector.data, "Vector pointer is null");
    TEST_ASSERT_EQUAL_INT_MESSAGE(VECTOR_SIZE, vector.size, "Size of the Vectors does not correspond to input");

    for (size_t i = 0; i < VECTOR_SIZE; i++)
    {
        TEST_ASSERT_DOUBLE_WITHIN_MESSAGE(
            VECTOR_TOLERANCE, 0.0,
            vector.data[i], "Vector was not initialized correctly");
    }

    freeVector(&vector);
}

void test_vector_free()
{
    Vector vector;
    initVector(&vector, VECTOR_SIZE);
    freeVector(&vector);
    TEST_ASSERT_NULL_MESSAGE(vector.data, "Vector pointer is not null");
    TEST_ASSERT_EQUAL_INT(0, vector.size);
}

void test_vector_files()
{
    /*Case 1 - Correct output and input file*/
    Vector vector;
    Vector newVector;

    randomVector(&vector, VECTOR_SIZE, VECTOR_MIN, VECTOR_MAX); //Generate random test data
    // Print to file
    printVectorToFile(&vector, FILE_TEST_PATH);  
    // Read from file
    readVectorFromFile(&newVector, FILE_TEST_PATH);
    // Vector must be the same
    for (size_t i = 0; i < VECTOR_SIZE; i++)
    {
        TEST_ASSERT_DOUBLE_WITHIN_MESSAGE(
            VECTOR_TOLERANCE, vector.data[i],
            newVector.data[i], "Case 1 - Vector are not the same\n");
    }(&newVector, &vector, VECTOR_SIZE);

    /*Case 2 - vector in the file is wrong format*/
    bool file_good;
    bool file_bad;

    TEST_ASSERT_TRUE_MESSAGE(
        _checkVectorFileFormat(FILE_TEST_PATH), 
        "Correct format file is recognized with wrong format"
        );
    TEST_ASSERT_FALSE_MESSAGE(
        _checkVectorFileFormat(FILE_WRONG_FORMAT),
        "Wrong format file is recognized with correct format"
        );

    freeVector(&vector);
    freeVector(&newVector);
}

void test_vector_norm()
{
    // TODO: here I am hardcoding everything
    Vector L1Vector;
    Vector L2Vector;
    Vector LinfVector;
    Vector NullVector;
    /*Case 1 - L1 norm*/ // Todo: handle file path much bettern than this
    readVectorFromFile(&L1Vector, strcat(BASE_FILE_TESTS, "/vectors/norm/L1_norm.txt"));
    TEST_ASSERT_DOUBLE_WITHIN_MESSAGE(
        VECTOR_TOLERANCE,
        17.3,
        calcNorm(&L1Vector, 1),
        "L1 non-null norm calculation failed"
    );

    /*Case 2 - L2 norm*/
    readVectorFromFile(&L2Vector, "/home/edo/dev/cath/test_files/vectors/norm/L2_norm.txt");
    TEST_ASSERT_DOUBLE_WITHIN_MESSAGE(
        VECTOR_TOLERANCE,
        8.566796,
        calcNorm(&L2Vector, 2),
        "L2 non-null norm calculation failed"
    );

    /*Case 3 - Linf norm, is the max(fabs(x_i))*/ 
    readVectorFromFile(&LinfVector, "/home/edo/dev/cath/test_files/vectors/norm/Linf_norm.txt");
    TEST_ASSERT_DOUBLE_WITHIN_MESSAGE(
        VECTOR_TOLERANCE,
        findAbsMax(&LinfVector),
        calcNorm(&LinfVector, 1000),
        "Linf non-null norm calculation failed"
    );

    /*Case 4 - Lp norm of null vector*/ 
    readVectorFromFile(&NullVector, "/home/edo/dev/cath/test_files/vectors/norm/null_vector.txt");
    TEST_ASSERT_DOUBLE_WITHIN_MESSAGE(
        VECTOR_TOLERANCE,
        0.0,
        calcNorm(&NullVector, 1),
        "L1 null norm calculation failed"
    );
    TEST_ASSERT_DOUBLE_WITHIN_MESSAGE(
        VECTOR_TOLERANCE,
        0.0,
        calcNorm(&NullVector, 2),
        "L2 null norm calculation failed"
    );
    TEST_ASSERT_DOUBLE_WITHIN_MESSAGE(
        VECTOR_TOLERANCE,
        0.0,
        calcNorm(&NullVector, 1000),
        "Linf null norm calculation failed"
    );

    freeVector(&L1Vector);
    freeVector(&L2Vector);
    freeVector(&LinfVector);
    freeVector(&NullVector);
}

void test_vector_algebra()
{
    // Test sum of vector
    Vector sumVec1;
    Vector sumVec2;
    Vector sumActual;
    Vector sumExpected;
    readVectorFromFile(&sumVec1, "/home/edo/dev/cath/test_files/vectors/algebra/sum_vec1.txt");
    readVectorFromFile(&sumVec2, "/home/edo/dev/cath/test_files/vectors/algebra/sum_vec2.txt");
    readVectorFromFile(&sumExpected, "/home/edo/dev/cath/test_files/vectors/algebra/sum_result.txt");
    initVector(&sumActual, sumExpected.size);
    addVectors(&sumVec1, &sumVec2, &sumActual);
    TEST_ASSERT_DOUBLE_ARRAY_WITHIN(VECTOR_TOLERANCE, sumExpected.data, sumActual.data, 5);
    freeVector(&sumVec1);
    freeVector(&sumVec2);
    freeVector(&sumActual);
    freeVector(&sumExpected);

    // Test sub of vector
    Vector subVec1;
    Vector subVec2;
    Vector subActual;
    Vector subExpected;
    readVectorFromFile(&subVec1, "/home/edo/dev/cath/test_files/vectors/algebra/sub_vec1.txt");
    readVectorFromFile(&subVec2, "/home/edo/dev/cath/test_files/vectors/algebra/sub_vec2.txt");
    readVectorFromFile(&subExpected, "/home/edo/dev/cath/test_files/vectors/algebra/sub_result.txt");
    initVector(&subActual, subExpected.size);
    substractVectors(&subVec1, &subVec2, &subActual);
    TEST_ASSERT_DOUBLE_ARRAY_WITHIN(VECTOR_TOLERANCE, subExpected.data, subActual.data, 5);
    freeVector(&subVec1);
    freeVector(&subVec2);
    freeVector(&subActual);
    freeVector(&subExpected);

    // Test Negative
    Vector negVector;
    Vector negVectorExpected;
    readVectorFromFile(&negVector, "/home/edo/dev/cath/test_files/vectors/algebra/neg_vec.txt");
    readVectorFromFile(&negVectorExpected, "/home/edo/dev/cath/test_files/vectors/algebra/neg_vec_result.txt");
    invertSign(&negVector);
    TEST_ASSERT_DOUBLE_ARRAY_WITHIN(VECTOR_TOLERANCE, negVectorExpected.data, negVector.data, 5);
    freeVector(&negVector);
    freeVector(&negVectorExpected);

    // Test product with a sclar
    Vector vecWithScalar;
    Vector vecWithScalarExpected;
    readVectorFromFile(&vecWithScalar, "/home/edo/dev/cath/test_files/vectors/algebra/vec_with_scalar.txt");
    readVectorFromFile(&vecWithScalarExpected, "/home/edo/dev/cath/test_files/vectors/algebra/vec_with_scalar_result.txt");
    double scalar = 2.0;
    multiplyByScalar(&vecWithScalar, scalar);
    TEST_ASSERT_DOUBLE_ARRAY_WITHIN(VECTOR_TOLERANCE, vecWithScalar.data, vecWithScalarExpected.data, 5);
    freeVector(&vecWithScalar);
    freeVector(&vecWithScalarExpected);
    

    // Test Scalar Product (Dot-product)
    Vector scalarProductVec1;
    Vector scalarProductVec2;
    double scalarProductExpected = 47.5;
    readVectorFromFile(&scalarProductVec1, "/home/edo/dev/cath/test_files/vectors/algebra/scalar_prod_vec1.txt");
    readVectorFromFile(&scalarProductVec2, "/home/edo/dev/cath/test_files/vectors/algebra/scalar_prod_vec2.txt");
    double scalarProductActual = scalarProduct(&scalarProductVec1, &scalarProductVec2);
    TEST_ASSERT_DOUBLE_WITHIN(VECTOR_TOLERANCE, scalarProductExpected, scalarProductActual);
    freeVector(&scalarProductVec1);
    freeVector(&scalarProductVec2);
}