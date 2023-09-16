/*
** EPITECH PROJECT, 2023
** tables.h
** File description:
** Created by Arthur MAQUET
** First edition:
** 01:17:24 22/04/2023
*/

#ifndef B_NWP_400_LYN_4_1_MYTEAMS_LUCAS_SIRAUX_INCLUDE_SERVER_DATABASE_TABLES_H_
#define B_NWP_400_LYN_4_1_MYTEAMS_LUCAS_SIRAUX_INCLUDE_SERVER_DATABASE_TABLES_H_

#include <stdbool.h>

bool create_table_if_needed(char *filename, const char *column_names[]);
bool add_row_to_table(const char *filename, const char *row[]);
char ***get_rows_from_key(const char *filename, const char *key,
                          const char *value, int column_count);
#endif //B_NWP_400_LYN_4_1_MYTEAMS_LUCAS_SIRAUX_INCLUDE_SERVER_DATABASE_TABLES_H_