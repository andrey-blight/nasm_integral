#ifndef PARSER_HEADER
#define PARSER_HEADER

#include "functions.h"
#include "../test/test.h"

struct root_test_data
{
    afunc *f;
    afunc *g;
    afunc *f_d;
    afunc *g_d;
    double left;
    double right;
    double eps;
    double ans;
};
struct integral_test_data
{
    afunc *f;
    double left;
    double right;
    double eps;
    double ans;
};

struct root_test_data parse_root(const char *string);
struct integral_test_data parse_integral(const char *string);

#endif