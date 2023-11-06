#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define THREAD_COUNT 10

struct ArgStruct {
  double  **a;
  double  **b;
  double  **c;
  int     a_rows;
  int     a_cols;
  int     b_cols;
  int     id;
};

/*
  A naive implementation of matrix multiplication.

  DO NOT MODIFY THIS FUNCTION, the tests assume it works correctly, which it
  currently does
*/
void matrix_multiply(double **C, double **A, double **B, int a_rows, int a_cols,
                     int b_cols) {
  for (int i = 0; i < a_rows; i++) {
    for (int j = 0; j < b_cols; j++) {
      C[i][j] = 0;
      for (int k = 0; k < a_cols; k++) {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
}

void *matrix_multiply_p(void *args) {
  double **a, **b, **c;
  int a_rows, a_cols, b_cols, id;
  struct ArgStruct * my_args;
  my_args = (struct ArgStruct*) (args);
  a = my_args->a;
  b = my_args->b;
  c = my_args->c;
  a_rows = my_args->a_rows;
  a_cols = my_args->a_cols;
  b_cols = my_args->b_cols;
  id = my_args->id;

  int l = id * (a_rows / THREAD_COUNT);
  int r = (id + 1) * (a_rows / THREAD_COUNT) -1;

  for (int i = l; i <= r; i++) {
    for (int j = 0; j < b_cols; j++) {
      c[i][j] = 0;
      for (int k = 0; k < a_cols; k++) {
        c[i][j] += a[i][k] * b[k][j];
      }
    }
  }
  free(args);
  return NULL;
}

void parallel_matrix_multiply(double **c, double **a, double **b, int a_rows,
    int a_cols, int b_cols) {

  int interval = a_rows / THREAD_COUNT;
  if (interval == 0) {
    interval = 1;
  } else if (interval > THREAD_COUNT) {
    interval = THREAD_COUNT;
  }
  printf("Interval: %d\n", interval);
  pthread_t threads[THREAD_COUNT];
  int t;

  for (t = 0; t < interval; t++) {
    struct ArgStruct* args = malloc(sizeof(struct ArgStruct));
    args->a = a;
    args->b = b;
    args->c = c;
    args->a_rows = a_rows;
    args->a_cols = a_cols;
    args->b_cols = b_cols;
    args->id = t;
    if (pthread_create(&threads[t], NULL, &matrix_multiply_p, args) != 0) {
      fprintf(stderr, "Error: Cannot create thread # %d \n", t);
    }
  }

  for (t = 0; t < interval; t++) {
    if (pthread_join(threads[t], NULL) != 0) {
      fprintf(stderr, "Error: Cannot join thread # %d\n", t);
    }
  }
}
