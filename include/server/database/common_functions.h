/*
** EPITECH PROJECT, 2023
** common_functions.h
** File description:
** Created by Arthur MAQUET
** First edition:
** 01:21:01 22/04/2023
*/

#ifndef B_NWP_400_LYN_4_1_MYTEAMS_LUCAS_SIRAUX_INCLUDE_SERVER_DATABASE_COMMON_FUNCTIONS_H_
#define B_NWP_400_LYN_4_1_MYTEAMS_LUCAS_SIRAUX_INCLUDE_SERVER_DATABASE_COMMON_FUNCTIONS_H_

#include <stdbool.h>

#define DATABASE_PATH "database"
#define SEPARATOR ";"

char *get_file_path(const char *filename);
bool file_exists(const char *filename);

#endif //B_NWP_400_LYN_4_1_MYTEAMS_LUCAS_SIRAUX_INCLUDE_SERVER_DATABASE_COMMON_FUNCTIONS_H_