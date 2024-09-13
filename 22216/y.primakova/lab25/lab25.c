#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

int main() {
    int fd[2];
    if (pipe(fd) == -1) {
        perror("Pipe fail.");
        exit(1);
    }
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork fail.");
        exit(1);
    } 
    if (pid == 0) {
        close(fd[0]);
        char buff[BUFSIZ];
        ssize_t size;
        while ((size = read(0, buff, BUFSIZ)) > 0) {
            if (write(fd[1], buff, size) == -1) {
                perror("Write fail.");
                exit(1);
            }
        }
        if (size == -1) {
            perror("Read fail.");
            exit(1);
        }
        close(fd[1]);
    } else {
        close(fd[1]);
        char buff[BUFSIZ];
        ssize_t size;
        while ((size = read(fd[0], buff, BUFSIZ)) > 0) {
            for(int i = 0; i < size; i++) {
                putchar(toupper(buff[i]));
            }
        }
        if (size == -1) {
            perror("Read fail.");
            exit(1);
        }
        close(fd[0]);
    }
    return 0;
}
