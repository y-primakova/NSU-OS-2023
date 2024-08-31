#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

static int counter = 0;

void sigint(int sig) {
    write(STDOUT_FILENO, "\a", 1);
    counter++;    
}

void sigquit(int sig) {
    char buf[41];
    sprintf(buf, "\nThe sound was produced %d times", counter);
    write(STDOUT_FILENO, buf, strlen(buf));
    exit(-1);
}

int main() {
    if (sigset(SIGINT, sigint) == SIG_ERR) {
        perror("Fail to set SIGINT handler.");
        exit(-1);
    }
    if (sigset(SIGQUIT, sigquit) == SIG_ERR) {
        perror("Fail to set SIGQUIT handler.");
        exit(-1);
    }
    while (1) {}
}
