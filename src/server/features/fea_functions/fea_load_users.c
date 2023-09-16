/*
** EPITECH PROJECT, 2023
** B-NWP-400-LYN-4-1-myteams-lucas.siraux
** File description:
** fea_load_users
*/

#include "../../../../include/server/utils/messages.h"
#include "../../../../include/server/database/common_functions.h"
#include "../../../../include/server/database/tables.h"
#include <uuid/uuid.h>
#include <stdlib.h>
#include "../../../../include/mylib/mylib.h"

void fea_load_users(void)
{
    // Still have to add the NULL option in order to get all the values of a single table or add a key that's is same everyone
    create_table_if_needed("users", (const char *[]){"username", "user_uuid", NULL});
    char ***data = get_rows_from_key("users", NULL, NULL, 2);
    if (data == NULL)
        return;
    for (int i = 0; data[i] != NULL; i++)
        server_event_user_loaded(data[i][1], data[i][0]);
    free_data(data);
}