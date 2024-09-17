#include "parser.h"
#include <stdlib.h>

double get_val(int start_index, const char *string, int *next_index)
{
    char val[20];
    for (int i = start_index; 1; i++)
    {
        if (string[i] == ':' || string[i] == '\0')
        {
            *next_index = i;
            break;
        }
        val[i - start_index] = string[i];
    }
    return atof(val);
}

struct root_test_data parse_root(const char *string)
{
    struct root_test_data resp;
    switch (string[0])
    {
    case '1':
        resp.f = test1;
        resp.f_d = test1_d;
        break;
    case '2':
        resp.f = test2;
        resp.f_d = test2_d;
        break;
    case '3':
        resp.f = test3;
        resp.f_d = test3_d;
        break;
    }
    switch (string[2])
    {
    case '1':
        resp.g = test1;
        resp.g_d = test1_d;
        break;
    case '2':
        resp.g = test2;
        resp.g_d = test2_d;
        break;
    case '3':
        resp.g = test3;
        resp.g_d = test3_d;
        break;
    }
    int next_index = 0;
    resp.left = get_val(4, string, &next_index);
    resp.right = get_val(next_index + 1, string, &next_index);
    resp.eps = get_val(next_index + 1, string, &next_index);
    resp.ans = get_val(next_index + 1, string, &next_index);
    return resp;
}
struct integral_test_data parse_integral(const char *string)
{
    struct integral_test_data resp;
    switch (string[0])
    {
    case '1':
        resp.f = test1;
        break;
    case '2':
        resp.f = test2;
        break;
    case '3':
        resp.f = test3;
        break;
    }
    int next_index = 0;
    resp.left = get_val(2, string, &next_index);
    resp.right = get_val(next_index + 1, string, &next_index);
    resp.eps = get_val(next_index + 1, string, &next_index);
    resp.ans = get_val(next_index + 1, string, &next_index);
    return resp;
}