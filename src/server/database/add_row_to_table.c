/*
** EPITECH PROJECT, 2023
** add_row_to_table.c
** File description:
** Created by Arthur MAQUET
** First edition:
** 01:17:04 22/04/2023
*/

#include <stdio.h>
#include <stdlib.h>
#include "../../../include/server/database/common_functions.h"
#include "../../../include/server/database/tables.h"

/**
 * @brief Add a row to a table
 * @param filename The name of the file
 * @param row The row to add (array of strings)
 * @return true if the row was added, false otherwise
 */
bool add_row_to_table(const char *filename, const char *row[]) {
  char *filepath = get_file_path(filename);
  if (filepath == NULL || !file_exists(filepath)) return false;

  FILE *file = fopen(filepath, "a");
  if (file == NULL) {
    free(filepath);
    return false;
  }

  for (size_t i = 0; row[i] != NULL; i++) {
    if (i != 0) fprintf(file, "%s", SEPARATOR);
    fprintf(file, "%s", row[i]);
  }
  fprintf(file, "\n");
  fclose(file);
  free(filepath);
  return true;
}