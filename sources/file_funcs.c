//
// Created by ivanbrekman on 26.08.2021.
//

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include "../headers/string_funcs.h"
#include "../headers/file_funcs.h"
#include "../headers/standart_str_func.h"

#define dbg(code) do{ printf("%s:%d\n", __FILE__, __LINE__); code }while(0) // liberror.h (color)

/*
 * \brief Функция открывает файл, находящийся в filename, и возвращает указатель на FILE структуру
 * \param [in] filename - указатель на строку пути к файлу
 * \param [in] mode     - указатель на строку мода для чтения
 * \return              - Указатель на структуру FILE
 * \note Если файл не открывается, то вызовет assert
 */
FILE* open_file(c_string filename, char mode[5]) {
    FILE* file;
    file = fopen(filename, mode);

    assert(file != NULL);

    return file;
}

/*
 * \brief Функция считает количество строк в файле
 * \param [in] filename - указатель на строку пути к файлу
 * \return              - int количество строк в файле
 * \note Если файл не открывается, то вернет NULL_FILE_PTR
 */
int count_lines(c_string filename) {
    FILE* file = open_file(filename, "r");
    if (file == NULL) return NULL_FILE_PTR;
    char str[MAX_STRING_LENGTH] = {};

    int lines = 0;
    while (fgets(str, MAX_STRING_LENGTH, file) != NULL) lines++;

    fclose(file);

    return lines;
}

/*
 * \brief Функция возвращает массив строк (указателей на массив char), прочитанных с файла
 * \param [in] filename   - указатель на строку пути к файлу
 * \param [out] n_strings - int указатель, куда запишется количество строк в файле
 * \return                - массив строк (указателей на массив char)
 * \note Если файл не открывается, то в n_strings запишется NULL_FILE_PTR, а вернется NULL
 */
c_string* get_strings_from_file(c_string filename, int* n_strings) {
    FILE* file = open_file(filename, "r");
    if (file == NULL) {
        *n_strings = NULL_FILE_PTR;
        return NULL;
    }

    *n_strings = count_lines(filename);
    c_string* result = calloc(*n_strings, sizeof(c_string));

    int i = 0;
    char str[MAX_STRING_LENGTH] = {};
    while (my_fgets(str, MAX_STRING_LENGTH, file) != NULL) {
        printf("%s\n", str);
        result[i] = calloc(MAX_STRING_LENGTH, sizeof(char));

        int real_size = my_strlen(str) + 1;
        result[i] = realloc(result[i], real_size * sizeof(char));
        my_strcpy(result[i++], str);
    }
    fclose(file);

    return result;
}


/*
 * \brief Функция записывает массив строк в указанный файл
 * \param [in] filename  - указатель на строку пути к файлу
 * \param [in] data      - указатель на массив строк (на массив указателей), которые надо записать
 * \param [in] n_strings - int количество записываемых строк
 * \return               - количество записанных строк
 * \note Если файл не открывается, то вернет NULL_FILE_PTR
 */
int write_strings_to_file(c_string filename, c_string* data, int n_strings) {
    FILE* file = open_file(filename, "w");
    if (file == NULL) return NULL_FILE_PTR;

    int n_wr_strings;
    for (n_wr_strings = 0; n_wr_strings < n_strings; n_wr_strings++) {
        fputs(data[n_wr_strings], file);
        fputs("\n", file);
    }

    return n_wr_strings;
}
