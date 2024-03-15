#include "unity.h"
#include "Vector.h"
#include <stdlib.h>
#include <stdio.h>

double TOLERANCE = 1e-8;

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
    size_t size = 1000;
    initVector(&vector, size);

    TEST_ASSERT_NOT_NULL_MESSAGE(vector.data, "Vector pointer is not null");
    TEST_ASSERT_EQUAL_INT_MESSAGE(size, vector.size, "Size of the Vectors does not correspond to input");

    for (size_t i = 0; i < size; i++)
    {
        TEST_ASSERT_DOUBLE_WITHIN_MESSAGE(
            TOLERANCE, 0.0,
            vector.data[i], "Vector was not initialized correctly");
    }

    freeVector(&vector);
}

int main(void)
{
    UNITY_BEGIN();

    puts("Vector Tests");

    RUN_TEST(test_vector_init);

    UNITY_END();

    return EXIT_SUCCESS;
}
