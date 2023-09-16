/*
** EPITECH PROJECT, 2023
** close_all_connections.h
** File description:
** Created by Arthur MAQUET
** First edition:
** 19:35:46 08/04/2023
*/

#ifndef B_NWP_400_LYN_4_1_MYTEAMS_LUCAS_SIRAUX_SRC_SERVER_CONNECTIONS_CLOSE_ALL_CONNECTIONS_H_
#define B_NWP_400_LYN_4_1_MYTEAMS_LUCAS_SIRAUX_SRC_SERVER_CONNECTIONS_CLOSE_ALL_CONNECTIONS_H_

#include "../../../include/server/utils/messages.h"

#define SERVER_CLOSING_MESSAGE "Server is closing, bye bye!\r\n"

void close_all_connections(client_t clients[MAX_CLIENTS]);
void close_specific_connection(int *client_sock_fd);

#endif //B_NWP_400_LYN_4_1_MYTEAMS_LUCAS_SIRAUX_SRC_SERVER_CONNECTIONS_CLOSE_ALL_CONNECTIONS_H_
