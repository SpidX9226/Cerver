#include <err.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define LISTEN_BACKLOG 50

#define PORT 8080
#define BUFFER_SIZE 4096

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    char buffer[BUFFER_SIZE];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd == -1) {
        err(EXIT_FAILURE, "socket");
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) ==
        -1) {
        err(EXIT_FAILURE, "bind");
    }

    if (listen(server_fd, LISTEN_BACKLOG) == -1) {
        err(EXIT_FAILURE, "listen");
    }

    const char *http_respone =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=UTF-8\r\n"
        "Connection: close\r\n"
        "\r\n"
        "<!DOCTYPE html><html><body><h1>Hello From C!</h1></body></html>";

    while (1) {
        client_fd =
            accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);

        if (client_fd == -1) {
            err(EXIT_FAILURE, "client socket");
        }

        memset(buffer, 0, BUFFER_SIZE);
        read(client_fd, buffer, BUFFER_SIZE - 1);
        printf("Received request: %s\n", buffer);

        write(client_fd, http_respone, strlen(http_respone));
        close(client_fd);
    }

    close(client_fd);
}
