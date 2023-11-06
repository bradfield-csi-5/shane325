#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

void* routine(void* arg) {
    sleep(1);
    int index = *(int*)arg;
    printf("Index: %d ", index);
    printf("Value: %d ", primes[index]);
    return NULL;
}

int main() {
    pthread_t th[10];

    for (int i = 0; i < 10; i++) {
        printf("%d\n", i);
        if (pthread_create(&th[i], NULL, &routine, &i) != 0) {
            fprintf(stderr, "Error: failed to create thread");
        }
    }

    for (int i = 0; i < 10; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            fprintf(stderr, "Error: failed to join thread");
        }
    }

    return 0;
}
