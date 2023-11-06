#include <stdio.h>
#include <pthread.h>

#define NTHREADS 10

void *computation(void *add); // This function has to return a void pointer.

struct Pair {
    int i;
    int j;
};

int main() {
    pthread_t threads[NTHREADS];
    void * retvals[NTHREADS];
    int count_threads;
    // pthread_t thread1;
    // pthread_t thread2;

    // long value1 = 1;
    // long value2 = 2;

    for (count_threads = 0; count_threads < NTHREADS; count_threads++) {
        printf("%d\n", count_threads);
        if (pthread_create(&threads[count_threads], NULL, computation, &count_threads) != 0) {
            fprintf(stderr, "Error: Cannot create thread # %d\n", count_threads);
            break;
        }
    }

    for (int i = 0; i < count_threads; i++) {
        if (pthread_join(threads[i], &retvals[i]) != 0) {
            fprintf(stderr, "Error: Cannot join thread # %d\n", i);
        }
    }

    // computation((void *) &value1);
    // computation((void *) &value2);


    // pthread_create's fourth argument is expected to be a void pointer.
    // `(void *) &value1` => we are passing in the pointer to value 1 with `&value1` and we are casting that to a void pointer with `(void *)`.
    // It's a little bit of a roundabout way to pass in a value but it's a technique we can use.
    /*
    pthread_create(&thread1, NULL, computation, (void*) &value1);
    pthread_create(&thread2, NULL, computation, (void*) &value2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    */

    return 0;
}

void *computation(void *add) {
    // long sum = 0;
    int *add_num = (int *) (add); // Here we are taking in the void pointer, casting it to a long pointer, and assigning it to `long *add_num`. Now we have the actual value in `*add_num`.

    // for (long i = 0; i < 10; i++) {
    //     sum += *add_num;
    // }
    printf("Add %d.\n", *add_num);

    // Have to return something here.
    return NULL;
}
