#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <math.h>
#include "src/functions.h"
#include "src/parser.h"

int PRINT_ITERATIONS = 0;

extern double function1(double x);
extern double function1_derivative(double x);
extern double function2(double x);
extern double function2_derivative(double x);
extern double function3(double x);
extern double function3_derivative(double x);

int main(int argc, char *argv[])
{
   int print_root = 0; // flag to print roots
   const struct option long_option[] = {{"help", no_argument, NULL, 'h'},
                                        {"root", no_argument, NULL, 'r'},
                                        {"iterations", no_argument, NULL, 'i'},
                                        {"test-root", required_argument, NULL, 'R'},
                                        {"test-integral", required_argument, NULL, 'I'},
                                        {NULL, 0, NULL, 0}};
   int opt;
   int option_index;
   while ((opt = getopt_long(argc, argv, "hriR:I:", long_option, &option_index)) != -1)
   {
      switch (opt)
      {
      case '?':
         printf("Unknown option.\n");
         exit(1);
      case 'h':
         printf("--help or -h for get info\n");
         printf("--root or -r for get intersection with abscissa\n");
         printf("--iterations or -i for get count iterations to get root\n");
         printf("--test-root or -R F1:F2:A:B:E:R for test root function. F1 and F2 number of test function. ");
         printf("[A, B] line segment with root, E - eps, R - true ansver\n");
         printf("--test-integral or -I F:A:B:E:R for test root function. F1 number of test function. ");
         printf("[A, B] integral segment, E - eps, R - true ansver\n");
         exit(0);
      case 'R':
         struct root_test_data data = parse_root(optarg);
         double my_ans = root(data.f, data.g, data.f_d, data.g_d, data.left, data.right, data.eps);
         if (data.ans - data.eps <= my_ans && data.ans + data.eps >= my_ans)
         {
            printf("YES\n");
         }
         exit(0);
      case 'I':
         struct integral_test_data data1 = parse_integral(optarg);
         double my_ans1 = integral(data1.f, data1.left, data1.right, data1.eps);
         if (data1.ans - data1.eps <= my_ans1 && data1.ans + data1.eps >= my_ans1)
         {
            printf("YES\n");
         }
         exit(0);
      case 'r':
         print_root = 1;
      case 'i':
         PRINT_ITERATIONS = 1;
      }
   }

   double left = root(function1, function3, function1_derivative, function3_derivative, 0.8, 2, 0.000001);
   double right = root(function1, function2, function1_derivative, function2_derivative, 3, 4, 0.000001);
   double mid = root(function2, function3, function2_derivative, function3_derivative, 3, 4, 0.000001);
   if (print_root)
   {
      printf("We have three roots: %.6lf\t%.6lf\t%.6lf\n", left, mid, right);
   }
   double line_integral = integral(function1, left, right, 0.00001);
   double under_line = integral(function3, left, right, 0.00001);
   double right_part = integral(function2, mid, right, 0.00001);
   line_integral -= under_line + right_part;
   printf("%.6lf\n", line_integral);
   return 0;
}
