#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Cabeçalho necessário para a função sleep

pthread_mutex_t lock1;
pthread_mutex_t lock2;

// Função executada pela primeira thread
void *thread1_func(void *arg) {
    pthread_mutex_lock(&lock1);
    printf("Thread 1: locked lock1\n");

    sleep(1);  // Simula algum trabalho

    printf("Thread 1: trying to lock lock2\n");
    pthread_mutex_lock(&lock2);
    printf("Thread 1: locked lock2\n");

    // Seção crítica
    pthread_mutex_unlock(&lock2);
    pthread_mutex_unlock(&lock1);

    return NULL;
}

// Função executada pela segunda thread
void *thread2_func(void *arg) {
    pthread_mutex_lock(&lock2);
    printf("Thread 2: locked lock2\n");

    sleep(1);  // Simula algum trabalho

    printf("Thread 2: trying to lock lock1\n");
    pthread_mutex_lock(&lock1);
    printf("Thread 2: locked lock1\n");

    // Seção crítica
    pthread_mutex_unlock(&lock1);
    pthread_mutex_unlock(&lock2);

    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Inicializa os mutexes
    pthread_mutex_init(&lock1, NULL);
    pthread_mutex_init(&lock2, NULL);

    // Cria as threads
    pthread_create(&thread1, NULL, thread1_func, NULL);
    pthread_create(&thread2, NULL, thread2_func, NULL);

    // Espera que as threads terminem
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Destrói os mutexes
    pthread_mutex_destroy(&lock1);
    pthread_mutex_destroy(&lock2);

    return 0;
}