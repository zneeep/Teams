/*
** EPITECH PROJECT, 2023
** B-NWP-400-LYN-4-1-myteams-lucas.siraux
** File description:
** fea_messages
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

bool check_logged_messages(client_t *clients, int cci)
{
    if (clients[cci].user_uuid == NULL) {
        char *buffer = malloc(sizeof(char) * 128);
        buffer[0] = '\0';
        strcat(buffer, "/messages \"unauthorized\"\r\n");
        save_string(clients[cci].write_buffer, buffer);
        clients[cci].switch_read_write = true;
        handle_client_write_message(&clients[cci]);
        free(buffer);
        return false;
    }
    return true;
}

bool check_user_messages(client_t *clients, char **command, int cci, char ***data)
{
    if (data == NULL) {
        char *buffer = malloc(sizeof(char) * 128);
        buffer[0] = '\0';
        strcat(buffer, "/messages \"unknown_user\" ");
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


void fea_messages(client_t *clients, char **command, int cci)
{
    char ***receiver_name = get_rows_from_key("users", "user_uuid", command[1], 2);
    if (!check_logged_messages(clients, cci) || !check_user_messages(clients, command, cci, receiver_name))
        return;
    char *conv_id = concat_biggest_to_smallest(clients[cci].username, receiver_name[0][0]);
    printf("conv_id = %s\n", conv_id);
    create_table_if_needed("conv", (const char *[]){"from", "to", "message", "conv_id", "time", NULL});
    char ***data = get_rows_from_key("conv", "conv_id", conv_id, 5);
    if (data == NULL)
        return;
    for (int i = 0; data[i] != NULL; i++) {
        char *buffer = malloc(sizeof(char) * 1024);
        buffer[0] = '\0';
        strcat(buffer, "/messages \"message\" \"");
        strcat(buffer, data[i][0]);
        strcat(buffer, "\" \"");
        strcat(buffer, data[i][4]);
        strcat(buffer, "\" \"");
        strcat(buffer, data[i][2]);
        strcat(buffer, "\"\n\r");
        save_string(clients[cci].write_buffer, buffer);
        clients[cci].switch_read_write = true;
        handle_client_write_message(&clients[cci]);
        free(buffer);
        usleep(10000);
    }
    free_data(data);
}
