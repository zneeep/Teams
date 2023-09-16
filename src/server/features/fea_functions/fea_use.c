/*
** EPITECH PROJECT, 2023
** B-NWP-400-LYN-4-1-myteams-lucas.siraux
** File description:
** fea_use
*/

#include "../../../../include/server/utils/messages.h"
#include "../../../../include/server/database/common_functions.h"
#include "../../../../include/server/database/tables.h"
#include <uuid/uuid.h>
#include <stdlib.h>
#include <string.h>

void fea_set_thread(client_t *clients, char *thread_uuid, int cci)
{
    create_table_if_needed("threads", (const char *[]){"thread_title", "thread_uuid", "thread_message", "channel_uuid", NULL});
    clients[cci].context_thread_uuid = strdup(thread_uuid);
}

void fea_set_channel(client_t *clients, char *channel_uuid, int cci)
{
    create_table_if_needed("channels", (const char *[]){"channel_name", "channel_uuid", "description", "team_uuid", NULL});
    clients[cci].context_channel_uuid = strdup(channel_uuid);
}

void fea_set_team(client_t *clients, char *team_uuid, int cci)
{
    create_table_if_needed("teams", (const char *[]){"team_name", "team_uuid", "description", NULL});
    clients[cci].context_team_uuid = strdup(team_uuid);
}

void fea_use(client_t *clients, char **command, int cci)
{
    clients[cci].context_channel_uuid = NULL;
    clients[cci].context_team_uuid = NULL;
    clients[cci].context_thread_uuid = NULL;

    for (int i = 1; command[i] != NULL; i++) {
        if (i == 1)
            fea_set_team(clients, command[i], cci);
        else if (i == 2)
            fea_set_channel(clients, command[i], cci);
        else 
            fea_set_thread(clients, command[i], cci);
    }
}
