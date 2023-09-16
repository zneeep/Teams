/*
** EPITECH PROJECT, 2023
** find_feature.c
** File description:
** Created by Arthur MAQUET
** First edition:
** 21:01:38 08/04/2023
*/

#include <string.h>

#include "../../../include/server/feature/fea_functions.h"
#include "../../../include/server/feature/find_feature.h"
#include "../../../include/server/feature/save_string.h"
#include <stdlib.h>

typedef struct {
  char *command_name;
  void (*function)(client_t *, char **, int);
} feature_t;

static feature_t features[] = {
    {"/help", &fea_help},
    {"/login", &fea_login},
    {"/subscribe", &fea_subscribe},
    {"/messages", &fea_messages},
    {"/create", &fea_create},
    {"/subscribed", &fea_subscribed},
    {"/send", &fea_send},
    {"/use", &fea_use},
    {"/list", &fea_list},
    {"/logout", &fea_logout},
    {NULL, NULL}
};

void find_feature(int client_sock_fd, client_t *clients, char **command, int cci)
{
  for (int i = 0; features[i].command_name != NULL; i++) {
    if (strcmp(features[i].command_name, command[0]) == 0) {
      features[i].function(clients, command, cci);
      return;
    }
  }
  save_string(clients[cci].write_buffer, "Unknown command, try /help\r\n");
}
