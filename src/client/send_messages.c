/*
** EPITECH PROJECT, 2023
** B-NWP-400-LYN-4-1-myteams-lucas.siraux
** File description:
** send_messages
*/

#include <stdio.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "../../include/mylib/mylib.h"
void interpret_command(char **command);

#ifdef EXIT_FAILURE
#undef EXIT_FAILURE
#endif
#define EXIT_FAILURE 84

#define DELIMITER "\r\n"

int global_socket_fd;

static void replace_with_delimiter(char **message_ptr) {
  char *message = *message_ptr;
  char *newline_char = strchr(message, '\n');

  if (newline_char == NULL) return;
  if (newline_char > message && *(newline_char - 1) == '\r') newline_char--;
  *newline_char = '\0';

  size_t new_size = newline_char - message + strlen(DELIMITER) + 1;
  message = realloc(message, new_size);
  if (message == NULL) {
    perror("Error reallocating memory");
    exit(EXIT_FAILURE);
  }
  strcat(message, DELIMITER);

  *message_ptr = message;
}

void close_connection_and_exit(__attribute__((unused)) int sig) {
  const char message[] = "/logout\r\n";

  if (global_socket_fd != -1) {
    send(global_socket_fd, message, strlen(message), 0);
    close(global_socket_fd);
  }
  exit(EXIT_SUCCESS);
}

static char *get_message(void) {
  char *message = NULL;
  size_t size = 0;

  if (getline(&message, &size, stdin) == -1) {
    perror("Error getting message");
    return (NULL);
  }

  replace_with_delimiter(&message);
  return (message);
}

void handle_user_input(int socket_fd) {
  char *message = get_message();
  if (message == NULL) return;
  if (send(socket_fd, message, strlen(message), 0) < 0) {
    perror("Error sending message");
    return;
  }
  free(message);
}

void handle_server_message(int socket_fd) {
  char buffer[1024] = {0};
  int received_bytes = recv(socket_fd, buffer, sizeof(buffer) - 1, 0);

  if (received_bytes < 0) {
      perror("Error receiving message");
      return;
  } else if (received_bytes == 0) {
    exit(EXIT_FAILURE); 
  } else {
    buffer[received_bytes] = '\0';
    char **command = str_to_wrd_arr(buffer);
    interpret_command(command);
  }
}

void process_io(int socket_fd, fd_set *read_fds) {
  if (FD_ISSET(socket_fd, read_fds)) {
    handle_server_message(socket_fd);
  }
  if (FD_ISSET(fileno(stdin), read_fds)) {
    handle_user_input(socket_fd);
  }
}

void send_messages(int socket_fd) {
  global_socket_fd = socket_fd;
  signal(SIGINT, close_connection_and_exit);

  fd_set read_fds;
  int max_fd = socket_fd > fileno(stdin) ? socket_fd : fileno(stdin);

  while (true) {
    FD_ZERO(&read_fds);
    FD_SET(socket_fd, &read_fds);
    FD_SET(fileno(stdin), &read_fds);

    if (select(max_fd + 1, &read_fds, NULL, NULL, NULL) < 0) {
      perror("Error with select");
      return;
    }

    process_io(socket_fd, &read_fds);
  }
}
