/*
** EPITECH PROJECT, 2023
** teams
** File description:
** free_data
*/

#include <stdlib.h>

void free_data(char ***arr_ptr)
{
    if (arr_ptr == NULL) {
        return;
    }

    char **arr = *arr_ptr;
    if (arr == NULL) {
        return;
    }

    int i = 0;
    while (arr[i] != NULL) {
        free(arr[i]);
        i++;
    }

    free(arr);
    *arr_ptr = NULL;
}