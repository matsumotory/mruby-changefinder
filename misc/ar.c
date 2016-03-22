// create simulation data created by ar moder, White noise and change point
// parameter
// gcc -lm ar.c -o ar
// ./ar number_of_data ar1_coeff ar2_coeff change_point_total
// ./ar 10000 0.6 0.5 5.0

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

static double white_noise(double ex, double sigma) {
  int i;
  double r;

  while (1) {
    r = (double)rand() / RAND_MAX;
    if (1.0 / sqrt(2 * M_PI * sigma) *
            exp(-(r - ex) * (r - ex) / 2.0 / sigma / sigma) >=
        (double)rand() / RAND_MAX)
      break;
  }

  return r;
}

int main(int argc, char **argv) {

  int k, t, s, max_points;
  double *x, *z, *a, *e, *u;

  // change point params
  double expected_change_total = 5.0;
  double decrease_change_value = 0.5;

  // white noise params
  double expected_value = 0.0;
  double variance_value = 1.0;

  if (argc != 5) {
    fprintf(stderr, "Usage : %s number_of_data ar1_coeff ar2_coeff change_point_total\n",
            argv[0]);
    exit(1);
  }

  // ar coefficient order
  k = 2;

  // the number of time series data
  max_points = atoi(argv[1]);

  if ((x = (double *)malloc((max_points + 1) * sizeof(double))) == NULL)
    goto MALLOC_ERROR;
  if ((z = (double *)malloc((max_points + 1) * sizeof(double))) == NULL)
    goto MALLOC_ERROR;
  if ((a = (double *)malloc((k + 1) * sizeof(double))) == NULL)
    goto MALLOC_ERROR;
  if ((e = (double *)malloc((max_points + 1) * sizeof(double))) == NULL)
    goto MALLOC_ERROR;
  if ((u = (double *)malloc((max_points + 1) * sizeof(double))) == NULL)
    goto MALLOC_ERROR;

  t = 1;
  s = 1;

  // setup ar coefficient
  a[0] = 0;
  a[1] = atof(argv[2]);
  a[2] = atof(argv[3]);

  // Change Points Initial Value
  expected_change_total = atof(argv[4]);
  u[0] = expected_change_total;

  while (t <= max_points) {
    if (t > 2) {
      u[t] = u[t - 1];
      e[t] = white_noise(expected_value, variance_value);
      z[t] = a[1] * z[t - 1] - a[2] * z[t - 2] + e[t];
      x[t] = z[t] + u[t];

      // Change Points Create Rull
      if (t == 1000 * s) {
        u[t] += u[0] - decrease_change_value;
        u[0] -= decrease_change_value;
        s++;
      }
    } else {
      u[t] = u[t - 1];
      e[t] = white_noise(expected_value, variance_value);
      x[t] = e[t];
    }

    printf("% lf\n", x[t]);
    t++;
  }

  free(x);
  free(z);
  free(a);
  free(e);
  free(u);

  return 0;

MALLOC_ERROR:
  fprintf(stderr, "Unable to malloc memory – fatal !\n");
  exit(-1);
}
