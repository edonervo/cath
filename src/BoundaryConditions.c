#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "assert.h"
#include "BoundaryConditions.h" 

void setLhsDirichletBc(BoundaryConditions* bp, double lhsValue)
{
    bp->lhsBcIsNeumann = false;
    bp->lhsBcIsDirichlet = true;
    bp->lhsBcValue = lhsValue;
}
void setRhsDirichletBc(BoundaryConditions* bp, double rhsValue)
{
    bp->rhsBcIsNeumann = false;
    bp->rhsBcIsDirichlet = true;
    bp->rhsBcValue = rhsValue;
}

void setLhsNeumannBc  (BoundaryConditions* bp, double lhsDerivValue)
{
    bp->lhsBcIsNeumann = true;
    bp->lhsBcIsDirichlet = false;
    bp->lhsBcValue = lhsDerivValue;
}
void setRhsNeumannBc  (BoundaryConditions* bp, double rhsDerivValue)
{
    bp->rhsBcIsNeumann = true;
    bp->rhsBcIsDirichlet = false;
    bp->rhsBcValue = rhsDerivValue;
}