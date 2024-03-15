/*Vector math class Header*/
#ifndef VECTOR
#define VECTOR

#include <stddef.h>

typedef struct Vector
{
    double* data;
    size_t size;
} Vector;

void initVector(Vector* vec, int size);
void printVector(const Vector* vec);
void freeVector(Vector* vec);
int getSize(const Vector* vec);
double at(const Vector* vec, int index);

double calcNorm(const Vector* vec, int p); // Calculate LP norm

// Algebra operations
void addVectors(Vector* vec1, Vector* vec2, Vector* result);
void SubstractVectors(Vector* vec1, Vector* vec2, Vector* result);
double ScalarProduct(Vector* vec1, Vector* vec2);

#endif /* VECTOR */