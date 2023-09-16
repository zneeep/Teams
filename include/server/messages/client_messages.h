/*
** EPITECH PROJECT, 2023
** client_messages.h
** File description:
** Created by Arthur MAQUET
** First edition:
** 18:57:18 08/04/2023
*/

#ifndef B_NWP_400_LYN_4_1_MYTEAMS_LUCAS_SIRAUX_SRC_SERVER_CLIENT_MESSAGES_H_
#define B_NWP_400_LYN_4_1_MYTEAMS_LUCAS_SIRAUX_SRC_SERVER_CLIENT_MESSAGES_H_

#include <sys/select.h>

#include "../../../include/server/utils/messages.h"

void handle_client_activity(fd_set *read_fds, fd_set *write_fds,
                            client_t *clients);

#endif //B_NWP_400_LYN_4_1_MYTEAMS_LUCAS_SIRAUX_SRC_SERVER_CLIENT_MESSAGES_H_
