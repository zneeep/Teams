/*
** EPITECH PROJECT, 2023
** client_connections.c
** File description:
** Created by Arthur MAQUET
** First edition:
** 18:52:43 08/04/2023
*/

#include <unistd.h>
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>

#include "../../../include/server/connections/client_connections.h"
#include "../../../include/server/messages/client_messages.h"
#include "../../../include/server/feature/save_string.h"

void init_clients(client_t *clients, int num_clients) {
  for (int i = 0; i < num_clients; i++) {
    clients[i].client_sock_fd = -1;
    clients[i].read_ptr = NULL;
    clients[i].write_ptr = NULL;
    clients[i].switch_read_write = false;
    clients[i].context_channel_uuid = NULL;
    clients[i].context_team_uuid = NULL;
    clients[i].context_thread_uuid = NULL;
    clients[i].user_uuid = NULL;
    clients[i].username = NULL;
    memset(clients[i].read_buffer, 0, sizeof(clients[i].read_buffer));
    memset(clients[i].write_buffer, 0, sizeof(clients[i].write_buffer));
  }
}

static int accept_new_client(int socket_fd, struct sockaddr_in *client_addr,
                             socklen_t *client_addr_len) {
  int new_socket = accept(socket_fd, (struct sockaddr *)client_addr,
                          client_addr_len);

  if (new_socket < 0) perror("accept");
  return new_socket;
}

void handle_new_connection(int socket_fd, fd_set *read_fds,
                           client_t *clients) {
  if (FD_ISSET(socket_fd, read_fds)) {
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    int new_socket = accept_new_client(socket_fd, &client_addr,
                                       &client_addr_len);
    if (new_socket < 0) return;

    for (int i = 0; i < MAX_CLIENTS; i++) {
      if (clients[i].client_sock_fd != -1) continue;
      clients[i].client_sock_fd = new_socket;
      break;
    }
  }
}
