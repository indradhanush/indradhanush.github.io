#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <setjmp.h>

char **get_input(char *);
int cd(char *);
void sigint_handler(int);

static sigjmp_buf env;
static volatile sig_atomic_t jump_active = 0;

int main() {
    char **command;
    char *input;
    pid_t child_pid;
    int stat_loc;

    /* Setup SIGINT */
    struct sigaction s;
    s.sa_handler = sigint_handler;
    sigemptyset(&s.sa_mask);
    s.sa_flags = SA_RESTART;
    sigaction(SIGINT, &s, NULL);

    while (1) {
        if (sigsetjmp(env, 1) == 42) {
            printf("\n");
            continue;
        }

        jump_active = 1;

        input = readline("unixsh> ");
        if (input == NULL) {  /* Exit on Ctrl-D */
            printf("\n");
            exit(0);
        }

        command = get_input(input);

        if (!command[0]) {      /* Handle empty commands */
            free(input);
            free(command);
            continue;
        }

        if (strcmp(command[0], "cd") == 0) {
            if (cd(command[1]) < 0) {
                perror(command[1]);
            }

            /* Skip the fork */
            continue;
        }

        child_pid = fork();
        if (child_pid < 0) {
            perror("Fork failed");
            exit(1);
        }

        if (child_pid == 0) {
            struct sigaction s_child;
            s_child.sa_handler = sigint_handler;
            sigemptyset(&s_child.sa_mask);
            s_child.sa_flags = SA_RESTART;
            sigaction(SIGINT, &s_child, NULL);

            /* Never returns if the call is successful */
            if (execvp(command[0], command) < 0) {
                perror(command[0]);
                exit(1);
            }
        } else {
            waitpid(child_pid, &stat_loc, WUNTRACED);
        }

        if (!input)
            free(input);
        if (!command)
            free(command);
    }

    return 0;
}

char **get_input(char *input) {
    char **command = malloc(8 * sizeof(char *));
    if (command == NULL) {
        perror("malloc failed");
        exit(1);
    }

    char *separator = " ";
    char *parsed;
    int index = 0;

    parsed = strtok(input, separator);
    while (parsed != NULL) {
        command[index] = parsed;
        index++;

        parsed = strtok(NULL, separator);
    }

    command[index] = NULL;
    return command;
}

int cd(char *path) {
    return chdir(path);
}

void sigint_handler(int signo) {
    if (!jump_active) {
        return;
    }
    siglongjmp(env, 42);
}
