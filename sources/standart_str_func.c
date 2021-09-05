//
// Created by ivanbrekman on 27.08.2021.
//

#include <stdio.h>
#include <malloc.h>
#include <assert.h>

#include "../headers/standart_str_func.h"
#define dbg(code) do{ printf("%s:%d\n", __FILE__, __LINE__); code }while(0) // liberror.h (color)

int my_puts(const char* str) { // big endian, little endian (порядок байтов в памяти)
    fwrite(str, sizeof(char), my_strlen(str), stdout);
    fwrite("\n", sizeof(char), 1, stdout);

    return '\n';
}

char* my_strchr(const char* str, int ch) {
    int i = 0;

    do {
        if (str[i] == ch)
            return (char*) &str[i];
    } while (str[i++] != '\0');

    return NULL;
}

char* my_strschr(const char* str, int ch, int start_index) {
    do {
        if (str[start_index] == ch) {
            return  (char*) &str[start_index];
        }
    } while (str[start_index++] != '\0');

    return NULL;
}

int my_strlen(const char* str) {
    return (int) (my_strchr(str, '\0') - str);
}

char* my_strcpy(char* dest, const char* src) {
    int i = 0;
    do {
        dest[i] = src[i];
    } while (src[i++] != '\0');

    return dest;
}

char* my_strncpy(char* dest, const char* src, size_t n) {
    int i = 0;
    do {
        dest[i] = src[i];
    } while (i < n ? src[i++] != '\0' : 0);

    return dest;
}

char* my_strcat(char* dest, const char* src) {
    int index = my_strlen(dest);
    int length = my_strlen(src);

    for (int i = 0; i < length; i++, index++)
        dest[index] = src[i];
    dest[index] = '\0';

    return dest;
}

char* my_strncat(char* dest, const char* src, size_t n) {
    int index = my_strlen(dest);
    int length = my_strlen(src);

    for (int i = 0; i < n && i < length; i++, index++)
        dest[index] = src[i];
    dest[index] = '\0';

    return dest;
}

char* my_strdup(const char* str) {
    char* new_string = calloc(my_strlen(str) + 1, sizeof(char));

    my_strcpy(new_string, str);

    return new_string;
}

char* my_fgets(char* str, int num, FILE* stream) {
    assert(num > 0);
    assert(str != NULL);

    int elements_to_read = 5;
    int index = 0;

    char* new_line_ptr = NULL;
    while (new_line_ptr == NULL && num - 1 > 0) {
        int n_read = elements_to_read < num - 1 ? elements_to_read : num - 1;
        size_t bytes = fread(&str[index], sizeof(char), n_read, stream);

        index += (int) bytes;
        num -= (int) bytes;
        if (bytes < n_read) {
            fseek(stream, 0, SEEK_END);
            if (bytes == 0 && index == 0) {
                return NULL;
            }

            num = 0;
            str[index] = '\0';
        }
        if ((new_line_ptr = my_strschr(str, '\n', (int) (index - bytes))) != NULL) {
            int excess_chars = (int)((char*) &str[index - 1] - new_line_ptr);
            str[index - 1 - excess_chars] = '\0';
            fseek(stream, -excess_chars, SEEK_CUR);
        }
    }

    return str;
}