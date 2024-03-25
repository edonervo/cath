#ifndef BOUNDARY_CONDITIONS
#define BOUNDARY_CONDITIONS

#include <stdbool.h>

typedef struct BoundaryConditions
{
    bool lhsBcIsDirichlet;
    bool rhsBcIsDirichlet;
    bool lhsBcIsNeumann;
    bool rhsBcIsNeumann;
    double lhsBcValue;
    double rhsBcValue;
} BoundaryConditions;

void setLhsDirichletBc(BoundaryConditions* bp, double lhsValue);
void setRhsDirichletBc(BoundaryConditions* bp, double rhsValue);
void setLhsNeumannBc(BoundaryConditions* bp, double lhsDerivValue);
void setRhsNeumannBc(BoundaryConditions* bp, double rhsDerivValue);
#endif