/*Matrix math class Header*/
#ifndef LINSYS
#define LINSYS

#include "Vector.h"
#include "Matrix.h"
#include <math.h>

typedef struct LinearSystem
{
    Vector* vec;
    Matrix* mat;
    size_t size;
} LinearSystem;

void initLinSys(LinearSystem* linsys, Matrix* mat, Vector* vec);
#endif
