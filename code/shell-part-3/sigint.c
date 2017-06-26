#include <stdio.h>
#include <signal.h>

void sigint_handler(int signo) {
    printf("Caught SIGINT\n");
}

int main() {
    signal(SIGINT, sigint_handler);
    while (1);                  /* Infinite loop */
}
