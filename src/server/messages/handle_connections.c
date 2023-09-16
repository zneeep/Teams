/*
** EPITECH PROJECT, 2023
** handle_connections.c
** File description:
** Created by Arthur MAQUET
** First edition:
** 17:03:16 08/04/2023
*/

#include <sys/select.h>
#include <stddef.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>

#include "server/utils/messages.h"
#include "server/connections/client_connections.h"
#include "server/messages/client_messages.h"
#include "server/connections/close_connections.h"

static volatile sig_atomic_t server_running = 1;

static void setup_fd_sets(int socket_fd, client_t clients[MAX_CLIENTS],
                          fd_set *read_fds, fd_set *write_fds, int *max_fd) {
  FD_ZERO(read_fds);
  FD_ZERO(write_fds);
  FD_SET(socket_fd, read_fds);

  for (int i = 0; i < MAX_CLIENTS; i++) {
    if (clients[i].client_sock_fd > 0) {
      FD_SET(clients[i].client_sock_fd, read_fds);
      FD_SET(clients[i].client_sock_fd, write_fds);
      *max_fd = (clients[i].client_sock_fd > *max_fd)
                ? clients[i].client_sock_fd
                : *max_fd;
    }
  }
}

static void sigint_handler(__attribute__((unused)) int signum) {
  server_running = 0;
}

void handle_connections(int socket_fd, const char *port_number) {
  fd_set read_fds, write_fds;
  client_t *clients = malloc(sizeof(client_t) * MAX_CLIENTS);
  int max_fd = socket_fd;

  init_clients(clients, MAX_CLIENTS);
  signal(SIGINT, sigint_handler);

  while (server_running) {
    setup_fd_sets(socket_fd, clients, &read_fds, &write_fds, &max_fd);

    struct timeval timeout = {1, 0};
    int select_result = select(max_fd + 1, &read_fds, &write_fds, NULL,
                               &timeout);
    if (select_result < 0) {
      if (errno != EINTR) {
        perror("select");
        return;
      }
    } else {
      handle_new_connection(socket_fd, &read_fds, clients);
      handle_client_activity(&read_fds, &write_fds, clients);
    }
  }
  close_all_connections(clients);
  puts("Server shutting down");
}
