// /*
// ** EPITECH PROJECT, 2023
// ** teams
// ** File description:
// ** fea_info
// */

#include "../../../../include/server/utils/messages.h"
#include "../../../../include/server/database/common_functions.h"
#include "../../../../include/server/database/tables.h"
#include "../../../../include/server/feature/fea_functions.h"
#include <uuid/uuid.h>
#include <stdlib.h>
#include <string.h>

// void fea_info_user(client_t *clients, char **command, int cci)
// {
//     create_table_if_needed("users", (const char *[]){"username", "user_uuid", NULL});
//     char ***data = get_rows_from_key("users", "username", command[1]);
//     clients[cci].switch_read_write = true;
//     for (int i = 0; data[i] != NULL; i++) {
//         char *tmp = strdup(data[i][0]);
//         strcat(tmp, " ");
//         strcat(tmp, data[i][1]);
//         strcat(tmp, "\n\r");
//         save_string(clients[cci].write_buffer, tmp);
//         handle_client_write_message(&clients[cci]);
//         free(tmp);
//         usleep(10000);
//     }
//     clients[cci].switch_read_write = false;
// }

// void fea_info_team(client_t *clients, char **command, int cci)
// {
//     create_table_if_needed("teams", (const char *[]){"team_name", "team_uuid", "description", NULL});
//     create_table_if_not_exists("teams");
//     char ***data = get_rows_from_key("teams", NULL, NULL);
//     clients[cci].switch_read_write = true;
//     for (int i = 0; data[i] != NULL; i++) {
//         char *tmp = strdup(data[i][0]);
//         strcat(tmp, " ");
//         strcat(tmp, data[i][1]);
//         strcat(tmp, "\n\r");
//         save_string(clients[cci].write_buffer, tmp);
//         handle_client_write_message(&clients[cci]);
//         free(tmp);
//         usleep(10000);
//     }
//     clients[cci].switch_read_write = false;
//     destroy_table(table);
// }


// void fea_info_channel(client_t *clients, char **command, int cci)
// {
//     table_t *table = create_table_struct("channels", (const char *[]){"channel_name", "channel_uuid", "description", "team_uuid", NULL});
//     create_table_if_not_exists(table);
//     char ***data = get_rows_from_key(table, "team_uuid", clients[cci].context_team_uuid);
//     clients[cci].switch_read_write = true;
//     for (int i = 0; data[i] != NULL; i++) {
//         char *tmp = strdup(data[i][0]);
//         strcat(tmp, " ");
//         strcat(tmp, data[i][1]);
//         strcat(tmp, "\n\r");
//         save_string(clients[cci].write_buffer, tmp);
//         handle_client_write_message(&clients[cci]);
//         free(tmp);
//         usleep(10000);
//     }
//     clients[cci].switch_read_write = false;
//     destroy_table(table);
// }

// void fea_info_thread(client_t *clients, char **command, int cci)
// {
//     table_t *table = create_table_struct("threads", (const char *[]){"thread_title", "thread_uuid", "thread_message", "channel_uuid", "team_uuid", NULL});
//     create_table_if_not_exists(table);
//     char ***data = get_rows_from_key(table, "channel_uuid", clients[cci].context_channel_uuid);
//     clients[cci].switch_read_write = true;
//     for (int i = 0; data[i] != NULL; i++) {
//         char *tmp = strdup(data[i][0]);
//         strcat(tmp, " ");
//         strcat(tmp, data[i][1]);
//         strcat(tmp, "\n\r");
//         save_string(clients[cci].write_buffer, tmp);
//         handle_client_write_message(&clients[cci]);
//         free(tmp);
//         usleep(10000);
//     }
//     clients[cci].switch_read_write = false;
//     destroy_table(table);
// }

void fea_info(client_t *clients, char **command, int cci)
{
    return;
}
// {
//     if (clients[cci].context_team_uuid == NULL) {
//         fea_info_user(clients, command, cci);
//         return;
//     } else if (clients[cci].context_channel_uuid == NULL) {
//         fea_info_team(clients, command, cci);
//         return;
//     } else {
//         if (clients[cci].context_thread_uuid == NULL) {
//             fea_info_channel(clients, command, cci);
//             return;
//         }
//     }
//     fea_info_thread(clients, command, cci);
// }
