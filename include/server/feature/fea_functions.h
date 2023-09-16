/*
** EPITECH PROJECT, 2023
** fea_help.h
** File description:
** Created by Arthur MAQUET
** First edition:
** 21:05:42 08/04/2023
*/

#ifndef B_NWP_400_LYN_4_1_MYTEAMS_LUCAS_SIRAUX_INCLUDE_SERVER_FEATURE_FEA_FUNCTIONS_H_
#define B_NWP_400_LYN_4_1_MYTEAMS_LUCAS_SIRAUX_INCLUDE_SERVER_FEATURE_FEA_FUNCTIONS_H_

#include "../utils/messages.h"
#include "../database/tables.h"
#include "../database/common_functions.h"
#include "../../../libs/logging_server.h"
#include "../../mylib/mylib.h"
#include <unistd.h>

void fea_help(client_t *clients, __attribute__((unused))char **command, int cci);
void fea_login(client_t *clients, char **command, int cci);
void fea_messages(client_t *clients, char **command, int cci);
void fea_subscribe(client_t *clients, char **command, int cci);
void fea_create(client_t *clients, char **command, int cci);
void fea_subscribed(client_t *clients, char **command, int cci);
void fea_send(client_t *clients, char **command, int cci);
void fea_use(client_t *clients, char **command, int cci);
void fea_list(client_t *clients, char **command, int cci);
void fea_info(client_t *clients, char **command, int cci);
void fea_load_users(void);
void fea_logout(client_t *clients, char **command, int cci);
void save_string(char write_buffer[BUFSIZ], const char *buffer);
void handle_client_write_message(client_t *client);

#endif //B_NWP_400_LYN_4_1_MYTEAMS_LUCAS_SIRAUX_INCLUDE_SERVER_FEATURE_FEA_FUNCTIONS_H_
