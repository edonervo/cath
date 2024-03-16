/*Vector math class Header*/
#ifndef VECTOR
#define VECTOR

#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Vector
{
    double* data;
    size_t size;
} Vector;

// private (?)
void initVector(Vector* vec, int size);
bool _checkInitVector(Vector* vec);
void freeVector(Vector* vec);

// IO
void printVector(const Vector* vec);
void printVectorToFile(const Vector* vec, char* filePath);
void readVectorFromFile(Vector* vec, char* filePath);

// utils
void randomVector(Vector* vec, int size, double min, double max);
int getSize(const Vector* vec);
double at(const Vector* vec, int index);

// Math
void addVectors(Vector* vec1, Vector* vec2, Vector* result);
void SubstractVectors(Vector* vec1, Vector* vec2, Vector* result);
double ScalarProduct(Vector* vec1, Vector* vec2);
double calcNorm(const Vector* vec, int p); // Calculate LP norm

#endif /* VECTOR */