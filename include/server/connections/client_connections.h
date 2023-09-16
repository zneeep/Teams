/*
** EPITECH PROJECT, 2023
** client_connections.h
** File description:
** Created by Arthur MAQUET
** First edition:
** 18:52:43 08/04/2023
*/

#ifndef B_NWP_400_LYN_4_1_MYTEAMS_LUCAS_SIRAUX_SRC_SERVER_CLIENT_CONNECTIONS_H_
#define B_NWP_400_LYN_4_1_MYTEAMS_LUCAS_SIRAUX_SRC_SERVER_CLIENT_CONNECTIONS_H_

#include "../../../include/server/utils/messages.h"
#include <sys/select.h>

void init_clients(client_t *clients, int num_clients);
void handle_new_connection(int socket_fd, fd_set *read_fds,
                           client_t *clients);

#endif //B_NWP_400_LYN_4_1_MYTEAMS_LUCAS_SIRAUX_SRC_SERVER_CLIENT_CONNECTIONS_H_
