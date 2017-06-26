#include <stdio.h>
#include <signal.h>
#include <setjmp.h>
#include <unistd.h>

static jmp_buf env;

void sigint_handler(int signo) {
    longjmp(env, 42);
}

int main() {
    signal(SIGINT, sigint_handler);
    while (1){                  /* Infinite loop */
        if (setjmp(env) == 42) {
            printf("Restart.\n");
        }
        printf("next iteration...\n");
        sleep(2);
    }
}
