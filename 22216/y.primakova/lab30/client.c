#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>

int main() {
    struct sockaddr_un addr;
    char buf[BUFSIZ];
    ssize_t size;
    char *socketPath = "./socket";
    int socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (socket == -1) {
        perror("Socket fail.");
        exit(-1);
    }
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, socketPath);
    if (connect(socket, (struct addr*)&addr, sizeof(addr)) == -1) {
        perror("Connect fail.");
        exit(-1);
    }
    while ((size = read(0, buf, BUFSIZ)) > 0) {
        if (write(socket, buf, size) == -1) {
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
