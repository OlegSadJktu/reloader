#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>


int main(int argc, char **argv) {
    if (argc < 2) {
        printf("No such args\n");
        exit(1);
    }

    struct termios attrs;
    tcgetattr(STDIN_FILENO, &attrs);
    attrs.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &attrs);
    char c = 0;
    char *args[argc];
    /* args[0] = argv[1]; */

    for (int i = 0; i < argc; i++) {
        args[i] = argv[i + 1];
    }
    args[argc-1] = NULL;
    int pid = 0;

    do {
        printf("Press 'r' for reload program\n");
        if (c == 'r') {
            if (pid != 0) {
                kill(pid, SIGKILL);
                wait(NULL);
            }
            pid = fork();
            if (pid == 0) {
                execvp(argv[1], args);
                perror("execvp");
                exit(1);
            } 
        }
    } while ((c = getchar()));

}
