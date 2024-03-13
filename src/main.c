#include <stdio.h>
#include <stdlib.h>
#include "Vector.h"
#include "Matrix.h"

void testVectors(void) {
        // Vectors
    // Init
    puts("Defining a vector...\n");
    Vector vec;
    initVector(&vec, 10);

    // Assign
    for (size_t i=0; i<getSize(&vec); i++) {
        vec.data[i] = (double)i;
    }
    printf("Value is %d\n", at(&vec, 9));

    // Calculate Norm
    double norm = calcNorm(&vec, 2);
    printf("norm: %f\n", norm);

    printVector(&vec);
    printf("Vector size: %d\n", getSize(&vec));
    freeVector(&vec);

    // Algebra with vectors
    Vector vec1, vec2, vec3;
    initVector(&vec1, 5);
    initVector(&vec2, 5);
    initVector(&vec3, 5);   
    for (size_t i=0; i<getSize(&vec1); i++) {
        vec1.data[i] = (double)i;
        vec2.data[i] = (double)i * 2.0;
    }
    printf("Vector 1: \n");
    printVector(&vec1);
    printf("Vector 2: \n");
    printVector(&vec2);
    printf("Vector 3: \n");
    printVector(&vec3);

    addVectors(&vec1, &vec2, &vec3);
    printf("Vector 3 after sum: \n");
    printVector(&vec3);

    // printf("Vector 3: \n");

    // ScalarProduct
    double scProd = ScalarProduct(&vec2, &vec3);
    printf("Scalar Product: %f\n", scProd);

    freeVector(&vec);
    freeVector(&vec1);
    freeVector(&vec2);
    freeVector(&vec3);
    return EXIT_SUCCESS;
}

void testMatrix(void) {
    // Init Mat
    Matrix mat;

    initMatrix(&mat, 3, 3);
    printMatrix(&mat);
    freeMatrix(&mat);
};

void testLinSys(void) {
    Matrix mat;
    initMatrix(&mat, 3, 3);

}

int main() {
    // testVectors();
    testMatrix();

}