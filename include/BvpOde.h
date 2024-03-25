#ifndef BVPODE
#define BVPODE

#include <stdio.h>
#include <stdlib.h>
#include "SecondOrderOde.h"
#include "BoundaryConditions.h"
#include "FiniteDiffGrid.h"
#include "Vector.h" 
#include "Matrix.h"
#include "LinSys.h"

typedef struct BvpOde
{
    SecondOrderOde* ode;
    BoundaryConditions* bc;

    int numNodes;
    FiniteDiffGrid1D* grid;

    Vector* solVec;
    Vector* rhsVec;
    Matrix* lhsMat;

    LinearSystem* linSys;

} BvpOde;



#endif

