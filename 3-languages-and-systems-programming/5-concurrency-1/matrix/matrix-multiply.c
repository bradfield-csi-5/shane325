#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct ArgStruct {
  double  **c;
  double  **a;
  double  **b;
  // int     a_cols;
  // int     b_cols;
  int     k;
  int     j;
  int     i;
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
        printf("%d %d %d\n", i, j, k);
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
}

/**
void *inner_multiply(void *arguments) {
  struct arg_struct *args = arguments;
  for (int j = 0; j < args->b_cols; j++) {
    args->c[args->i][j] = 0;
    for (int k = 0; k < args->a_cols; k++) {
      args->c[args->i][j] += args->a[args->i][k] * args->b[k][j];
    }
  }
}
*/

void *final_multiply(void *arguments) {
  double **a, **b, **c;
  int k, j, i;
  // struct ArgStruct * my_args = (struct Args *) (arguments);
  struct ArgStruct * my_args;
  my_args = (struct ArgStruct*) (arguments);
  a = my_args->a;
  b = my_args->b;
  c = my_args->c;
  k = my_args->k;
  j = my_args->j;
  i = my_args->i;

  printf("Parr: %d %d %d\n", i, j, k);
  c[i][j] += a[i][k] * b[k][j];
  return NULL;
}

void parallel_matrix_multiply(double **c, double **a, double **b, int a_rows,
    int a_cols, int b_cols) {
  // pthread_t tid;
  // struct arg_struct args;
  // args.c = c;
  // args.a = a;
  // args.b = b;
  // args.a_cols = a_cols;
  // args.b_cols = b_cols;
  // for (int i = 0; i < a_rows; i++) {
  //   args.i = i;

  //   pthread_create(&tid, NULL, inner_multiply, (void *)&args);
  // }

  printf("\n\n\nStarting parallel:\n");
  pthread_t threads[a_cols];
  void * retvals[a_cols];
  // void * thread_arg_v;

  struct ArgStruct args;
  struct ArgStruct * args_address;
  args.a = a;
  args.b = b;
  args.c = c;
  for (int i = 0; i < a_rows; i++) {
    args.i = i;
    for (int j = 0; j < b_cols; j++) {
      args.j = j;
      c[i][j] = 0;
      int k;
      for (k = 0; k < a_cols; k++) {
        printf("Real: %d %d %d\n", i, j, k);
        args.k = k;
        args_address = &args;
        // thread_arg_v = (void *) 0;
        if (pthread_create(&threads[k], NULL, final_multiply, &args_address) != 0) {
          fprintf(stderr, "Error: Cannot create thread # %d\n", k);
          break;
        }
      }

      for (int i = 0; i < k; i++) {
        if (pthread_join(threads[i], &retvals[i]) != 0) {
          fprintf(stderr, "Error: Cannot join thread # %d\n", i);
        }
      }
    }
  }
}
