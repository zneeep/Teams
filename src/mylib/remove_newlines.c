/*
** EPITECH PROJECT, 2023
** teams
** File description:
** remove_newlines
*/

#include <string.h>

char *remove_newlines(char *str)
{
  size_t len = strlen(str);
  while (len > 0 && str[len - 1] == '\n')
    str[--len] = '\0';

  return str;
}
