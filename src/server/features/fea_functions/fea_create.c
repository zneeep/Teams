/*
** EPITECH PROJECT, 2023
** B-NWP-400-LYN-4-1-myteams-lucas.siraux
** File description:
** fea_create
*/

#include "../../../../include/server/utils/messages.h"
#include "../../../../include/server/database/common_functions.h"
#include "../../../../include/server/database/tables.h"
#include "../../../../include/server/feature/fea_functions.h"
#include <uuid/uuid.h>
#include <stdlib.h>
#include <string.h>

void notify_team_creator(char **command, char *uuid_str, client_t *clients, int cci)
{
    char *buffer = malloc(sizeof(char) * 128);
    buffer[0] = '\0';
    strcat(buffer, "/create \"team_created\" \"");
    strcat(buffer, uuid_str);
    strcat(buffer, "\" \"");
    strcat(buffer, command[1]);
    strcat(buffer, "\" \"");
    strcat(buffer, command[2]);
    strcat(buffer, "\"\r\n");
    save_string(clients[cci].write_buffer, buffer);
    clients[cci].switch_read_write = true;
    handle_client_write_message(&clients[cci]);
    free(buffer);   
}

void notify_channel_creator(char **command, char *uuid_str, client_t *clients, int cci)
{
    char *buffer = malloc(sizeof(char) * 128);
    buffer[0] = '\0';
    strcat(buffer, "/create \"channel_created\" \"");
    strcat(buffer, uuid_str);
    strcat(buffer, "\" \"");
    strcat(buffer, command[1]);
    strcat(buffer, "\" \"");
    strcat(buffer, command[2]);
    strcat(buffer, "\"\r\n");
    save_string(clients[cci].write_buffer, buffer);
    clients[cci].switch_read_write = true;
    handle_client_write_message(&clients[cci]);
    free(buffer);   
}

bool is_client_subbed(char ***data, char *user_uuid)
{
    for (int i = 0; data[i] != NULL; i++) {
        if (strcmp(user_uuid, data[i][1]) == 0)
            return true;
    }
    return false;
}

bool check_logged_create(client_t *clients, char **command, int cci)
{
    if (clients[cci].user_uuid == NULL) {
        char *buffer = malloc(sizeof(char) * 128);
        buffer[0] = '\0';
        strcat(buffer, "/create \"unauthorized\"\r\n");
        save_string(clients[cci].write_buffer, buffer);
        clients[cci].switch_read_write = true;
        handle_client_write_message(&clients[cci]);
        free(buffer);
        return false;
    }
    return true;
}

bool check_exist(client_t *clients, char **command, int cci, char ***data)
{
    if (data != NULL) {
        char *buffer = malloc(sizeof(char) * 128);
        buffer[0] = '\0';
        strcat(buffer, "/create \"already_exist\"\r\n");
        save_string(clients[cci].write_buffer, buffer);
        clients[cci].switch_read_write = true;
        handle_client_write_message(&clients[cci]);
        free(buffer);
        return false;
    }
    return true;
}

bool check_team_context(client_t *clients, int cci)
{
    char ***data = get_rows_from_key("teams", "team_uuid", clients[cci].context_team_uuid, 3);
    if (data == NULL) {
        char *buffer = malloc(sizeof(char) * 128);
        buffer[0] = '\0';
        strcat(buffer, "/create \"unknown_team\" \"");
        strcat(buffer, clients[cci].context_team_uuid);
        strcat(buffer, "\"\r\n");
        save_string(clients[cci].write_buffer, buffer);
        clients[cci].switch_read_write = true;
        handle_client_write_message(&clients[cci]);
        free(buffer);
        return false;
    }
    return true;
}

bool check_channel_context(client_t *clients, int cci)
{
    char ***data = get_rows_from_key("channels", "channel_name", clients[cci].context_channel_uuid, 4);
    if (data == NULL) {
        char *buffer = malloc(sizeof(char) * 128);
        buffer[0] = '\0';
        strcat(buffer, "/create \"unknown_channel\" \"");
        strcat(buffer, clients[cci].context_channel_uuid);
        strcat(buffer, "\"\r\n");
        save_string(clients[cci].write_buffer, buffer);
        clients[cci].switch_read_write = true;
        handle_client_write_message(&clients[cci]);
        free(buffer);
        return false;
    }
    return true;

}

bool check_thread_context(client_t *clients, int cci)
{
    char ***data = get_rows_from_key("threads", "thread_title", clients[cci].context_thread_uuid, 5);
    if (data == NULL) {
        char *buffer = malloc(sizeof(char) * 128);
        buffer[0] = '\0';
        strcat(buffer, "/create \"unknown_thread\" \"");
        strcat(buffer, clients[cci].context_thread_uuid);
        strcat(buffer, "\"\r\n");
        save_string(clients[cci].write_buffer, buffer);
        clients[cci].switch_read_write = true;
        handle_client_write_message(&clients[cci]);
        free(buffer);
        return false;
    }
    return true;

}

