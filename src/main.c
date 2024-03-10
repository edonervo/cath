#include <stdio.h>
#include <stdlib.h>
#include "Vector.h"

int main() {
    // Vectors
    puts("Defining a vector...\n");
    Vector vec;
    initVector(&vec, 10);
    printVector(&vec);
    freeVector(&vec);

    return EXIT_SUCCESS;
}