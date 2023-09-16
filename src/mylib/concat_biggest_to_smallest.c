/*
** EPITECH PROJECT, 2023
** B-NWP-400-LYN-4-1-myteams-lucas.siraux
** File description:
** fea_send
*/

#include <string.h>
#include <stdlib.h>

char* concat_biggest_to_smallest(const char* str1, const char* str2)
{
    int cmp = strcmp(str1, str2);
    const char* biggest = (cmp > 0) ? str1 : str2;
    const char* smallest = (cmp > 0) ? str2 : str1;
    size_t biggest_len = strlen(biggest);
    size_t smallest_len = strlen(smallest);
    char* result = (char*) malloc((biggest_len + smallest_len + 1) * sizeof(char));
    strcpy(result, biggest);
    strcat(result, smallest);
    return result;
}