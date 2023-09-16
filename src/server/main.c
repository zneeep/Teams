/*
** EPITECH PROJECT, 2023
** main.c
** File description:
** Created by Arthur MAQUET
** First edition:
** 14:02:32 08/04/2023
*/

#include <stdio.h>
#include <stdlib.h>


#include "../../include/common/ip_port_validation.h"
#include "../../include/server/connections/create_server_socket.h"
#include "../../include/server/messages/handle_connections.h"
void fea_load_users(void);

#ifdef EXIT_FAILURE
#undef EXIT_FAILURE
#endif
#define EXIT_FAILURE 84

static void print_help(const char *program_name, FILE *stream) {
  static const char *help
      = "USAGE: ./%s port\n"
        "\tport\tis the port number on which the server socket listens.\n";

  fprintf(stream, help, program_name);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    print_help(argv[0], stderr);
    return (EXIT_FAILURE);
  }
  if (!is_valid_port(argv[1])) {
    fprintf(stderr, "Invalid port number: %s\n", argv[1]);
    return (EXIT_FAILURE);
  }

  int socket_fd;
  if (!create_server_socket(argv[1], &socket_fd)) {
    return (EXIT_FAILURE);
  }
  fea_load_users();
  handle_connections(socket_fd, argv[1]);
  return (EXIT_SUCCESS);
}
