#include <stdlib.h>
#include <stdio.h>
#include <time.h>

double randomDouble(double min, double max)
{   
    srand((unsigned int) clock());
    return min + ((double)rand() / RAND_MAX) * (max - min);
}
