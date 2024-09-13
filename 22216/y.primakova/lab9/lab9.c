#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "There is no filename.");
        exit(1);
    }
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork fail.");
        exit(1);
    } 
    if (pid == 0) {
        execlp("cat", "cat", argv[1], (char*)0);
        perror("Execlp fail.");
        exit(1);
    } 
    int status;
    if (wait(&status) == -1) {
        perror("Wait fail.");
        exit(1);
    }
    if (WIFEXITED(status)) {
        printf("The child process terminated normally. The exit status of the child process: %d.\n", WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        printf("The child process was terminated by a signal. The number of the signal that caused the child process to terminate: %d.\n", WTERMSIG(status));
    }
    printf("The output of the parent process.");
    return 0;
}
