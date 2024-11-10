#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 5

typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int count;
    int num_threads;
} barrier_t;

typedef struct {
    int thread_num;
    barrier_t *barrier;
} thread_args_t;

void barrier_init(barrier_t *barrier, int num_threads) {
    barrier->num_threads = num_threads;
    barrier->count = 0;
    pthread_mutex_init(&barrier->mutex, NULL);
    pthread_cond_init(&barrier->cond, NULL);
}

void barrier_wait(barrier_t *barrier) {
    pthread_mutex_lock(&barrier->mutex);
    barrier->count++;
    if (barrier->count == barrier->num_threads) {
        barrier->count = 0;
        printf("All threads reached the barrier. Broadcasting...\n");
        pthread_cond_broadcast(&barrier->cond);
    } else {
        while (pthread_cond_wait(&barrier->cond, &barrier->mutex) != 0);
    }
    pthread_mutex_unlock(&barrier->mutex);
}

void *thread_function(void *arg) {
    thread_args_t *args = (thread_args_t *)arg;
    int thread_num = args->thread_num;
    barrier_t *barrier = args->barrier;

    printf("Thread %d is waiting at the barrier\n", thread_num);
    barrier_wait(barrier);
    printf("Thread %d passed the barrier\n", thread_num);

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    thread_args_t thread_args[NUM_THREADS];
    barrier_t barrier;

    barrier_init(&barrier, NUM_THREADS);

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_args[i].thread_num = i;
        thread_args[i].barrier = &barrier;
        pthread_create(&threads[i], NULL, thread_function, &thread_args[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&barrier.mutex);
    pthread_cond_destroy(&barrier.cond);

    return 0;
}