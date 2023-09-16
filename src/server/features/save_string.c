/*
** EPITECH PROJECT, 2023
** save_string.c
** File description:
** Created by Arthur MAQUET
** First edition:
** 20:16:25 11/04/2023
*/

#include <string.h>

#include "../../../include/server/utils/messages.h"

void save_string(char write_buffer[BUFSIZ], const char *buffer)
{
  size_t length = strnlen(buffer, BUFSIZ-1);
  memcpy(write_buffer, buffer, length);
  write_buffer[length] = '\0';
}
