#include "BvpOde.h" 

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
    int numNodes = 5;

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

    solve(&bvp, false);
    printVector(&solVec);
}