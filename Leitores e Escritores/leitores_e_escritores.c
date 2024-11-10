#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int read_count = 0;
int write_count = 0;
int data = 0;

void *reader(void *arg) {
    int num = *((int *)arg);

    pthread_mutex_lock(&mutex);
    while (write_count > 0) {
        pthread_cond_wait(&cond, &mutex);
    }
    read_count++;
    pthread_mutex_unlock(&mutex);

    printf("Reader %d: read data = %d\n", num, data);

    pthread_mutex_lock(&mutex);
    read_count--;
    if (read_count == 0) {
        pthread_cond_signal(&cond);
    }
    pthread_mutex_unlock(&mutex);

    return NULL;
}

void *writer(void *arg) {
    int num = *((int *)arg);

    pthread_mutex_lock(&mutex);
    while (read_count > 0 || write_count > 0) {
        pthread_cond_wait(&cond, &mutex);
    }
    write_count++;
    pthread_mutex_unlock(&mutex);

    data++;
    printf("Writer %d: wrote data = %d\n", num, data);

    pthread_mutex_lock(&mutex);
    write_count--;
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main() {
    pthread_t readers[5], writers[5];
    int thread_nums[5];

    for (int i = 0; i < 5; i++) {
        thread_nums[i] = i;
        pthread_create(&readers[i], NULL, reader, &thread_nums[i]);
        pthread_create(&writers[i], NULL, writer, &thread_nums[i]);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(readers[i], NULL);
        pthread_join(writers[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}