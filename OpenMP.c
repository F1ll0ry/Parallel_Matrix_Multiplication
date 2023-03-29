#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    int i, j, k;
    int m, n, p;
    double start_time, end_time, total_time;

    printf("Enter the dimensions of matrix A (m x n): ");
    scanf("%d %d", &m, &n);

    int **a = (int **) malloc(m * sizeof(int *));
    for (i = 0; i < m; i++) {
        a[i] = (int *) malloc(n * sizeof(int));
        printf("Enter row %d of matrix A: ", i+1);
        for (j = 0; j < n; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    printf("Enter the dimensions of matrix B (n x p): ");
    scanf("%d %d", &n, &p);

    int **b = (int **) malloc(n * sizeof(int *));
    for (i = 0; i < n; i++) {
        b[i] = (int *) malloc(p * sizeof(int));
        printf("Enter row %d of matrix B: ", i+1);
        for (j = 0; j < p; j++) {
            scanf("%d", &b[i][j]);
        }
    }

    int **c = (int **) malloc(m * sizeof(int *));
    for (i = 0; i < m; i++) {
        c[i] = (int *) malloc(p * sizeof(int));
    }

    start_time = omp_get_wtime();
omp_set_num_threads(8);

    #pragma omp parallel for private(i,j,k)
    for (i = 0; i < m; i++) {
        for (j = 0; j < p; j++) {
            int sum = 0;
            for (k = 0; k < n; k++) {
                sum += a[i][k] * b[k][j];
            }
            c[i][j] = sum;
        }
    }

    end_time =omp_get_wtime();
total_time = end_time - start_time;
printf("Resultant matrix C:\n");
for (i = 0; i < m; i++) {
    for (j = 0; j < p; j++) {
        printf("%d ", c[i][j]);
    }
    printf("\n");
}

printf("Time taken for multiplication: %lf seconds", total_time);

for (i = 0; i < m; i++) {
    free(a[i]);
}
free(a);

for (i = 0; i < n; i++) {
    free(b[i]);
}
free(b);

for (i = 0; i < m; i++) {
    free(c[i]);
}
free(c);

return 0;

}
