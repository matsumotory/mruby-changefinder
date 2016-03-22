// create simulation data created by ar moder, White noise and change point
// parameter
// gcc -lm ar.c -o ar
// ./ar number_of_data ar1_coeff ar2_coeff change_point_time change_point_total
// change_point_decrease expected_value_for_white_noise
// variance_value_white_noise
// ./ar 10000 0.6 0.5 5.0 0.5 0.0 1.0

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

static double white_noise(double ex, double sigma)
{
  int i;
  double r;

  while (1) {
    r = (double)rand() / RAND_MAX;
    if (1.0 / sqrt(2 * M_PI * sigma) * exp(-(r - ex) * (r - ex) / 2.0 / sigma / sigma) >= (double)rand() / RAND_MAX)
      break;
  }

  return r;
}

int main(int argc, char **argv)
{

  int k, t, s;
  double *x, *z, *a, *e, *u;

  // the number of time series data
  int max_points = 10000;
  int outlier_point;

  // ar coefficient parameter
  double ar1_coeff = 0.6;
  double ar2_coeff = 0.5;

  // change point params
  int change_point_time = 1000;
  double expected_change_total = 5.0;
  double decrease_change_value = 0.5;

  // white noise params
  double expected_value = 0.0;
  double variance_value = 1.0;

  srand((unsigned)time(NULL));
  outlier_point = rand() % max_points;

  if (argc != 9) {
    fprintf(stderr, "Usage : %s number_of_data ar1_coeff ar2_coeff "
                    "change_point_time change_point_total "
                    "change_point_decrease expected_value_for_white_noise "
                    "variance_value_white_noise\n",
            argv[0]);
    exit(1);
  }

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

  // ar coefficient order
  k = 2;

  // the number of time series data
  max_points = atoi(argv[1]);
  ar1_coeff = atof(argv[2]);
  ar2_coeff = atof(argv[3]);
  change_point_time = atoi(argv[4]);
  expected_change_total = atof(argv[5]);
  decrease_change_value = atof(argv[6]);
  expected_value = atof(argv[7]);
  variance_value = atof(argv[8]);

  // setup ar coefficient
  a[0] = 0;
  a[1] = ar1_coeff;
  a[2] = ar2_coeff;

  // Change Points Initial Value
  u[0] = expected_change_total;

  t = 1;
  s = 1;

  while (t <= max_points) {
    if (t > 2) {
      u[t] = u[t - 1];
      e[t] = white_noise(expected_value, variance_value);
      z[t] = a[1] * z[t - 1] - a[2] * z[t - 2] + e[t];
      x[t] = z[t] + u[t];

      // Change Points Create Rull
      if (t == change_point_time * s) {
        u[t] += u[0] - decrease_change_value;
        u[0] -= decrease_change_value;
        s++;
      }

    } else {
      u[t] = u[t - 1];
      e[t] = white_noise(expected_value, variance_value);
      x[t] = e[t];
    }

    if (t == outlier_point) {
      printf("% lf\n", x[t] + expected_change_total);
    } else {
      printf("% lf\n", x[t]);
    }
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
