#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 1000
#define N 1000

int main(int argc, char** argv) {
  int i, j, k;
  double start_time, end_time;
  double** a = (double**)malloc(M * sizeof(double*));
  double** b = (double**)malloc(N * sizeof(double*));
  double** c = (double**)malloc(M * sizeof(double*));
  for (i = 0; i < M; i++) {
    a[i] = (double*)malloc(N * sizeof(double));
    c[i] = (double*)malloc(N * sizeof(double));
    for (j = 0; j < N; j++) {
      a[i][j] = i + j;
      c[i][j] = 0.0;
    }
  }
  for (i = 0; i < N; i++) {
    b[i] = (double*)malloc(M * sizeof(double));
    for (j = 0; j < M; j++) {
      b[i][j] = i + j;
    }
  }

  start_time = (double) clock() / CLOCKS_PER_SEC;
  for (i = 0; i < M; i++) {
    for (j = 0; j < N; j++) {
      for (k = 0; k < M; k++) {
        c[i][j] += a[i][k] * b[j][k];
      }
    }
  }
  end_time = (double) clock() / CLOCKS_PER_SEC;
  printf("Elapsed time = %lf seconds\n", end_time - start_time);

  for (i = 0; i < M; i++) {
    free(a[i]);
    free(c[i]);
  }
  for (i = 0; i < N; i++) {
    free(b[i]);
  }
  free(a);
  free(b);
  free(c);
  return 0;
}
