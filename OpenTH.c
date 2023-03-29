#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define M 1000
#define N 1000
#define NUM_THREADS 8

double a[M][N], b[N][M], c[M][N];
pthread_t threads[NUM_THREADS];
int block_size;

void* multiply(void* arg) {
  int thread_id = *(int*) arg;
  int start = thread_id * block_size;
  int end = start + block_size;
  for (int i = start; i < end; i++) {
    for (int j = 0; j < N; j++) {
      for (int k = 0; k < M; k++) {
        c[i][j] += a[i][k] * b[j][k];
      }
    }
  }
  pthread_exit(NULL);
}

int main(int argc, char** argv) {
  block_size = M / NUM_THREADS;
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      a[i][j] = i + j;
      c[i][j] = 0.0;
    }
  }
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      b[i][j] = i + j;
    }
  }
  struct timeval start_time, end_time;
  gettimeofday(&start_time, NULL);
  for (int i = 0; i < NUM_THREADS; i++) {
    int* thread_id = (int*) malloc(sizeof(int));
    *thread_id = i;
    pthread_create(&threads[i], NULL, multiply, thread_id);
  }
  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_join(threads[i], NULL);
  }
  gettimeofday(&end_time, NULL);
  double elapsed_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1000000.0;
  printf("Elapsed time = %lf seconds\n", elapsed_time);
  return 0;
}
