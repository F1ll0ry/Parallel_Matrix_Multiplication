#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MAX_THREADS 8

int rows_a, cols_a, rows_b, cols_b, rows_c, cols_c;
int **matrix_a, **matrix_b, **result_matrix;

void *multiply(void *thread_arg) {
    int tid = *((int*)thread_arg);
    int i, j, k;

    int start = tid * rows_c / MAX_THREADS;
    int end = (tid + 1) * rows_c / MAX_THREADS;

    for (i = start; i < end; i++) {
        for (j = 0; j < cols_c; j++) {
            result_matrix[i][j] = 0;
            for (k = 0; k < cols_a; k++) {
                result_matrix[i][j] += matrix_a[i][k] * matrix_b[k][j];
            }
        }
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    int i, j;
    int thread_id[MAX_THREADS];
    pthread_t threads[MAX_THREADS];

    clock_t start_time, end_time;
    double elapsed_time;

    start_time = clock();

    printf("Enter the dimensions of matrix A (row column): ");
    scanf("%d %d", &rows_a, &cols_a);

    matrix_a = (int**)malloc(rows_a * sizeof(int*));
    printf("Enter the elements of matrix A:\n");
    for (i = 0; i < rows_a; i++) {
        matrix_a[i] = (int*)malloc(cols_a * sizeof(int));
        for (j = 0; j < cols_a; j++) {
            scanf("%d", &matrix_a[i][j]);
        }
    }

    printf("Enter the dimensions of matrix B (row column): ");
    scanf("%d %d", &rows_b, &cols_b);

    matrix_b = (int**)malloc(rows_b * sizeof(int*));
for (i = 0; i < rows_b; i++) {
matrix_b[i] = (int*)malloc(cols_b * sizeof(int));
printf("Enter the elements of row %d of matrix B:\n", i+1);
for (j = 0; j < cols_b; j++) {
scanf("%d", &matrix_b[i][j]);
}
}
if (cols_a != rows_b) {
    printf("Error: The number of columns of matrix A must be equal to the number of rows of matrix B.\n");
    return 0;
}

rows_c = rows_a;
cols_c = cols_b;

result_matrix = (int**)malloc(rows_c * sizeof(int*));
for (i = 0; i < rows_c; i++) {
    result_matrix[i] = (int*)malloc(cols_c * sizeof(int));
}

for (i = 0; i < MAX_THREADS; i++) {
    thread_id[i] = i;
    pthread_create(&threads[i], NULL, multiply, (void*)&thread_id[i]);
}

for (i = 0; i < MAX_THREADS; i++) {
    pthread_join(threads[i], NULL);
}

end_time = clock();
elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

printf("Resultant matrix C:\n");
for (i = 0; i < rows_c; i++) {
    for (j = 0; j < cols_c; j++) {
        printf("%d ", result_matrix[i][j]);
    }
    printf("\n");
}

printf("Time taken to compute the multiplication: %lf seconds\n", elapsed_time);

for (i = 0; i < rows_a; i++) {
    free(matrix_a[i]);
}
free(matrix_a);

for (i = 0; i < rows_b; i++) {
    free(matrix_b[i]);
}
free(matrix_b);

for (i = 0; i < rows_c; i++) {
    free(result_matrix[i]);
}
free(result_matrix);

return 0;
}
