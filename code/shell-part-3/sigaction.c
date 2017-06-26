#include <stdio.h>
#include <signal.h>
#include <setjmp.h>
#include <unistd.h>

static sigjmp_buf env;
static volatile sig_atomic_t jump_active = 0;

void sigint_handler(int signo) {
    if (!jump_active) {
        return;
    }
    siglongjmp(env, 42);
}

int main() {
    struct sigaction s;
    s.sa_handler = sigint_handler;
    sigemptyset(&s.sa_mask);
    s.sa_flags = SA_RESTART;
    sigaction(SIGINT, &s, NULL);

    while (1){                  /* Infinite loop */
        if (sigsetjmp(env, 1) == 42) {
            printf("Restart.\n");
        }
        jump_active = 1;        /* Set the flag */
        printf("next iteration...\n");
        sleep(2);
    }
}
