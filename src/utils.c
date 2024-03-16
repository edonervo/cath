#include <stdlib.h>
#include <stdio.h>

double randomDouble(double min, double max)
{   
    return min + ((double)rand() / RAND_MAX) * (max - min);
}
