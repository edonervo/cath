#include "unity.h"
#include "utils.h"
#include "Vector.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

double VECTOR_TOLERANCE = 1e-6;
int VECTOR_SIZE = 1000;
double VECTOR_MIN = 0.0;
double VECTOR_MAX = 1.0;
char* FILE_TEST_PATH = "/home/edo/dev/cath/tmp/output.txt"; // TODO: Handle Paths in C
char* FILE_WRONG_FORMAT = "/home/edo/dev/cath/test_files/wrong_vector_format.txt";

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

int main(void)
{
    UNITY_BEGIN();

    puts("Vector Tests");

    RUN_TEST(test_vector_init);
    RUN_TEST(test_vector_free);
    RUN_TEST(test_vector_files);

    UNITY_END();

    return EXIT_SUCCESS;
}