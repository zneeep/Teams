/*
** EPITECH PROJECT, 2023
** handle_client_write_message.c
** File description:
** Created by Arthur MAQUET
** First edition:
** 20:54:44 11/04/2023
*/

#include <string.h>
#include <sys/socket.h>
#include <errno.h>

#include "../../../include/server/utils/messages.h"

void handle_client_write_message(client_t *client)
{
  size_t total_sent = 0;
  size_t buffer_length = strlen(client->write_buffer);
  ssize_t bytes_sent;
  client->write_ptr = client->write_buffer;

  while (total_sent < buffer_length) {
    bytes_sent = send(client->client_sock_fd, client->write_ptr + total_sent,
                      buffer_length - total_sent, 0);
    if (bytes_sent < 0) {
      if (errno == EINTR) {
        continue;
      }
      perror("Error sending message");
      return;
    }
    total_sent += bytes_sent;
  }

  client->switch_read_write = false;
  memset(client->write_buffer, 0, buffer_length);
  memset(client->read_buffer, 0, strlen(client->read_buffer));
}
