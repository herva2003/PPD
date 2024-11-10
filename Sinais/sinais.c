#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Handler para o sinal SIGUSR1 no processo filho
void handle_signal(int signal) {
    if (signal == SIGUSR1) {
        printf("Child process received SIGUSR1 signal (%d)\n", signal);
    }
}

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Processo filho
        signal(SIGUSR1, handle_signal);

        printf("Child process waiting for SIGUSR1 signal\n");

        while (1) {
            sleep(1);  // Espera indefinidamente
        }
    } else { // Processo pai
        sleep(2);  // Espera antes de enviar o sinal

        printf("Parent process sending SIGUSR1 signal to child process\n");
        kill(pid, SIGUSR1);  // Envia o sinal SIGUSR1 para o processo filho

        wait(NULL);  // Espera que o processo filho termine
        printf("Child process exited\n");
    }

    return 0;
}