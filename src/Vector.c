/*Vector math class Header*/
#include "Vector.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>


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

bool _checkInitVector(Vector* vec)
{
    if (vec->data == NULL) 
    {
        return false;
    } else 
    {
        return true;
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

void printVectorToFile(const Vector* vec, char* filePath) 
{
    if (!_checkInitVector(vec))
    {

    }
    FILE* fp;
    fp = fopen(filePath, "w");

    if (fp == NULL) 
    {
        perror("Error: ");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < vec->size; i++)
    {
        if (i < (vec->size - 1))
        {
            fprintf(fp, "%f ", vec->data[i]);
        }
        else
        {
            fprintf(fp, "%f\n", vec->data[i]);
        }
    }
    fclose(fp);
}

bool _checkVectorFileFormat(char* filePath)
{   
    /*Vector must be saved in a single line with space-sep double*/
    FILE* fp;
    fp = fopen(filePath, "r+");
    if (fp == NULL) {
        perror("Error");
        exit(EXIT_FAILURE);
    }

    int c;
    bool previousWasSpace = false;
    bool previousWasDouble = false;

    while ((c = fgetc(fp)) != EOF)
    {
        if (c == '\n') 
        {
            // Check if the last character before newline was a Double
            if (!previousWasDouble) 
            {
                fclose(fp);
                return false;
            }
            break;
        } else if (c == ' ')
        {
            if (previousWasSpace || !previousWasDouble)
            {
                fclose(fp);
                return false;
            }
            previousWasSpace = true;
        } else if ((c >= '0' && c<='9') || c == '.' || c == '-') 
        {
            previousWasDouble = true;
            previousWasSpace = false;
        } else 
        {
            // Non-double char is found
            fclose(fp);
            return false;
        }
    }
    fclose(fp);
    return true;
}

void readVectorFromFile(Vector* vec, char* filePath) 
{
    if (!_checkVectorFileFormat(filePath))
    {
        fprintf(stderr, "File %s is not in correct format!", filePath);
        exit(EXIT_FAILURE);
    }

    FILE* fp = fopen(filePath, "r");
    if (fp == NULL) {
        fprintf(stderr, "Failed to open file %s! Exiting...\n", filePath);
        exit(EXIT_FAILURE);
    }

    // Determine vector length
    int vectorSize = 0;
    double num;
    while (true)
    {
        
        if (fscanf(fp, "%lf", &num) != EOF)
        {   
            vectorSize ++;
        } else
        {
            // EOF reached
            break;
        }
    }
    fclose(fp);
    
    // Save data to vector known length
    fp = fopen(filePath, "r");
    initVector(vec, vectorSize);
    for (size_t i=0; i<vectorSize; i++)
    {   
        fscanf(fp, "%lf", &num);
        vec->data[i] = num;
    }
}

void randomVector(Vector* vec, int size, double min, double max)
{
    initVector(vec, size);

    for (int i=0; i<vec->size; i++) 
    {
        vec->data[i] = randomDouble(min, max);
    }
}

double calcNorm(const Vector *vec, int p)
//TODO: better handle Lp inf norm
{
    double sum = 0.0;

    for (size_t i = 0; i < vec->size; i++)
    {
        sum += pow(fabs(vec->data[i]), p);
    }

    if (!isinf(sum))
    {
        return pow(sum, 1.0 / (double)p);

    } else
    {
        fprintf(stderr, "Lp-inf was Computed assuming the high p-value of input!\n");
        return findAbsMax(vec);
    }
}

void invertSign(Vector* vec)
{
    if (!_checkInitVector(vec))
    {
        fprintf(stderr, "Vector is not initialized, exiting...\n");
        exit(EXIT_FAILURE);
    }
    for (size_t i=0; i<vec->size; i++)
    {
        vec->data[i] = -1 * vec->data[i];
    }
}

void multiplyByScalar(Vector* vec, double scalar)
{
    if (!_checkInitVector(vec))
    {
        fprintf(stderr, "Vector is not initialized, exiting...\n");
        exit(EXIT_FAILURE);
    }
    for (size_t i=0; i<vec->size; i++)
    {
        vec->data[i] = scalar * vec->data[i];
    }
}

void addVectors(Vector *vec1, Vector *vec2, Vector *result)
{
    // Algebraic sum of two vectors
    if ((vec1->size != vec2->size) || ((vec1->size != result->size)))
    {
        fprintf(stderr, "Vector are incompatible in size");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < vec1->size; i++)
    {
        result->data[i] = vec1->data[i] + vec2->data[i];
    }
}

void substractVectors(Vector *vec1, Vector *vec2, Vector *result)
{
    if ((vec1->size != vec2->size) || ((vec1->size != result->size)))
    {
        fprintf(stderr, "Vector are incompatible in size");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < vec1->size; i++)
    {
        result->data[i] = vec1->data[i] - vec2->data[i];
    }
}

double scalarProduct(Vector *vec1, Vector *vec2)
{
    if (vec1->size != vec2->size)
    {
        fprintf(stderr, "Vector are incompatible in size");
        exit(EXIT_FAILURE);
    }

    double result = 0.0;
    for (size_t i = 0; i < vec1->size; i++)
    {
        result += vec1->data[i] * vec2->data[i];
    }

    return result;
}

double findMax(Vector* vec) 
{
    _checkInitVector(vec);
    double max = vec->data[0];
    for (size_t i=1; i<vec->size; i++)  
    {
        if (vec->data[i]>max)
        {
            max = vec->data[i];
        }
    }

    return max;
}

double findAbsMax(Vector* vec)
{
    _checkInitVector(vec);
    double abs_max = fabs(vec->data[0]);
    for (size_t i=1; i<vec->size; i++)  
    {
        if (fabs(vec->data[i])>abs_max)
        {
            abs_max = vec->data[i];
        }
    }

    return abs_max;
}

double findMin(Vector* vec) 
{
    _checkInitVector(vec);
    double min = vec->data[0];
    for (size_t i=1; i<vec->size; i++)  
    {
        if (vec->data[i]<min)
        {
            min = vec->data[i];
        }
    }

    return min;
}

double findAbsMin(Vector* vec)
{
    _checkInitVector(vec);
    double abs_min = fabs(vec->data[0]);
    for (size_t i=0; i<vec->size; i++)  
    {
        if (fabs(vec->data[i])<fabs(vec->data[i]))
        {
            abs_min = vec->data[i];
        }
    }

    return abs_min;
}
