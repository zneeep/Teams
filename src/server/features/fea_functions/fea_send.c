/*
** EPITECH PROJECT, 2023
** B-NWP-400-LYN-4-1-myteams-lucas.siraux
** File description:
** fea_send
*/

#include "../../../../include/server/utils/messages.h"
#include "../../../../include/server/database/common_functions.h"
#include "../../../../include/server/database/tables.h"
#include "../../../../include/server/messages/client_messages.h"
#include "../../../../include/server/feature/save_string.h"
#include "../../../../include/server/messages/handle_client_write_message.h"
#include "../../../../include/server/feature/fea_functions.h"
#include <string.h>
#include <stdlib.h>

bool check_logged_send(client_t *clients, char **command, int cci)
{
    if (clients[cci].user_uuid == NULL) {
        char *buffer = malloc(sizeof(char) * 128);
        buffer[0] = '\0';
        strcat(buffer, "/send \"unauthorized\"\n\r");
        save_string(clients[cci].write_buffer, buffer);
        clients[cci].switch_read_write = true;
        handle_client_write_message(&clients[cci]);
        free(buffer);
        return false;
    }
    return true;
}

bool check_receiver(client_t *clients, char **command, int cci, char ***data)
{
    if (data == NULL) {
        char *buffer = malloc(sizeof(char) * 128);
        buffer[0] = '\0';
        strcat(buffer, "/send \"unknown_user\" ");
        strcat(buffer, command[1]);
        strcat(buffer, "\n\r");
        save_string(clients[cci].write_buffer, buffer);
        clients[cci].switch_read_write = true;
        handle_client_write_message(&clients[cci]);
        free(buffer);
        return false;
    }
    return true;
}

void fea_send(client_t *clients, char **command, int cci)
{
    char ***receiver_name = get_rows_from_key("users", "user_uuid", command[1], 2);
    
    if (!check_logged_send(clients, command, cci) || !check_receiver(clients, command, cci, receiver_name)) {
        free_data(receiver_name);
        return;
    }
    char *conv_id = concat_biggest_to_smallest(clients[cci].username, receiver_name[0][0]);
    create_table_if_needed("conv", (const char *[]){"from", "to", "message", "conv_id", "time", NULL});
    add_row_to_table("conv", (const char *[]){clients[cci].user_uuid, command[1], command[2], conv_id, "1", NULL});
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i].user_uuid != NULL && strcmp(clients[i].user_uuid, command[1]) == 0) {
            char *buffer = malloc(sizeof(char) * 1024);
            buffer[0] = '\0';
            strcat(buffer, "/send \"authorized\" ");
            strcat(buffer, clients[cci].user_uuid);
            strcat(buffer, " \"");
            strcat(buffer, command[2]);
            strcat(buffer, "\"\n\r");
            save_string(clients[i].write_buffer, buffer);
            clients[i].switch_read_write = true;
            handle_client_write_message(&clients[i]);
            free(buffer);
        }
    }
    free_data(receiver_name);
    server_event_private_message_sended(clients[cci].user_uuid, command[1], command[2]);
}