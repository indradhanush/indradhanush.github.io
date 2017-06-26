#include <stdio.h>
#include <signal.h>
#include <setjmp.h>
#include <unistd.h>

static sigjmp_buf env;

void sigint_handler(int signo) {
    siglongjmp(env, 42);
}

int main() {
    signal(SIGINT, sigint_handler);
    while (1){                  /* Infinite loop */
        if (sigsetjmp(env, 1) == 42) {
            printf("Restart.\n");
        }
        printf("next iteration...\n");
        sleep(2);
    }
}
