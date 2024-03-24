#ifndef SECOND_ORDER_ODE
#define SECOND_ORDER_ODE

typedef struct SecondOrderOde
{
    // Coefficient on the LHS of the ODE
    double coeffTxx;
    double coeffTx;
    double coeffT;

    // Function on RHS ode
    double (*rhsFunc)(double x);

    // Interval for domain
    double xMin;
    double xMax;
} SecondOrderOde;

void initSecondOrderOde(
    SecondOrderOde* ode,
    double coeffTxx, double coeffTx, double coeffT,
    double (*rhsFunc)(double),
    double xMin, double xMax
    );

#endif