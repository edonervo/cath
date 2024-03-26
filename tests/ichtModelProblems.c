#include "BvpOde.h" 
#include "Plot.h"
#include "math.h"
#include "unity.h"

double problem_rhs_lab4_es1(double x)
{
    // -qvol / k
    double k = 5; // [W/mK]
    double qvol = 5e05; // [W/m3]
    return -qvol / k;
}

void solve_icht_lab4_es1()
{
    // Data
    double k = 5; // [W/mK]
    double qvol = 5e05; // [W/m3]
    double delta = 0.05; // [m]
    double T0 = 300; // [K]
    
    // Discretization
    int numNodes = 1000;

    // Problem structures
    Vector solVec;
    Vector rhsVec;
    Matrix lhsMat;
    LinearSystem linSys;
    SecondOrderOde ode;
    BoundaryConditions bc;
    FiniteDiffGrid1D grid;

    BvpOde bvp;

    // Initialization

    initSecondOrderOde(
        &ode,
        1.0, 0.0, 0.0,
        problem_rhs_lab4_es1,
        0.0, delta
    );

    setRhsDirichletBc(&bc, 300);
    setLhsNeumannBc(&bc, 0);

    initBvpOde(&solVec, &rhsVec, &lhsMat, &linSys, &ode, &bc, &grid, numNodes, &bvp);

    // Solution
    solve(&bvp, false);

    // Compute analytic solution for testing
    Vector solVecExpected;
    initVector(&solVecExpected, numNodes);
    for (size_t i=0; i<numNodes; i++)
    {
        solVecExpected.data[i] = -qvol/(2 * k) * (pow(grid.nodes[i].coordinate, 2) - pow(delta, 2)) + T0;
    }
    // Let's tolerate a 0.5 K absolute error
    TEST_ASSERT_DOUBLE_ARRAY_WITHIN(0.5, solVecExpected.data, solVec.data, numNodes);
    // Plotting
    // plot(&solVec, &grid);
}