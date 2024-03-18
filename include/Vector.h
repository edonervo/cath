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
bool _checkVectorFileFormat(char* filePath);
void freeVector(Vector* vec);

// IO
void printVector(const Vector* vec);
void printVectorToFile(const Vector* vec, char* filePath);
void readVectorFromFile(Vector* vec, char* filePath);

// utils
void randomVector(Vector* vec, int size, double min, double max);

// Math
double findMax(Vector* vec);
double findAbsMax(Vector* vec);
double findMin(Vector* vec);
double findAbsMin(Vector* vec);
void addVectors(Vector* vec1, Vector* vec2, Vector* result);
void substractVectors(Vector* vec1, Vector* vec2, Vector* result);
void invertSign(Vector* vec);
void multiplyByScalar(Vector* vec, double scalar);
double scalarProduct(Vector* vec1, Vector* vec2);
double calcNorm(const Vector* vec, int p); // Calculate LP norm

#endif /* VECTOR */