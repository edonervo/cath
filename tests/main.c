#include "unity.h"
#include "utils.h"
#include "testVector.h"
#include "testMatrix.h"
#include <stdlib.h>

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

int main(void)
{
    UNITY_BEGIN();
    
    // Vector
    RUN_TEST(test_vector_init);
    RUN_TEST(test_vector_free);
    RUN_TEST(test_vector_files);
    RUN_TEST(test_vector_norm);
    RUN_TEST(test_vector_algebra);

    // Matrix
    RUN_TEST(test_matrix_init);
    RUN_TEST(test_matrix_free);
    RUN_TEST(test_matrix_files);

    UNITY_END();

    return EXIT_SUCCESS;
}