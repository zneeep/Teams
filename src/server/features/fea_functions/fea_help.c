/*
** EPITECH PROJECT, 2023
** fea_help.c
** File description:
** Created by Arthur MAQUET
** First edition:
** 21:05:11 08/04/2023
*/

#include "../../../../include/server/database/common_functions.h"
#include "../../../../include/server/database/tables.h"
#include "../../../../include/server/messages/client_messages.h"
#include "../../../../include/server/feature/save_string.h"

void fea_help(client_t *clients, __attribute__((unused))char **command, int cci)
{
  const char *help
      = "- /login [“user_name”] : set the user_name used by client\r\n"
        "- /logout : disconnect the client from the server\r\n"
        "- /users : get the list of all users that exist on the domain\r\n"
        "- /user [“user_uuid”] : get details about the requested user\r\n"
        "- /send [“user_uuid”] [“message_body”] : send a message to specific user\r\n"
        "- /messages [“user_uuid”] : list all messages exchanged with the specified user\r\n"
        "- /subscribe [“team_uuid”] : subscribe to the events of a team and its sub directories (enable reception of all events from a team)\r\n"
        "- /subscribed ?[“team_uuid”] : list all subscribed teams or list all users subscribed to a team\r\n"
        "- /unsubscribe [“team_uuid”] : unsubscribe from a team\r\n"
        "- /use ?[“team_uuid”] ?[“channel_uuid”] ?[“thread_uuid”] : Sets the command context to a team/channel/thread\r\n"
        "- /create : based on the context, create the sub resource\r\n"
        "- /list : based on the context, list all the sub resources\r\n"
        "- /info : based on the context, display details of the current resource\r\n";

  save_string(clients[cci].write_buffer, help);
}
