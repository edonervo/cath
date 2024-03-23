#include "testGrid.h"
#include "FiniteDiffGrid.h"    
#include "unity.h"
#include "utils.h"

double GRID_TOLERANCE = 1e-6;


void test_init_grid()
{
    FiniteDiffGrid1D grid;
    int numNodes = 10;
    double xMin = 0.0;
    double xMax = 10.0;
    initFiniteDiffGrid1D(&grid, numNodes, xMin, xMax);
    TEST_ASSERT_DOUBLE_WITHIN_MESSAGE(
        GRID_TOLERANCE,
        xMin,
        grid.xMin,
        "Xmin of grid does not correspond to inoput"    
    );
    TEST_ASSERT_DOUBLE_WITHIN_MESSAGE(
        GRID_TOLERANCE,
        xMax,
        grid.xMax,
        "Xmax of grid does not correspond to inoput"    
    );
    // Check sixe of nodes arrays is same as numNodes
    TEST_ASSERT_EQUAL_INT(numNodes, grid.numNodes);
}