/*
** EPITECH PROJECT, 2023
** B-NWP-400-LYN-4-1-myteams-lucas.siraux
** File description:
** fea_logout
*/

#include <sys/socket.h>
#include <unistd.h>
#include "../../../../libs/logging_server.h"
#include "../../../../include/server/utils/messages.h"
#include "../../../../include/server/database/common_functions.h"
#include "../../../../include/server/database/tables.h"
#include "../../../../include/server/feature/fea_functions.h"
#include <uuid/uuid.h>
#include <stdlib.h>
#include <string.h>

#include "server/utils/messages.h"

static void set_values_to_default(client_t *clients, int cci) {
  client_t *client = &clients[cci];

  client->client_sock_fd = -1;

  bzero(client->read_buffer, BUFSIZ);
  bzero(client->write_buffer, BUFSIZ);

  client->read_ptr = client->read_buffer;
  client->write_ptr = client->write_buffer;

  char **fields[] = {
    &client->username,
    &client->user_uuid,
    &client->context_team_uuid,
    &client->context_channel_uuid,
    &client->context_thread_uuid
  };

  for (int i = 0; i < sizeof(fields)/sizeof(fields[0]); i++) {
    if (*fields[i] != NULL) {
      free(*fields[i]);
      *fields[i] = NULL;
    }
  }
}

bool check_logged_logout(client_t *clients, int cci)
{
    if (clients[cci].user_uuid == NULL) {
        char *buffer = malloc(sizeof(char) * 128);
        buffer[0] = '\0';
        strcat(buffer, "/logout \"unauthorized\"\r\n");
        save_string(clients[cci].write_buffer, buffer);
        clients[cci].switch_read_write = true;
        handle_client_write_message(&clients[cci]);
        free(buffer);
        return false;
    }
    return true;
}

void fea_logout(client_t *clients, char **command, int cci)
{
  server_event_user_logged_out(clients[cci].user_uuid);

  char buffer[BUFSIZ];
  int len = snprintf(buffer, BUFSIZ, "/logout \"client\" \"%s\" \"%s\"\r\n",
                     clients[cci].user_uuid, clients[cci].username);
  
  for (int i = 0; i < MAX_CLIENTS; i++) {
    if (clients[i].user_uuid != NULL) {
        save_string(clients[i].write_buffer, buffer);
        clients[i].switch_read_write = true;
        handle_client_write_message(&clients[i]);
    }
  }

  close(clients[cci].client_sock_fd);
  set_values_to_default(clients, cci);
}
