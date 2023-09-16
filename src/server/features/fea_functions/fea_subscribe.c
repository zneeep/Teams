/*
** EPITECH PROJECT, 2023
** B-NWP-400-LYN-4-1-myteams-lucas.siraux
** File description:
** fea_subscribe
*/

#include "../../../../include/server/utils/messages.h"
#include "../../../../include/server/database/common_functions.h"
#include "../../../../include/server/database/tables.h"
#include "../../../../include/server/feature/fea_functions.h"
#include <uuid/uuid.h>
#include <stdlib.h>
#include <string.h>

bool check_logged_subscribe(client_t *clients, int cci)
{
    if (clients[cci].user_uuid == NULL) {
        char *buffer = malloc(sizeof(char) * 128);
        buffer[0] = '\0';
        strcat(buffer, "/subscribe \"unauthorized\"\r\n");
        save_string(clients[cci].write_buffer, buffer);
        clients[cci].switch_read_write = true;
        handle_client_write_message(&clients[cci]);
        free(buffer);
        return false; 
    }
    return true;
}

void notify_subscriber(client_t *clients, char **command, int cci)
{
    char *buffer = malloc(sizeof(char) * 512);
    buffer[0] = '\0';
    strcat(buffer, "/subscribe \"successful\" \"");
    strcat(buffer, clients[cci].user_uuid);
    strcat(buffer, "\" \"");
    strcat(buffer, command[1]);
    strcat(buffer, "\"\r\n");
    save_string(clients[cci].write_buffer, buffer);
    clients[cci].switch_read_write = true;
    handle_client_write_message(&clients[cci]);
    free(buffer);
}

bool check_already_sub(client_t *clients, char **command, int cci)
{
    create_table_if_needed("subs", (const char *[]){"team_uuid", "user_uuid", NULL});
    char ***data = get_rows_from_key("subs", "user_uuid", clients[cci].user_uuid, 2);
    if (data == NULL)
        return true;
    for (int i = 0; data[i] != NULL; i++) {
        printf("data [%d][%d] = %s", i, 1, data[i][1]);
        if (strcmp(data[i][1], command[1]) == 0) {
            char *buffer = malloc(sizeof(char) * 128);
            buffer[0] = '\0';
            strcat(buffer, "/subscribe \"unauthorized\"\r\n");
            save_string(clients[cci].write_buffer, buffer);
            clients[cci].switch_read_write = true;
            handle_client_write_message(&clients[cci]);
            free(buffer);
            free_data(data);
            return false; 
        }
    }
    free_data(data);
    return true;
}

bool check_team_subscribe(client_t *clients, char **command, int cci)
{
    create_table_if_needed("teams", (const char *[]){"team_name", "team_uuid", "description", NULL});
    char ***data = get_rows_from_key("teams", "team_uuid", command[1], 3);
    if (data == NULL) {
        char *buffer = malloc(sizeof(char) * 128);
        buffer[0] = '\0';
        strcat(buffer, "/subscribe \"unknown_team\" \"");
        strcat(buffer, command[1]);
        strcat(buffer, "\"\r\n");
        save_string(clients[cci].write_buffer, buffer);
        clients[cci].switch_read_write = true;
        handle_client_write_message(&clients[cci]);
        free(buffer);
        return false;
    }
    free_data(data);
    return true;
}

void fea_subscribe(client_t *clients, char **command, int cci)
{
    create_table_if_needed("subs", (const char *[]){"team_uuid", "user_uuid", NULL});
    if (!(check_logged_subscribe(clients, cci)) || !check_team_subscribe(clients, command, cci)
    || !check_already_sub(clients, command, cci))
        return;
    add_row_to_table("subs", (const char*[]){command[1], clients[cci].user_uuid, NULL});
    notify_subscriber(clients, command, cci);
    server_event_user_subscribed(command[1], clients[cci].user_uuid);
}