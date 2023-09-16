/*
** EPITECH PROJECT, 2023
** teams
** File description:
** fea_list
*/

#include "../../../../include/server/utils/messages.h"
#include "../../../../include/server/database/common_functions.h"
#include "../../../../include/server/database/tables.h"
#include "../../../../include/server/feature/fea_functions.h"
#include <uuid/uuid.h>
#include <stdlib.h>
#include <string.h>

bool check_logged_list(client_t *clients, char **command, int cci)
{
    if (clients[cci].user_uuid == NULL) {
        char *buffer = malloc(sizeof(char) * 128);
        buffer[0] = '\0';
        strcat(buffer, "/list \"unauthorized\"\r\n");
        save_string(clients[cci].write_buffer, buffer);
        clients[cci].switch_read_write = true;
        handle_client_write_message(&clients[cci]);
        free(buffer);
        return false;
    }
    return true;
}

bool check_team_context_list(client_t *clients, int cci)
{
    if (clients[cci].context_team_uuid == NULL)
        return true;
    create_table_if_needed("teams", (const char *[]){"team_name", "team_uuid", "description", NULL});
    char ***data = get_rows_from_key("teams", "team_uuid", clients[cci].context_team_uuid, 3);
    if (data == NULL) {
        char *buffer = malloc(sizeof(char) * 128);
        buffer[0] = '\0';
        strcat(buffer, "/list \"unknown_team\" \"");
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

bool check_channel_context_list(client_t *clients, int cci)
{
    if (clients[cci].context_channel_uuid == NULL)
        return true;
    create_table_if_needed("channels", (const char *[]){"channel_name", "channel_uuid", "description", "team_uuid", NULL});
    char ***data = get_rows_from_key("channels", "channel_name", clients[cci].context_channel_uuid, 4);
    if (data == NULL) {
        char *buffer = malloc(sizeof(char) * 128);
        buffer[0] = '\0';
        strcat(buffer, "/list \"unknown_channel\" \"");
        strcat(buffer, clients[cci].context_channel_uuid);
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

bool check_thread_context_list(client_t *clients, int cci)
{
    if (clients[cci].context_thread_uuid == NULL)
        return true;
    create_table_if_needed("threads", (const char *[]){"thread_title", "thread_uuid", "thread_message", "channel_uuid", "team_uuid", NULL});
    char ***data = get_rows_from_key("threads", "thread_title", clients[cci].context_thread_uuid, 5);
    if (data == NULL) {
        char *buffer = malloc(sizeof(char) * 128);
        buffer[0] = '\0';
        strcat(buffer, "/list \"unknown_thread\" \"");
        strcat(buffer, clients[cci].context_thread_uuid);
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

void fea_list_teams(client_t *clients, char **command, int cci)
{
    create_table_if_needed("teams", (const char *[]){"team_name", "team_uuid", "description", NULL});
    char ***data = get_rows_from_key("teams", NULL, NULL, 3);
    if (data == NULL)
        return;
    for (int i = 0; data[i] != NULL; i++) {
        char *buffer = malloc(sizeof(char) * 512);
        buffer[0] = '\0';
        strcat(buffer, "/list \"teams\" \"");
        strcat(buffer, data[i][1]);
        strcat(buffer, "\" \"");
        strcat(buffer, data[i][0]);
        strcat(buffer, "\" \"");
        strcat(buffer, data[i][2]);
        strcat(buffer, "\"\r\n");
        save_string(clients[cci].write_buffer, buffer);
        clients[cci].switch_read_write = true;
        handle_client_write_message(&clients[cci]);
        free(buffer); 
        usleep(10000);
    }
    free_data(data);
}

void fea_list_channels(client_t *clients, char **command, int cci)
{
    create_table_if_needed("channels", (const char *[]){"channel_name", "channel_uuid", "description", "team_uuid", NULL});
    char ***data = get_rows_from_key("channels", "team_uuid", clients[cci].context_team_uuid, 4);
    if (data == NULL)
        return;
    clients[cci].switch_read_write = true;
    for (int i = 0; data[i] != NULL; i++) {
        char *buffer = malloc(sizeof(char) * 512);
        buffer[0] = '\0';
        strcat(buffer, "/list \"teams\" \"");
        strcat(buffer, data[i][1]);
        strcat(buffer, "\" \"");
        strcat(buffer, data[i][0]);
        strcat(buffer, "\" \"");
        strcat(buffer, data[i][2]);
        strcat(buffer, "\"\r\n");
        save_string(clients[cci].write_buffer, buffer);
        clients[cci].switch_read_write = true;
        handle_client_write_message(&clients[cci]);
        free(buffer);
        usleep(10000);
    }
    free(data);
}

void fea_list_threads(client_t *clients, char **command, int cci)
{
    create_table_if_needed("threads", (const char *[]){"thread_title", "thread_uuid", "thread_message", "channel_uuid", "team_uuid", NULL});
    char ***data = get_rows_from_key("threads", "channel_uuid", clients[cci].context_channel_uuid, 5);
    if (data == NULL)
        return;
    clients[cci].switch_read_write = true;
    for (int i = 0; data[i] != NULL; i++) {
        char *tmp = malloc(sizeof(char) * 1024);
        tmp[0] = '\0';
        strcat(tmp, data[i][0]);
        strcat(tmp, " ");
        strcat(tmp, data[i][1]);
        strcat(tmp, "\r\n");
        // printf("tmp = %s\n", tmp);
        // char *buffer = malloc(sizeof(char) * (strlen(data[0][0]) + 2));
        // buffer[0] = '\0';
        // strcat(buffer, data[0][0]);
        // strcat(buffer, "\r\n");
        save_string(clients[cci].write_buffer, tmp);
        clients[cci].switch_read_write = true;
        handle_client_write_message(&clients[cci]);
        // free(buffer);
        free(tmp);
        // usleep(10000);
    }
    free(data);
}

void fea_list_replies(client_t *clients, char **command, int cci)
{
    create_table_if_needed("threads_replies", (const char *[]){"thread_title", "thread_uuid", "thread_message", "channel_uuid", "team_uuid", "replie", "from", NULL});
    char ***data = get_rows_from_key("threads_replies", "thread_uuid", clients[cci].context_thread_uuid, 7);
    if (data == NULL) {
        return;
    }
    clients[cci].switch_read_write = true;
    for (int i = 0; data[i] != NULL; i++) {
        char *tmp = malloc(sizeof(char) * 1024);
        tmp[0] = '\0';
        strcat(tmp, data[i][0]);
        strcat(tmp, " ");
        strcat(tmp, data[i][1]);
        strcat(tmp, "\r\n");
        // printf("tmp = %s\n", tmp);
        // char *buffer = malloc(sizeof(char) * (strlen(data[0][0]) + 2));
        // buffer[0] = '\0';
        // strcat(buffer, data[0][0]);
        // strcat(buffer, "\r\n");
        save_string(clients[cci].write_buffer, tmp);
        clients[cci].switch_read_write = true;
        handle_client_write_message(&clients[cci]);
        // free(buffer);
        free(tmp);
        usleep(10000);
    }
    free(data);
}

void fea_list(client_t *clients, char **command, int cci)
{
    if (!check_logged_list(clients, command, cci) || !check_team_context_list(clients, cci)
    || !check_channel_context_list(clients, cci) || !check_thread_context_list(clients, cci)) {
        return;
    }
    if (clients[cci].context_team_uuid == NULL) {
        fea_list_teams(clients, command, cci);
        return;
    } else if (clients[cci].context_channel_uuid == NULL) {
        fea_list_channels(clients, command, cci);
        return;
    } else {
        if (clients[cci].context_thread_uuid == NULL) {
            fea_list_threads(clients, command, cci);
            return;
        }
    }
    fea_list_replies(clients, command, cci);
}