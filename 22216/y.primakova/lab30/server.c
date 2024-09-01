#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <ctype.h>

int main() {
    struct sockaddr_un addr;
    char buf[BUFSIZ];
    ssize_t size;
    char *socketPath = "./socket";
    int server_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket fail.");
        exit(-1);
    }
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, socketPath);
    if (bind(server_socket, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        perror("Bind fail.");
        exit(-1);
    }
    if (listen(server_socket, 1) == -1) {
        perror("Listen fail.");
        unlink(socketPath);
        exit(-1);
    }
    int client_socket = accept(server_socket, NULL, NULL);
    if (client_socket == -1) {
        perror("Accept fail.");
        unlink(socketPath);
        exit(-1);
    }
    unlink(socketPath);
    while ((size = read(client_socket, buf, BUFSIZ)) > 0) {
        for (int i = 0; i < size; i++) {
            buf[i] = toupper(buf[i]);
        }
        if (write(1, buf, size) == -1) {
            perror("Write fail.");
            exit(-1);
        }
    }
    if (size == -1) {
        perror("Read fail.");
        exit(-1);
    }

    return 0;
}
