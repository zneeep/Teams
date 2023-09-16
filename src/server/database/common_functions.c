/*
** EPITECH PROJECT, 2023
** common_functions.c
** File description:
** Created by Arthur MAQUET
** First edition:
** 01:20:50 22/04/2023
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../../include/server/database/common_functions.h"
#include "../../../include/server/database/tables.h"

/**
 * @brief Get the path of a file in the database
 * @param filename The name of the file
 * @return The path of the file in the database, or NULL if an error occurred
 */
char *get_file_path(const char *filename) {
  size_t len = strlen(DATABASE_PATH) + strlen(filename) + 6;
  char *path = malloc(sizeof(char)*len);

  if (path == NULL) return NULL;
  snprintf(path, len, "%s/%s.csv", DATABASE_PATH, filename);
  return path;
}

/**
 * @brief Check if a file exists
 * @param filename The file to check
 * @return true if the file exists, false otherwise
 */
bool file_exists(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (file != NULL) {
    fclose(file);
    return true;
  }
  return false;
}