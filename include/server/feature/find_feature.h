/*
** EPITECH PROJECT, 2023
** find_feature.h
** File description:
** Created by Arthur MAQUET
** First edition:
** 21:01:38 08/04/2023
*/

#ifndef B_NWP_400_LYN_4_1_MYTEAMS_LUCAS_SIRAUX_SRC_SERVER_FEATURES_FIND_FEATURE_H_
#define B_NWP_400_LYN_4_1_MYTEAMS_LUCAS_SIRAUX_SRC_SERVER_FEATURES_FIND_FEATURE_H_

#include <stdio.h>

#include "../utils/messages.h"

void find_feature(int client_sock_fd, client_t *clients, char **command, int cci);

#endif //B_NWP_400_LYN_4_1_MYTEAMS_LUCAS_SIRAUX_SRC_SERVER_FEATURES_FIND_FEATURE_H_
