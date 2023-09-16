#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int add_quoted(int num_words, char **words, const char *str, int i)
{
    int index = i + 1;
    while (str[index] != '\"' && str[index] != 0)
        index++;
    words[num_words] = malloc(sizeof(char) * (index - i));
    if (words[num_words] == NULL) {
        return -1;
    }
    strncpy(words[num_words], &str[i+1], index-i-1);
    words[num_words][index-i-1] = 0;
    return index;
}

int add_string(int num_words, char **words, const char *str, int i)
{
    int index = i;
    while (isalnum(str[index]) || str[index] == '/' || str[index] == '-')
        index++;
    words[num_words] = malloc(sizeof(char) * (index - i + 1));
    if (words[num_words] == NULL) {
        return -1;
    }
    strncpy(words[num_words], &str[i], index-i);
    words[num_words][index-i] = 0;
    return index;
}

// int get_number_of_word(const char *str)
// {
//     int num_words = 0;
//     for (int i = 0; str[i] != 0 && str[i] != '\n'; i++) {
//         if (str[i] == '\"') {
//             while (str[i] !=)
//             if (i == -1) {
//                 return NULL;
//             }
//             num_words++;
//         } else if (isalnum(str[i]) || str[i] == '/') {
//             words = realloc(words, sizeof(char *) * (num_words + 2));
//             if (words == NULL) {
//                 return NULL;
//             }
//             i = add_string(num_words, words, str, i);
//             if (i == -1) {
//                 return NULL;
//             }
//             num_words++;
//         }
//     }
//     words[num_words] = NULL;
//     return words;

// }

char **str_to_wrd_arr(const char *str)
{
    char **words = malloc(sizeof(char *));
    if (words == NULL) {
        return NULL;
    }
    int num_words = 0;
    for (int i = 0; str[i] != 0 && str[i] != '\n'; i++) {
        if (str[i] == '\"') {
            words = realloc(words, sizeof(char *) * (num_words + 2));
            if (words == NULL) {
                return NULL;
            }
            i = add_quoted(num_words, words, str, i);
            if (i == -1) {
                return NULL;
            }
            num_words++;
        } else if (isalnum(str[i]) || str[i] == '/') {
            words = realloc(words, sizeof(char *) * (num_words + 2));
            if (words == NULL) {
                return NULL;
            }
            i = add_string(num_words, words, str, i);
            if (i == -1) {
                return NULL;
            }
            num_words++;
        }
    }
    words[num_words] = NULL;
    return words;
}
