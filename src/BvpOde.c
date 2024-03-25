#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "BvpOde.h"
#include "assert.h"

void initBvpOde(
    Vector* solVec,
    Vector* rhsVec,
    Matrix* lhsMat,
    LinearSystem* linSys,
    SecondOrderOde* ode,
    BoundaryConditions* bc,
    FiniteDiffGrid1D* grid,
    int numNodes,
    BvpOde* bvp
    )    
{
    // Init
    // Size of the 1D proble,s
    bvp->numNodes = numNodes;
    // Knwon and solution vector
    initVector(solVec, bvp->numNodes);
    initVector(rhsVec, bvp->numNodes);
    bvp->rhsVec = rhsVec;
    bvp->solVec = solVec;
    // LHS Matrix
    initMatrix(lhsMat, bvp->numNodes, bvp->numNodes);
    bvp->lhsMat = lhsMat;
    // Linear System to solve
    initLinSys(linSys, bvp->lhsMat, bvp->rhsVec);
    bvp->linSys = linSys;
    // Init 2nd ORDER 1D diff equation
    initSecondOrderOde(
        ode, 
        ode->coeffTxx, ode->coeffTx, ode->coeffT,
        ode->rhsFunc,
        ode->xMin, ode->xMax);
    bvp->ode = ode;
    // Boundary conditions
    bvp->bc = bc;
    // Set up the grid
    initFiniteDiffGrid1D(grid, bvp->numNodes, bvp->ode->xMin, bvp->ode->xMax);
    bvp->grid = grid;
}

void solve(BvpOde* bvp, bool verbose)
{
    // Init
    populateMatrix(bvp);
    populateVector(bvp);
    applyBoundaryConditions(bvp);

    // Solve the linsys
    solveLinSys(bvp->linSys, bvp->solVec);

    // Debug output
    if (verbose)
    {
        printf("Matrix: \n");
        printMatrix(bvp->lhsMat);
        printf("---------------\n\n");

        printf("Known Vector: \n");
        printVector(bvp->rhsVec);
        printf("---------------\n\n");

        printf("Grid: \n");
        for (size_t i=0; i<bvp->numNodes; i++)
        {
            if (i<bvp->numNodes - 1)
            {
                printf("%lf ", bvp->grid->nodes[i].coordinate);
            } else
            {
                printf("%lf\n", bvp->grid->nodes[i].coordinate);

            }
        }
        printf("---------------\n\n");

        printf("Boundary Conditions: \n");
        if (bvp->bc->lhsBcIsDirichlet)
        {
            printf("Lhs is Dirichlet, T = %lf K\n", bvp->bc->lhsBcValue);
        }
        if (bvp->bc->lhsBcIsNeumann)
        {
            printf("Lhs is Neumann, DT/DX = %lf\n", bvp->bc->lhsBcValue);
        }
        if (bvp->bc->rhsBcIsDirichlet)
        {
            printf("Rhs is Dirichlet, T = %lf K\n", bvp->bc->rhsBcValue);
        }
        if (bvp->bc->rhsBcIsNeumann)
        {
            printf("Rhs is Neumann, DT/DX = %lf\n", bvp->bc->rhsBcValue);
        }
        printf("---------------\n\n");

        printf("Solution Vector: \n");
        printVector(bvp->solVec);
        printf("---------------\n\n");
    }
}

void populateMatrix(BvpOde* bvp)
{
    for (size_t i=1; i<bvp->numNodes-1; i++)
    {
        // xm, x and xp are x(i-1), x(i) and x(i+1)
        double xm = bvp->grid->nodes[i-1].coordinate;
        double x = bvp->grid->nodes[i].coordinate;
        double xp = bvp->grid->nodes[i+1].coordinate;
        double alpha = 2.0/(xp-xm)/(x-xm);
        double beta = -2.0/(xp-x)/(x-xm);
        double gamma = 2.0/(xp-xm)/(xp-x);
        bvp->lhsMat->data[i][i-1] = (bvp->ode->coeffTxx)*alpha - (bvp->ode->coeffTx)/(xp-xm);
        bvp->lhsMat->data[i][i] = (bvp->ode->coeffTxx)*beta + bvp->ode->coeffT;
        bvp->lhsMat->data[i][i+1] = (bvp->ode->coeffTxx)*gamma + (bvp->ode->coeffTx/(xp-xm));
    }
}

void populateVector(BvpOde* bvp)
{
    for (size_t i=1; i<bvp->rhsVec->size-1; i++)  
    {
        double x = bvp->grid->nodes[i].coordinate;
        bvp->rhsVec->data[i] = bvp->ode->rhsFunc(x);
    }
}

void applyBoundaryConditions(BvpOde* bvp)
{
    bool left_bc_applied = false;
    bool right_bc_applied = false;

    if (bvp->bc->lhsBcIsDirichlet)
    {
        bvp->lhsMat->data[0][0] = 1.0;
        bvp->rhsVec->data[0] = bvp->bc->lhsBcValue;
        left_bc_applied = true;
    }

    if (bvp->bc->rhsBcIsDirichlet)
    {
        bvp->lhsMat->data[bvp->numNodes-1][bvp->numNodes-1] = 1.0;
        bvp->rhsVec->data[bvp->numNodes-1] = bvp->bc->rhsBcValue;
        right_bc_applied = true;
    }

    if (bvp->bc->lhsBcIsNeumann)
    {
        assert(left_bc_applied == false);
        double h = bvp->grid->nodes[1].coordinate - 
                   bvp->grid->nodes[0].coordinate;
        bvp->lhsMat->data[0][0] = -1.0/h;
        bvp->lhsMat->data[0][1] = 1.0/h;
        bvp->rhsVec->data[0] = bvp->bc->lhsBcValue;
        left_bc_applied = true;
    }

    if (bvp->bc->rhsBcIsNeumann)
    {
        assert(right_bc_applied == false);
        double h = bvp->grid->nodes[bvp->numNodes-1].coordinate - 
                   bvp->grid->nodes[bvp->numNodes-2].coordinate;
        bvp->lhsMat->data[bvp->numNodes-1][bvp->numNodes-2] = -1.0/h;
        bvp->lhsMat->data[bvp->numNodes-1][bvp->numNodes-1] = 1.0/h;
        bvp->rhsVec->data[bvp->numNodes-1] = bvp->bc->rhsBcValue;
        left_bc_applied = true;
    }

    // Check that bcs have been applied
    assert(left_bc_applied);
    assert(right_bc_applied);
}