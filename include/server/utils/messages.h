/*
** EPITECH PROJECT, 2023
** messages.h
** File description:
** Created by Arthur MAQUET
** First edition:
** 17:11:40 08/04/2023
*/

#ifndef B_NWP_400_LYN_4_1_MYTEAMS_LUCAS_SIRAUX_INCLUDE_SERVER_MESSAGES_H_
#define B_NWP_400_LYN_4_1_MYTEAMS_LUCAS_SIRAUX_INCLUDE_SERVER_MESSAGES_H_

#include <stdbool.h>
#include <stdio.h>

#define MAX_CLIENTS 10

typedef struct {
  int client_sock_fd;
  char read_buffer[BUFSIZ];
  char write_buffer[BUFSIZ];
  char *read_ptr;
  char *write_ptr;
  bool switch_read_write;
  char *username;
  char *user_uuid;
  char *context_team_uuid;
  char *context_channel_uuid;
  char *context_thread_uuid;
} client_t;

#endif //B_NWP_400_LYN_4_1_MYTEAMS_LUCAS_SIRAUX_INCLUDE_SERVER_MESSAGES_H_
