#ifndef FINITEDIFFGRID
#define FINITEDIFFGRID

#include "Node.h"

typedef struct FiniteDiffGrid1D
{
    int numNodes;
    double xMin;
    double xMax;
    Node* nodes;
} FiniteDiffGrid1D;

void initFiniteDiffGrid1D(FiniteDiffGrid1D* grid, double numNodes, double xMin, double xMax);

#endif