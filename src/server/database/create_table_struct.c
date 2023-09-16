/*
** EPITECH PROJECT, 2023
** create_table_struct.c
** File description:
** Created by Arthur MAQUET
** First edition:
** 00:15:52 22/04/2023
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../../include/server/database/common_functions.h"
#include "../../../include/server/database/tables.h"

#define COLUMN_SEPARATOR ";"

/***
 * @brief Check if the columns of a file are the same as the given columns
 * @param file The file to check
 * @param column_names The name of the columns of the table
 * @return true if the columns are the same, false otherwise
 */
bool check_columns(FILE *file, const char *column_names[]) {
  char line[1024];
  if (fgets(line, sizeof(line), file) == NULL) {
    return false;
  }

  char *token;
  int col_index = 0;

  token = strtok(line, COLUMN_SEPARATOR);
  while (token != NULL) {
    if (strcmp(token, column_names[col_index]) != 0) return false;
    col_index++;
    token = strtok(NULL, COLUMN_SEPARATOR);
  }
  return true;
}

/***
 * @brief Create a new file with the given columns
 * @param filepath The path of the file to create
 * @param column_names The name of the columns of the table
 * @return true if the file was created, false otherwise
 */
static bool create_new_file_with_columns(char filepath[256],
                                         const char *column_names[]) {
  FILE *file = fopen(filepath, "w");
  if (file == NULL) return false;

  for (int i = 0; column_names[i] != NULL; i++) {
    if (i != 0) fputs(COLUMN_SEPARATOR, file);
    fputs(column_names[i], file);
  }
  fputs("\n", file);
  fclose(file);
  return true;
}

/**
 * @brief Create a table in the database folder if it doesn't exist
 * @param filename The name of the file to create
 * @param column_names The name of the columns of the table
 * @return true if everything is okay for the next commands, false otherwise
 */
bool create_table_if_needed(char *filename, const char *column_names[])
{
    char *filepath = get_file_path(filename);
    bool return_value;

    if (file_exists(filepath)) {
        FILE *file = fopen(filepath, "r");
        if (file == NULL) return false;
        return_value = check_columns(file, column_names);
        fclose(file);
        free(filepath);
    } else {
        return_value = create_new_file_with_columns(filepath, column_names);
        free(filepath);
    }
    return return_value;
}