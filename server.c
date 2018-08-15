/*******************************************************
 * Filename: server.c
 * Author: David Wang
 * Date: 08/14/2018
 *
 * A server using tcp sockets that echos whatever
 * text was sent to it.
*******************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

void print_error(const char *msg) {
  perror(msg);
}

int startup_server(const char *port_p) {
  int socket_fd, newsock_fd, bytes_read;
  struct sockaddr_in server_addr, client_addr;
  char buffer[BUFSIZ];

  socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_fd < 0) {
    print_error("Couldn't get a valid socket file descriptor");
  }
  int port = atoi(port_p);
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  if (bind(socket_fd, (struct sockaddr *) &server_addr, sizeof(struct sockaddr_in)) < 0) {
    print_error("Could not bind to socket");
    return -1;
  }

  if (listen(socket_fd, 5)) {
    print_error("Could not connect to socket");
    return -1;
  }

  int clientlen = sizeof(struct sockaddr_in);

  if ((newsock_fd = accept(socket_fd, (struct sockaddr *) &server_addr, (socklen_t *) &clientlen)) < 0) {
    print_error("Could not accept connection to socket.");
    return -1;
  }

  if ((bytes_read = read(newsock_fd, buffer, BUFSIZ)) < 0) {
    print_error("Error reading in data");
  }

  printf("%s", buffer);

  return 0;
}


int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "usage: ./server <port>\n");
  }

  startup_server(argv[1]);
}
