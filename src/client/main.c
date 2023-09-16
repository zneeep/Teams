/*
** EPITECH PROJECT, 2023
** main.c
** File description:
** Created by Arthur MAQUET
** First edition:
** 13:04:18 08/04/2023
*/

#include <stdio.h>
#include <stdlib.h>

#include "common/ip_port_validation.h"
#include "client/connect.h"
#include "client/send_messages.h"

#ifdef EXIT_FAILURE
#undef EXIT_FAILURE
#endif
#define EXIT_FAILURE 84

static void print_help(const char *program_name, FILE *stream) {
  static const char *help
      = "USAGE: ./%s ip port\n"
        "\tip\tis the server ip address on which the server socket listens\n"
        "\tport\tis the port number on which the server socket listens\n";

  fprintf(stream, help, program_name);
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    print_help(argv[0], stderr);
    return (EXIT_FAILURE);
  }
  if (!is_valid_ipv4_address(argv[1])) {
    fprintf(stderr, "Invalid IP address: %s\n", argv[1]);
    return (EXIT_FAILURE);
  } else if (!is_valid_port(argv[2])) {
    fprintf(stderr, "Invalid port number: %s\n", argv[2]);
    return (EXIT_FAILURE);
  }

  int socket_fd = get_socket_fd(argv[1], atoi(argv[2]));
  send_messages(socket_fd);

  return (EXIT_FAILURE);
}
