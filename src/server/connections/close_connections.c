/*
** EPITECH PROJECT, 2023
** close_all_connections.c
** File description:
** Created by Arthur MAQUET
** First edition:
** 19:35:46 08/04/2023
*/

#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <stdio.h>

#include "../../../include/server/connections/close_connections.h"

void close_all_connections(client_t clients[MAX_CLIENTS]) {
  for (int i = 0; i < MAX_CLIENTS; i++) {
    if (clients[i].client_sock_fd > 0) {
      send(clients[i].client_sock_fd, SERVER_CLOSING_MESSAGE,
           strlen(SERVER_CLOSING_MESSAGE), 0);
      close(clients[i].client_sock_fd);
    }
  }
}

void close_specific_connection(int *client_sock_fd) {
  close(*client_sock_fd);
  *client_sock_fd = -1;
}
