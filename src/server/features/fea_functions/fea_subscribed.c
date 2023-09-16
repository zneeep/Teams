/*
** EPITECH PROJECT, 2023
** B-NWP-400-LYN-4-1-myteams-lucas.siraux
** File description:
** fea_subscribed
*/

#include "../../../../include/server/utils/messages.h"
#include "../../../../include/server/database/common_functions.h"
#include "../../../../include/server/database/tables.h"
#include "../../../../include/server/messages/client_messages.h"
#include "../../../../include/server/feature/save_string.h"
#include "../../../../include/server/messages/handle_client_write_message.h"
#include <string.h>
#include <stdlib.h>


bool check_logged_subscribed(client_t *clients, int cci)
{
    if (clients[cci].user_uuid == NULL) {
        char *buffer = malloc(sizeof(char) * 128);
        buffer[0] = '\0';
        strcat(buffer, "/subscribed \"unauthorized\"\n\r");
        save_string(clients[cci].write_buffer, buffer);
        clients[cci].switch_read_write = true;
        handle_client_write_message(&clients[cci]);
        free(buffer);
        return false;
    }
    return true;
}

bool check_team_subscribed(client_t *clients, char **command, int cci)
{
    if (command[1] == NULL)
        return true;
    create_table_if_needed("teams", (const char *[]){"team_name", "team_uuid", "description", NULL});
    char ***data = get_rows_from_key("teams", "team_uuid", command[1], 3);
    if (data == NULL) {
        char *buffer = malloc(sizeof(char) * 128);
        buffer[0] = '\0';
        strcat(buffer, "/subscribed \"unknown_team\" \"");
        strcat(buffer, clients[cci].context_team_uuid);
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

void fea_subscribed_no_id(client_t *clients, char **command, int cci)
{
    create_table_if_needed("subs", (const char *[]){"team_uuid", "user_uuid", NULL});
    char ***data = get_rows_from_key("subs", "user_uuid", clients[cci].user_uuid, 2);
    if (data == NULL)
        return;
    for (int i = 0; data[i] != NULL; i++) {
        char ***team = get_rows_from_key("teams", "team_uuid", data[i][0], 3);
        char *buffer = malloc(sizeof(char) * 512);
        buffer[0] = '\0';
        strcat(buffer, "/subscribed \"team\" \"");
        strcat(buffer, team[0][0]);
        strcat(buffer, "\" \"");
        strcat(buffer, team[0][1]);
        strcat(buffer, "\" \"");
        strcat(buffer, team[0][2]);
        strcat(buffer, "\"\r\n");
        save_string(clients[cci].write_buffer, buffer);
        clients[cci].switch_read_write = true;
        handle_client_write_message(&clients[cci]);
        free(buffer);
        free_data(team);
    }
}

void fea_subscribed_id(client_t *clients, char **command, int cci)
{
    create_table_if_needed("subs", (const char *[]){"team_uuid", "user_uuid", NULL});
    char ***data = get_rows_from_key("subs", "team_uuid", command[1], 2);
    if (data == NULL)
        return;
    for (int i = 0; data[i] != NULL; i++) {
        char ***user = get_rows_from_key("users", "user_uuid", data[i][1], 2);
        char *buffer = malloc(sizeof(char) * 512);
        char *status = "0";
        buffer[0] = '\0';
        strcat(buffer, "/subscribed \"user\" \"");
        strcat(buffer, user[0][1]);
        strcat(buffer, "\" \"");
        strcat(buffer, user[0][0]);
        strcat(buffer, "\" \"");
        for (int j = 0; j < MAX_CLIENTS; j++)
            if (strcmp(clients[j].user_uuid, user[0][1]) == 0)
                status = "1";
        strcat(buffer, status);
        strcat(buffer, "\"\r\n");
        save_string(clients[cci].write_buffer, buffer);
        clients[cci].switch_read_write = true;
        handle_client_write_message(&clients[cci]);
        free(buffer);
        free_data(user);
    }
}
void fea_subscribed(client_t *clients, char **command, int cci)
{
    if (!check_logged_subscribed(clients, cci) || !check_team_subscribed(clients, command, cci))
        return;
    if (command[1] == NULL) {
        fea_subscribed_no_id(clients, command, cci);
    } else 
        fea_subscribed_id(clients, command, cci);
}