void create_team(client_t *clients, char **command, int cci)
{
    create_table_if_needed("teams", (const char *[]){"team_name", "team_uuid", "description", NULL});
    char ***data = get_rows_from_key("teams", "team_name", command[1], 3);
    if (!check_exist(clients, command, cci, data)) {
        free(data);
        return;
    }
    uuid_t uuid;
    char *uuid_str = malloc(sizeof(char) * 37);
    uuid_generate(uuid);
    uuid_unparse(uuid, uuid_str);
    add_row_to_table("teams", (const char*[]){command[1], uuid_str, command[2], NULL});
    server_event_team_created(uuid_str, command[1], clients[cci].user_uuid);
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i].user_uuid != NULL) {
            char *buffer = malloc(sizeof(char) * 128);
            buffer[0] = '\0';
            strcat(buffer, "/create \"event_team_created\" \"");
            strcat(buffer, uuid_str);
            strcat(buffer, "\" \"");
            strcat(buffer, command[1]);
            strcat(buffer, "\" \"");
            strcat(buffer, command[2]);
            strcat(buffer, "\"\r\n");
            save_string(clients[i].write_buffer, buffer);
            clients[i].switch_read_write = true;
            handle_client_write_message(&clients[i]);
            free(buffer);
        }
    }
    notify_team_creator(command, uuid_str, clients, cci);
    free(uuid_str);
}

void create_channel(client_t *clients, char **command, int cci)
{   
    if (!check_team_context(clients, cci))
        return;
    create_table_if_needed("channels", (const char *[]){"channel_name", "channel_uuid", "description", "team_uuid", NULL});
    char ***data = get_rows_from_key("channels", "channel_name", command[1], 4);
    if (!check_exist(clients, command, cci, data)) {
        free(data);
        return;
    }
    uuid_t uuid;
    char *uuid_str = malloc(sizeof(char) * 37);
    uuid_generate(uuid);
    uuid_unparse(uuid, uuid_str);
    add_row_to_table("channels", (const char*[]){command[1], uuid_str, command[2], clients[cci].context_team_uuid, NULL});
    server_event_channel_created(clients[cci].context_team_uuid, uuid_str, command[1]);
    create_table_if_needed("subs", (const char *[]){"team_uuid", "user_uuid", NULL});
    for (int i = 0; i < MAX_CLIENTS; i++) {
        char ***is_sub = get_rows_from_key("subs", "team_uuid", clients[cci].context_team_uuid, 2);
        if (clients[i].user_uuid != NULL && is_client_subbed(is_sub, clients[i].user_uuid)) {
            char *buffer = malloc(sizeof(char) * 128);
            buffer[0] = '\0';
            strcat(buffer, "/create \"event_channel_created\" \"");
            strcat(buffer, uuid_str);
            strcat(buffer, "\" \"");
            strcat(buffer, command[1]);
            strcat(buffer, "\" \"");
            strcat(buffer, command[2]);
            strcat(buffer, "\"\r\n");
            save_string(clients[i].write_buffer, buffer);
            clients[i].switch_read_write = true;
            handle_client_write_message(&clients[i]);
            free(buffer);
            free_data(is_sub);
        }
    }
    notify_channel_creator(command, uuid_str, clients, cci);
    free(uuid_str);
}

void create_thread(client_t *clients, char **command, int cci)
{
    if (!check_team_context(clients, cci) || !check_channel_context(clients, cci))
        return;
    create_table_if_needed("threads", (const char *[]){"thread_title", "thread_uuid", "thread_message", "channel_uuid", "team_uuid", NULL});
    char ***data = get_rows_from_key("threads", "thread_title", command[1], 5);
    if (!check_exist(clients, command, cci, data)) {
        free(data);
        return;
    }
    uuid_t uuid;
    char *uuid_str = malloc(sizeof(char) * 37);
    uuid_generate(uuid);
    uuid_unparse(uuid, uuid_str);
    add_row_to_table("threads", (const char*[]){command[1], uuid_str, command[2], clients[cci].context_channel_uuid, clients[cci].context_team_uuid, NULL});
    server_event_thread_created(clients[cci].context_channel_uuid, uuid_str, clients[cci].user_uuid, command[1], command[2]);
}

void create_reply(client_t *clients, char **command, int cci)
{
    if (!check_team_context(clients, cci) || !check_channel_context(clients, cci) || !check_thread_context(clients, cci))
        return;
    char ***data = get_rows_from_key("threads", "thread_uuid", clients[cci].user_uuid, 5);
    create_table_if_needed("threads_replies", (const char *[]){"thread_title", "thread_uuid", "thread_message", "channel_uuid", "team_uuid", "replie", "from", NULL});
    uuid_t uuid;
    char *uuid_str = malloc(sizeof(char) * 37);
    uuid_generate(uuid);
    uuid_unparse(uuid, uuid_str);
    add_row_to_table("threads_replies", (const char*[]){command[1], uuid_str, command[2], clients[cci].context_channel_uuid, clients[cci].context_team_uuid, command[3], clients[cci].user_uuid, NULL});
}

void fea_create(client_t *clients, char **command, int cci)
{
    if (!check_logged_create(clients, command, cci))
        return;
    if (clients[cci].context_team_uuid == NULL) {
        create_team(clients, command, cci);
        return;
    } else if (clients[cci].context_channel_uuid == NULL) {
        create_channel(clients, command, cci);
        return;
    } else {
        if (clients[cci].context_thread_uuid == NULL) {
            create_thread(clients, command, cci);
            return;
        }
    }
    create_reply(clients, command, cci);
}
