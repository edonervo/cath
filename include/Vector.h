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
void printVector(Vector* vec);
void freeVector(Vector* vec);

#endif /* VECTOR */





