#ifndef FUNCTION_HEADER
#define FUNCTION_HEADER

extern int PRINT_ITERATIONS;
typedef double afunc(double);
double F(afunc *f, afunc *g, double x);
double root(afunc *f, afunc *g, afunc *f_d, afunc *g_d, double a, double b, double eps1);
double integral(afunc *f, double a, double b, double eps2);
#endif