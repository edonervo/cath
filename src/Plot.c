#include "Plot.h"   
#include "Vector.h" 
#include "FiniteDiffGrid.h" 
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void plot(Vector* vec, FiniteDiffGrid1D* grid)
{
    /*Plots a 1D vector with its grid*/

    // Print data to a temporary file
    char* commandsForGnuplot[] = {"set title \"TITLE\"", "plot 'data.temp' with linespoints\n"};
    FILE* temp = fopen("data.temp", "w");

    if (temp == NULL) 
    {
        perror("Error: ");
        exit(EXIT_FAILURE);
    }

    for (size_t i=0; i<vec->size; i++)
    {
        fprintf(temp, "%lf %lf\n", grid->nodes[i].coordinate, vec->data[i]);
    }
    

    // Sends data to gnuplot
    
    FILE *gnuplotPipe = popen("gnuplot -persistent", "w");
    if (!gnuplotPipe)
    {
        fprintf(stderr, "Gnuplot is not installed on this system.\n");
        exit(EXIT_FAILURE);
    } 

    for (size_t i=0; i<ARRAY_LENGTH(commandsForGnuplot); i++)
    {
        fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i]);
    }
}