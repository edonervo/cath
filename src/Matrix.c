#include "Matrix.h" 
#include <stdio.h>
#include <stdlib.h>

void initMatrix(Matrix* mat, size_t rows, size_t cols) {
    if (rows <= 0) {
        fprintf(stderr, "Error: rows size must be > 0");
        exit(EXIT_FAILURE);
    }

    if (cols <= 0) {
        fprintf(stderr, "Error: cols size must be > 0");
        exit(EXIT_FAILURE);
    }

    mat->data = (double **)malloc(rows * sizeof(double *));
    if (mat->data == NULL) {
        perror("Memory Allocation Failed");
        exit(EXIT_FAILURE);
    }

    mat->rows = rows;
    mat->cols = cols;

    for (size_t i=0; i<rows; i++) {
        mat->data[i] = (double *)malloc(cols * sizeof(double));
        if (mat->data[i] == NULL) {
            perror("Memory allocation Failed");
            exit(EXIT_FAILURE);
        }

        // Init to 0.0
        for (size_t j=0; j<cols; j++) {
            mat->data[i][j] = 0.0;
        }
    }   
}

void printMatrix(Matrix* mat) {
    if (mat->data == NULL) {
        fprintf(stderr, "Matrix has not been initialized");
        exit(EXIT_FAILURE);
    }

    for (size_t i=0; i<mat->rows; i++) {
        for (size_t j=0; j<mat->cols; j++) {
            if (j<mat->cols-1) {
                printf("%f ", mat->data[i][j]);
            } else {
                printf("%f\n", mat->data[i][j]);
            }
        }
    }
}