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

}