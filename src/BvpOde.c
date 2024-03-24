#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "BvpOde.h"
#include "assert.h"

void _initBvpOde(
    BvpOde* bvpOde,
    SecondOrderOde* ode,
    BoundaryConditions* bc,
    int numNodes
    )
{
    // Second order 1D differntial equation
    bvpOde->ode;
    // Boundary conditions
    bvpOde->bc = bc;
    // Other
    bvpOde->numNodes = numNodes;
    
    // Set up the grid
    FiniteDiffGrid1D grid;
    initFiniteDiffGrid1D(&grid, bvpOde->numNodes, ode->xMin, ode->xMax);

}

void solve(BvpOde* bvpOde)
{
    // Init
    initVector(bvpOde->rhsVec, bvpOde->numNodes);
    initMatrix(bvpOde->lhsMat, bvpOde->numNodes, bvpOde->numNodes);
    populateMatrix(bvpOde);
    populateVector(bvpOde);
}

void populateMatrix(BvpOde* bvpOde)
{
    for (size_t i=1; i<bvpOde->numNodes-1; i++)
    {
        // xm, x and xp are x(i-1), x(i) and x(i+1)
        double xm = bvpOde->grid->nodes[i-1].coordinate;
        double x = bvpOde->grid->nodes[i].coordinate;
        double xp = bvpOde->grid->nodes[i+1].coordinate;
        double alpha = 2.0/(xp-xm)/(x-xm);
        double beta = -2.0/(xp-x)/(x-xm);
        double gamma = 2.0/(xp-xm)/(xp-x);
        bvpOde->lhsMat->data[i][i-1] = (bvpOde->ode->coeffTxx)*alpha - (bvpOde->ode->coeffTx)/(xp-xm);
        bvpOde->lhsMat->data[i][i] = (bvpOde->ode->coeffTxx)*beta + bvpOde->ode->coeffT;
        bvpOde->lhsMat->data[i][i+1] = (bvpOde->ode->coeffTxx)*gamma + (bvpOde->ode->coeffTx/(xp-xm));
    }

}

void populateVector(BvpOde* bvpOde)
{
    for (size_t i=1; i<bvpOde->rhsVec->size-1; i++)  
    {
        double x = bvpOde->grid->nodes[i].coordinate;
        bvpOde->rhsVec->data[i] = bvpOde->ode->rhsFunc(x);
    }
}

void applyBoundaryConditions(BvpOde* bvpOde)
{
    bool left_bc_applied = false;
    bool right_bc_applied = false;

    if (bvpOde->bc->lhsBcIsDirichlet)
    {
        bvpOde->lhsMat->data[0][0] = 1.0;
        bvpOde->rhsVec->data[0] = bvpOde->bc->lhsBcValue;
        left_bc_applied = true;
    }

}