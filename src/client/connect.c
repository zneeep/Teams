/*
** EPITECH PROJECT, 2023
** connect.c
** File description:
** Created by Arthur MAQUET
** First edition:
** 14:00:16 17/04/2023
*/

#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int get_socket_fd(const char *ip_address, int port) {
  int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_fd < 0) {
    perror("Error creating socket");
    return (-1);
  }

  struct sockaddr_in server = {
      .sin_family = AF_INET,
      .sin_port = htons(port),
      .sin_addr.s_addr = inet_addr(ip_address)
  };
  if (connect(socket_fd, (struct sockaddr *)&server, sizeof(server)) < 0) {
    perror("Error connecting to server");
    close(socket_fd);
    return (-1);
  }

  return (socket_fd);
}
