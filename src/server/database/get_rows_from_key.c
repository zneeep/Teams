/*
** EPITECH PROJECT, 2023
** get_rows_from_key.c
** File description:
** Created by Arthur MAQUET
** First edition:
** 01:37:34 22/04/2023
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../../include/server/database/common_functions.h"
#include "../../../include/server/database/tables.h"

/**
 * @brief Check if a value matches a value in a line
 * @param line The line to check
 * @param value The value to check
 * @param index The index of the value to check
 * @return true if the value matches, false otherwise
 */

static bool value_matches(char *line, const char *value, int index) {
  char *line_copy = strdup(line);
  char *temp_line = line_copy;
  char *token;
  int cur_index = 0;
  line_copy[strcspn(line_copy, "\n")] = '\0';
  while ((token = strsep(&temp_line, SEPARATOR)) != NULL) {
    if (cur_index == index && strcmp(token, value) == 0) {
      free(line_copy);
      return true;
    }
    cur_index++;
  }

  free(line_copy);
  return false;
}

/**
 * @brief Get the index of a key in a line
 * @param line The line to check
 * @param key The key to check
 * @return The index of the key, or -1 if the key was not found
 */

static int get_key_index(char *line, const char *key) 
{
  if (key == NULL)
    return -1;
  char *line_copy = strdup(line);
  char *temp_line = line_copy;
  char *token;
  int index = 0;
  line_copy[strcspn(line_copy, "\n")] = '\0';
  while ((token = strsep(&temp_line, SEPARATOR)) != NULL) {
    if (strcmp(token, key) == 0) {
      free(line_copy);
      return index;
    }
    index++;
  }
  free(line_copy);
  return -1;
}

/**
 * @brief Add a row to an array of rows
 * @param rows The reference to the array of rows
 * @param row_count The reference to the number of rows
 * @param line The line to add
 */

void add_row(char ****rows, char *line, int row_index) 
{
  char *line_copy = strdup(line);
  char *temp_line = line_copy;
  char *token;
  int column_index = 0;
  line_copy[strcspn(line_copy, "\n")] = '\0';
  while ((token = strsep(&temp_line, SEPARATOR)) != NULL) {
    (*rows)[row_index][column_index] = strdup(token);
    column_index++;
  }
  (*rows)[row_index][column_index] = NULL;
  free(line_copy);
}

/**
 * @brief Get all the rows from a table that have a specific value for a key
 * @param filename The name of the file
 * @param key The key to search for
 * @param value The value to search for
 * @return An array of rows of all the rows that have the value for the key,
 * or NULL if an error occurred
 */

int get_number_of_rows(const char *filename, const char *key, const char *value)
{  
  int return_value = 0;
  char *file_path = get_file_path(filename);

  if (file_path == NULL || !file_exists(file_path)) return 0;

  FILE *file = fopen(file_path, "r");

  if (file == NULL) return 0;

  char line[BUFSIZ];
  fgets(line, sizeof(line), file);
  int key_index = get_key_index(line, key);

  if (key_index == -1 && key != NULL) return 0;

  if (key == NULL || value == NULL) {
    while (fgets(line, sizeof(line), file))
      return_value++;
  } else {
      while (fgets(line, sizeof(line), file)) {
        if (value_matches(line, value, key_index))
            return_value++;
        }
    }
    fclose(file);
    free(file_path);
    return return_value;
}

char ***get_rows_from_key(const char *filename, const char *key,
                          const char *value, int column_count) {
  
  int number_rows = get_number_of_rows(filename, key, value);
  if (number_rows == 0)
    return NULL;
  char ***data = malloc(sizeof(char **) * (number_rows + 1));

  for (int i = 0; i < number_rows; i++)
    data[i] = malloc(sizeof(char *) * (column_count) + 1);

  data[number_rows] = NULL;
  char *file_path = get_file_path(filename);
  if (file_path == NULL || !file_exists(file_path)) return NULL;

  FILE *file = fopen(file_path, "r");
  if (file == NULL) return NULL;

  char line[BUFSIZ];
  fgets(line, sizeof(line), file);
  int key_index = get_key_index(line, key);
  char ****ptr = &data;
  int row_index = 0;

  if (key == NULL || value == NULL) {
    while (fgets(line, sizeof(line), file)) {
      add_row(ptr, line, row_index);
      row_index++;
    } 
  } else {
      while (fgets(line, sizeof(line), file)) {
        if (value_matches(line, value, key_index)) {
            add_row(ptr, line, row_index);
            row_index++;
        }
      }
  }
  fclose(file);
  free(file_path);
  return data;
}
