#include "FiniteDiffGrid.h" 
#include "Node.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

void initFiniteDiffGrid1D(FiniteDiffGrid1D* grid, double numNodes, double xMin, double xMax)
{
    if (xMin >= xMax)
    {
        fprintf(stderr, "1D Grid is not defined correctly as xMin > xMax!\n");
        exit(EXIT_FAILURE);
    }
    grid->numNodes = numNodes;
    grid->xMax = xMax;
    grid->xMin = xMin;
    grid->nodes = (Node *)malloc(numNodes * sizeof(Node));
    if (grid->nodes == NULL)
    {
        perror("Memory Allocation failed");
        exit(EXIT_FAILURE);
    }
    double stepsize = (xMax - xMin) / (double)(numNodes - 1);
    for (size_t i=0; i<numNodes; i++)
    {
        grid->nodes[i].coordinate = xMin+i*stepsize;
    }
    // TODO: assert something?
}

bool _checkInitGrid(FiniteDiffGrid1D* grid)
{
    if (grid->nodes == NULL)
    {
        return false;
    } else
    {
        return true;
    }
}   

void printFiniteDiffGrid1D(FiniteDiffGrid1D* grid)
{
    /*Prints the finite diff grid in one dimension*/
    if (!_checkInitGrid(grid))
    {
        fprintf(stderr, "Grid is not initialized! Exiting...");
        exit(EXIT_FAILURE);
    }
        for (size_t i = 0; i < grid->numNodes; i++)
    {
        if (i < (grid->numNodes - 1))
        {
            printf("%f ", grid->nodes[i].coordinate);
        }
        else
        {
            printf("%f\n", grid->nodes[i].coordinate);
        }
    }
}