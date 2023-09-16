/*
** EPITECH PROJECT, 2023
** client_messages.c
** File description:
** Created by Arthur MAQUET
** First edition:
** 18:57:18 08/04/2023
*/

#include "../../../include/server/messages/client_messages.h"
#include "../../../include/server/messages/handle_client_read_messages.h"
#include "../../../include/server/messages/handle_client_write_message.h"

void handle_client_activity(fd_set *read_fds, fd_set *write_fds,
                            client_t *clients) {
  for (int i = 0; i < MAX_CLIENTS; i++) {
    if (FD_ISSET(clients[i].client_sock_fd, read_fds)
        && clients[i].switch_read_write == false) {
      handle_client_read_message(clients, i);
    }
    if (FD_ISSET(clients[i].client_sock_fd, write_fds)
        && clients[i].switch_read_write == true) {
      handle_client_write_message(&clients[i]);
    }
  }
}
