/*
** EPITECH PROJECT, 2023
** B-NWP-400-LYN-4-1-myteams-lucas.siraux
** File description:
** fea_login
*/

#include "../../../../include/server/utils/messages.h"
#include "../../../../include/server/database/common_functions.h"
#include "../../../../include/server/database/tables.h"
#include "../../../../include/server/feature/fea_functions.h"
#include <uuid/uuid.h>
#include <stdlib.h>
#include <string.h>

void fea_login(client_t *clients, char **command, int cci)
{
    create_table_if_needed("users", (const char *[]){"username", "user_uuid", NULL});
    char ***data = get_rows_from_key("users", "username", command[1], 2);
    if (data != NULL) {
        clients[cci].username = strdup(data[0][0]);
        clients[cci].user_uuid = strdup(data[0][1]);
    } else {
        uuid_t uuid;
        char *uuid_str = malloc(sizeof(char) * 37);
        uuid_generate(uuid);
        uuid_unparse(uuid, uuid_str);
        add_row_to_table("users", (const char *[]){command[1], uuid_str, NULL});
        clients[cci].username = strdup(command[1]);
        clients[cci].user_uuid = strdup(uuid_str);
        free(uuid_str);
        server_event_user_created(clients[cci].user_uuid, clients[cci].username);
    }
    free_data(data);
    server_event_user_logged_in(clients[cci].user_uuid);
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i].user_uuid != NULL) {
            char *buffer = malloc(sizeof(char) * 128);
            buffer[0] = '\0';
            strcat(buffer, "/login ");
            strcat(buffer, clients[cci].user_uuid);
            strcat(buffer, " ");
            strcat(buffer, clients[cci].username);
            strcat(buffer, "\r\n");
            save_string(clients[i].write_buffer, buffer);
            clients[i].switch_read_write = true;
            handle_client_write_message(&clients[i]);
            free(buffer);
        }
    }
}