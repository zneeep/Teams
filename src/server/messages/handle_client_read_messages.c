/*
** EPITECH PROJECT, 2023
** handle_client_messages.c
** File description:
** Created by Arthur MAQUET
** First edition:
** 20:00:51 11/04/2023
*/

#include <string.h>
#include <sys/socket.h>
#include "../../../include/server/messages/handle_client_read_messages.h"
#include "../../../include/server/feature/find_feature.h"
#include "../../../include/server/connections/close_connections.h"
#include <stdlib.h>
#include <ctype.h>
#include "../../../include/mylib/mylib.h"


static void process_client_message(client_t *clients, int cci)
{
  char **command = str_to_wrd_arr(clients[cci].read_buffer);
  find_feature(clients[cci].client_sock_fd, clients, command, cci);
  for (int i = 0; command[i] != NULL; i++)
    free(command[i]);
  free(command);
  memset(clients[cci].read_buffer, 0, BUFSIZ);
  clients[cci].read_ptr = clients[cci].read_buffer;
}

void handle_client_read_message(client_t *clients, int cci)
{
  ssize_t bytes_received;
  size_t remaining_buffer_size = BUFSIZ;

  if (clients[cci].read_ptr == NULL)
    clients[cci].read_ptr = clients[cci].read_buffer;

  while (remaining_buffer_size > 0 && !clients[cci].switch_read_write) {
    bytes_received = recv(clients[cci].client_sock_fd, clients[cci].read_ptr,
                          remaining_buffer_size, 0);
    if (bytes_received <= 0) {
      close_specific_connection(&clients[cci].client_sock_fd);
      return;
    }
    clients[cci].read_ptr[bytes_received] = '\0';

    char *delimiter = strstr(clients[cci].read_ptr, "\r\n");
    if (delimiter) {
      clients[cci].switch_read_write = true;
      *delimiter = '\0';
    } else {
      clients[cci].read_ptr += bytes_received;
      remaining_buffer_size -= bytes_received;
    }
  }

  if (!clients[cci].switch_read_write) {
    close_specific_connection(&clients[cci].client_sock_fd);
    return;
  }
  process_client_message(clients, cci);
}
