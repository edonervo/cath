/*Vector math class Header*/
#include "Vector.h"
#include <stdio.h>
#include <stdlib.h>

void initVector(Vector* vec, size_t size) {
    vec->data = (double *)malloc(size * sizeof(double));
    if (vec->data == NULL) {
        perror("Memory Allocation failed");
        exit(EXIT_FAILURE);
    }
    vec->size = size;
    for (size_t i=0; i<size; i++) {
        vec->data[i] = 0.0;
    }
}

void freeVector(Vector* vec) {
    free(vec->data);
    vec->data = NULL;
    vec->size = 0;
}

void printVector(Vector* vec) {
    for (size_t i = 0; i<vec->size; i++) {
        if (i < (vec->size - 1)) {
            printf("%f ", vec->data[i]);
        } else {
            printf("%f\n", vec->data[i]);
        }
    }
}