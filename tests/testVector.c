#include "unity.h"
#include "utils.h"
#include "Vector.h"
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

void setUp()
{
    /*
    The setUp function can contain anything
    you would like to run before each test.
    */
}

void tearDown()
{
    /*
    The tearDown function can contain anything
    you would like to run after each test
    */
}

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
    printf("L1 norm: %lf\n", calcNorm(&L1Vector, 1));
    TEST_ASSERT_DOUBLE_WITHIN_MESSAGE(
        VECTOR_TOLERANCE,
        17.3,
        calcNorm(&L1Vector, 1),
        "L1 non-null norm calculation failed"
    );

    /*Case 2 - L2 norm*/
    readVectorFromFile(&L2Vector, "/home/edo/dev/cath/test_files/vectors/norm/L2_norm.txt");
    printf("L2 norm: %lf\n", calcNorm(&L2Vector, 2));
    TEST_ASSERT_DOUBLE_WITHIN_MESSAGE(
        VECTOR_TOLERANCE,
        8.566796,
        calcNorm(&L2Vector, 2),
        "L2 non-null norm calculation failed"
    );

    /*Case 3 - Linf norm, is the max(fabs(x_i))*/ 
    readVectorFromFile(&LinfVector, "/home/edo/dev/cath/test_files/vectors/norm/Linf_norm.txt");
    printf("Linf norm: %lf\n", calcNorm(&LinfVector, 1000));
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
}


int main(void)
{
    UNITY_BEGIN();

    puts("Vector Tests");

    RUN_TEST(test_vector_init);
    RUN_TEST(test_vector_free);
    RUN_TEST(test_vector_files);
    RUN_TEST(test_vector_norm);

    UNITY_END();

    return EXIT_SUCCESS;
}