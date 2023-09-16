/*
** EPITECH PROJECT, 2023
** B-NWP-400-LYN-4-1-myteams-lucas.siraux
** File description:
** fea_user
*/

#include "../../../../include/server/utils/messages.h"
#include "../../../../include/server/database/common_functions.h"
#include "../../../../include/server/database/tables.h"
#include "../../../../include/server/feature/fea_functions.h"

// void fea_user(client_t *clients, char **command, int cci)
// {
//     table_t *table = create_table_struct("users", (const char *[]){"username", "user_uuid", NULL});
//     create_table_if_not_exists(table);
//     char ***data = get_rows_from_key(table, "user_uuid", command[1]);
//     for (int i = 0; data[1][i] != NULL; i++) {
//         if (strcmp(data[1][i], user_uuid) == 0 && data[2][i] != NULL) {
//             printf("%s\n", data[2][i]);
//         } else if (strcmp(data[1][i], user_uuid) == 0 && data[2][i] == NULL) {
//             printf("No description for the requested user\n");
//         }
//     }
// }