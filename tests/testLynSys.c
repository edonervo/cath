#include "testLynSys.h"
#include "FiniteDiffGrid.h"
#include "LinSys.h"
#include "unity.h"

double LINSYS_TOLERANCE = 1e-10;

void test_linsys_solve()
{   
    LinearSystem linsys;
    Matrix mat;
    Vector vec;
    Vector actualSolVec;
    Vector expectedSolVec;

    /*Case 1* - 2x2 simple*/
    // Read test data
    readMatrixFromFile(&mat, "/home/edo/dev/cath/test_files/linsys/simple/2x2_linsys_mat.txt");
    readVectorFromFile(&vec, "/home/edo/dev/cath/test_files/linsys/simple/2x2_linsys_vec.txt");
    readVectorFromFile(&expectedSolVec, "/home/edo/dev/cath/test_files/linsys/simple/2x2_linsys_sol.txt");

    // Init
    initLinSys(&linsys, &mat, &vec);
    solveLinSys(&linsys, &actualSolVec);
    TEST_ASSERT_DOUBLE_ARRAY_WITHIN(LINSYS_TOLERANCE, expectedSolVec.data, actualSolVec.data, expectedSolVec.size);
}