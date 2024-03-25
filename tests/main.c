#include "unity.h"
#include "utils.h"
#include "testVector.h"
#include "testMatrix.h"
#include "testLynSys.h" 
#include "testGrid.h"
#include "ichtModelProblems.h"  
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
    RUN_TEST(test_matrix_algebra);

    // Grid
    test_init_grid();

    // Linear System
    RUN_TEST(test_linsys_solve);

    // Model Problems
    solve_icht_lab4_es1();

    UNITY_END();

    return EXIT_SUCCESS;
}