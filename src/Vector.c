/*Vector math class Header*/
#include "Vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void initVector(Vector *vec, int size)
{

    if (size <= 0)
    {
        perror("Size of the Vector is <= 0, exiting...\n");
        exit(EXIT_FAILURE);
    }

    vec->data = (double *)malloc(size * sizeof(double));
    if (vec->data == NULL)
    {
        perror("Memory Allocation failed");
        exit(EXIT_FAILURE);
    }
    vec->size = size;
    for (size_t i = 0; i < size; i++)
    {
        vec->data[i] = 0.0;
    }
}

void freeVector(Vector *vec)
{
    free(vec->data);
    vec->data = NULL;
    vec->size = 0;
}

void printVector(const Vector *vec)
{
    for (size_t i = 0; i < vec->size; i++)
    {
        if (i < (vec->size - 1))
        {
            printf("%f ", vec->data[i]);
        }
        else
        {
            printf("%f\n", vec->data[i]);
        }
    }
}

int getSize(const Vector *vec)
{
    return vec->size;
}

double at(const Vector *vec, int index)
{
    if (index >= 0 && index <= getSize(vec))
    {
        return vec->data[index];
    }
    else
    {
        fprintf(stderr, "Index out of bounds\n");
        exit(EXIT_FAILURE);
    }
}

double calcNorm(const Vector *vec, int p)
{
    double norm = 0.0;
    double sum = 0.0;

    for (size_t i = 0; i < getSize(&vec); i++)
    {
        sum += pow(fabs(vec->data[i]), p);
    }

    return pow(sum, 1.0 / (double)p);
}

// double calcNorm(Vector* vec) { // Overload for L2 norm
//     double norm = 0.0;
//     double sum = 0.0;

//     for (size_t i=0; i<getSize(&vec); i++) {
//         sum += pow(fabs(vec->data[i]), 2.0);
//     }

//     return pow(sum, 1.0/2.0);
// }

void addVectors(Vector *vec1, Vector *vec2, Vector *result)
{
    // Algebraic sum of two vectors
    if ((getSize(vec1) != getSize(vec2)) || ((getSize(vec1) != getSize(result))))
    {
        fprintf(stderr, "Vector are incompatible in size");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < getSize(result); i++)
    {
        result->data[i] = vec1->data[i] + vec2->data[i];
    }
}

void SubstractVectors(Vector *vec1, Vector *vec2, Vector *result)
{
    if ((getSize(vec1) != getSize(vec2)) || ((getSize(vec1) != getSize(result))))
    {
        fprintf(stderr, "Vector are incompatible in size");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < getSize(result); i++)
    {
        result->data[i] = vec1->data[i] - vec2->data[i];
    }
}

double ScalarProduct(Vector *vec1, Vector *vec2)
{
    if (getSize(vec1) != getSize(vec2))
    {
        fprintf(stderr, "Vector are incompatible in size");
        exit(EXIT_FAILURE);
    }

    double result = 0.0;
    for (size_t i = 0; i < getSize(vec1); i++)
    {
        result += at(vec1, i) * at(vec2, i);
    }

    return result;
}
