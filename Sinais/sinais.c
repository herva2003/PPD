#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

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

    if (pid == 0) {
        signal(SIGUSR1, handle_signal);

        printf("Child process waiting for SIGUSR1 signal\n");

        while (1) {
            sleep(1);
        }
    } else {
        sleep(2);

        printf("Parent process sending SIGUSR1 signal to child process\n");
        kill(pid, SIGUSR1);

        wait(NULL);
        printf("Child process exited\n");
    }

    return 0;
}