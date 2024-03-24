#include "SecondOrderOde.h"

void initSecondOrderOde(
    SecondOrderOde* ode,
    double coeffTxx, double coeffTx, double coeffT,
    double (*rhsFunc)(double),
    double xMin, double xMax)
{
    ode->coeffTxx = coeffTxx;
    ode->coeffTx = coeffTx;
    ode->coeffT = coeffT;
    ode->rhsFunc = rhsFunc;
    ode->xMin = xMin;
    ode->xMax = xMax;
}