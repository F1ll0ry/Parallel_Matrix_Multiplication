/**
 * Matrix (N*N) multiplication with a single thread.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
double ** allocate_matrix( int size )
{
  /* Allocate 'size' * 'size' doubles contiguously. */
  double * vals = (double *) malloc( size * size * sizeof(double) );

  /* Allocate array of double* with size 'size' */
  double ** ptrs = (double **) malloc( size * sizeof(double*) );

  int i;
  for (i = 0; i < size; ++i) {
    ptrs[ i ] = &vals[ i * size ];
  }

  return ptrs;
}

void init_matrix( double **matrix, int size )
{
  int i, j;

  for (i = 0; i < size; ++i) {
    for (j = 0; j < size; ++j) {
      matrix[ i ][ j ] = 1.0;
    }
  }
}

void print_matrix( double **matrix, int size )
{
  int i, j;

  for (i = 0; i < size; ++i) {
    for (j = 0; j < size-1; ++j) {
      printf( "%lf, ", matrix[ i ][ j ] );
    }
    printf( "%lf", matrix[ i ][ j ] );
    putchar( '\n' );
  }
}

int main( int argc, char *argv[] )
{
  double **matrix1, **matrix2, **matrix3;
  int size, i, j, k;
  double sum = 0;
   clock_t start_time, end_time;
    double elapsed_time;

    start_time = clock();

  if (argc != 2) {
    fprintf( stderr, "%s <matrix size>\n", argv[0] );
    return -1;
  }

  size = atoi( argv[1] );

  matrix1 = allocate_matrix( size );
  matrix2 = allocate_matrix( size );
  matrix3 = allocate_matrix( size );
  
  init_matrix( matrix1, size );
  init_matrix( matrix2, size );

  if ( size <= 10 ) {
    printf( "Matrix 1:\n" );
    print_matrix( matrix1, size );
    printf( "Matrix 2:\n" );
    print_matrix( matrix2, size );
  }

  for (i = 0; i < size; ++i) { // hold row index of 'matrix1'
    for (j = 0; j < size; ++j) { // hold column index of 'matrix2'
      sum = 0; // hold value of a cell
      /* one pass to sum the multiplications of corresponding cells
	 in the row vector and column vector. */
      for (k = 0; k < size; ++k) { 
	sum += matrix1[ i ][ k ] * matrix2[ k ][ j ];
      }
      matrix3[ i ][ j ] = sum;
    }
  }
end_time = clock();
elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
  
  if ( size <= 10 ) {
    printf( "Matrix 3:\n" );
    print_matrix( matrix1, size );
  }

 
 
printf("Time taken to compute the multiplication: %lf seconds\n", elapsed_time);
  return 0;
}
