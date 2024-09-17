#include "functions.h"
#include <stdio.h>

// count f(x) - g(x)
double F(afunc *f, afunc *g, double x)
{
    return f(x) - g(x);
}

// Find root f(x) = g(x) at [a, b] with accuracy eps1
double root(afunc *f, afunc *g, afunc *f_d, afunc *g_d, double a, double b, double eps1)
{
    if (PRINT_ITERATIONS)
    {
        printf("Start root function.\n");
    }
    // F = f(x) - g(x)
    short F_d_positiv = (F(f, g, a) < 0);                                        // F`(x) > 0
    short F_d2_positiv = (F(f, g, (a + b) / 2) < (F(f, g, a) + F(f, g, b)) / 2); // F``(x) > 0

    short left; // side of approach
    double d;   // base value
    if ((F_d_positiv && F_d2_positiv) || (!F_d_positiv && !F_d2_positiv))
    {
        d = b;
        left = 0;
    }
    else
    {
        d = a;
        left = 1;
    }

    int count_iterations = 0; // how many iterations need to find root
    double c, val, eps_val;
    while (1)
    {
        c = d - F(f, g, d) / F(f_d, g_d, d);
        val = F(f, g, c);
        eps_val;
        if (left)
        {
            eps_val = F(f, g, c + eps1);
        }
        else
        {
            eps_val = F(f, g, c - eps1);
        }
        ++count_iterations;                                       // count iteration += 1
        if ((val > 0 && eps_val < 0) || (val < 0 && eps_val > 0)) // if point near root break
        {
            break;
        }
        d = c;
    }
    if (PRINT_ITERATIONS)
    {
        printf("Find root for %i iterations\n", count_iterations);
    }
    return c;
}

// Count integral f(x) from a to b with accuracy eps2
double integral(afunc *f, double a, double b, double eps2)
{
    int n = 20; // count of interations
    int i = 0;
    double h = (b - a) / n;

    double In = 0;
    double sum_for_next = 0; // sum that will be included in any I
    for (int i = 0; i <= n; i++)
    {
        double F_i = f(a + i * h);
        if (i == 0 || i == n) // 0.5F_0 and 0.5F_n included in In_sum and in I2n_sum
        {
            F_i /= 2;
        }
        sum_for_next += F_i;
        In += F_i;
    }
    In *= h; // We calculated In

    double I2n = 0;
    while (1)
    {
        I2n = sum_for_next;
        n *= 2;
        h = (b - a) / n;
        // Calculate I2n. We already have sum of F_2i. Lets add odd index
        for (int i = 1; i <= n; i += 2)
        {
            double F_i = f(a + i * h);
            sum_for_next += F_i;
            I2n += F_i;
        }
        I2n *= h; // We calculated I2n

        double diff = In - I2n;
        if (diff < 0)
        {
            diff = -diff;
        }
        if (1 / 3 * diff < eps2) // we have accuracy eps
        {
            break;
        }
        In = I2n;
    }
    return I2n;
}