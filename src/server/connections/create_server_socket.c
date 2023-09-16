/*
** EPITECH PROJECT, 2023
** create_server_socket.c
** File description:
** Created by Arthur MAQUET
** First edition:
** 14:20:44 08/04/2023
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>

#include "../../../include/server/connections/create_server_socket.h"
#include "../../../include/server/utils/messages.h"

bool create_server_socket(const char *port, int *socket_fd) {
  *socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (*socket_fd == -1) {
    perror("socket");
    return (false);
  }

  struct sockaddr_in address = {
      .sin_family = AF_INET,
      .sin_addr.s_addr = htonl(INADDR_ANY),
      .sin_port = htons(atoi(port)),
      .sin_zero = {0}
  };

  if (bind(*socket_fd, (struct sockaddr *)&address, sizeof(address)) == -1) {
    perror("bind");
    return (false);
  }
  if (listen(*socket_fd, MAX_CLIENTS) == -1) {
    perror("listen");
    return (false);
  }
  return (true);
}
