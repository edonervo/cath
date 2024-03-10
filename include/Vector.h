/*Vector math class Header*/
#ifndef VECTOR
#define VECTOR

#include <stddef.h>

typedef struct Vector
{
    double* data;
    size_t size;
} Vector;

void initVector(Vector* vec, size_t size);
void printVector(const Vector* vec);
void freeVector(Vector* vec);
size_t getSize(const Vector* vec);
double at(const Vector* vec, size_t index);

double calcNorm(Vector* vec, int p); // Calculate LP norm

// Algebra operations
void addVectors(Vector* vec1, Vector* vec2, Vector* result);
#endif /* VECTOR */