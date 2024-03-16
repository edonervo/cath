#include "unity.h"
#include "utils.h"
#include "Vector.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

double VECTOR_TOLERANCE = 1e-8;
int VECTOR_SIZE = 1000;
double VECTOR_MIN = 0.0;
double VECTOR_MAX = 1.0;

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
    Vector vector;
    randomVector(&vector, 5, VECTOR_MIN, VECTOR_MAX);

    // Print to file
    char* filename = "tmp/output.txt";
    printVectorToFile(&vector, filename);

    // Read from file

    freeVector(&vector);

}

int main(void)
{
    UNITY_BEGIN();

    puts("Vector Tests");

    RUN_TEST(test_vector_init);
    RUN_TEST(test_vector_free);
    test_vector_files();

    UNITY_END();

    return EXIT_SUCCESS;
}