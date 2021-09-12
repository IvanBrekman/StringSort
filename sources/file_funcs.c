//
// Created by ivanbrekman on 26.08.2021.
//

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <sys/stat.h>

#include "../headers/string_funcs.h"
#include "../headers/file_funcs.h"
#include "../headers/standard_str_func.h"
#include "../headers/errorlib.h"

//! Function opens file
//! \param filename path to file to open
//! \param mode mode with which open file
//! \return pointer to opened file (FILE*)
//! \note call assert if function cannot open file on the path filename
FILE* open_file(char* filename, char mode[5]) {
    assert(filename != NULL);

    FILE* file;
    file = fopen(filename, mode);

    assert(file != NULL);

    return file;
}

//! Function reads strings from file
//! \param filename pointer to string of path to file
//! \param n_strings pointer to value where will be written the number of strings
//! \return pointer to array of strings
//! \note if function wont be able to open file NULL_FILE_PTR will be written in n_strings
//!       and function will return NULL
char** get_strings_from_file(char* filename, int* n_strings) {
    assert(filename != NULL);
    assert(n_strings != NULL);

    FILE* file = open_file(filename, "r");
    if (file == NULL) {
        *n_strings = NULL_FILE_PTR;
        return NULL;
    }

    struct stat buff;
    stat(filename, &buff);
    int f_size = (int)buff.st_size;
    printf("%zd\n", buff.st_size);

    char* data = calloc(f_size + 1, sizeof(char));
    if (data[buff.st_size - 1] != '\n') {
        data[buff.st_size] = '\n';
        f_size++;
    }

    fread(data, sizeof(char), f_size, file);
    *n_strings = replace(data, '\n', '\0', -1);
    printf("lines: %d\n%s\n", *n_strings, data);

    char** result = calloc(*n_strings, sizeof(char*));
    load_string_pointers(result, data, f_size);
    
    fclose(file);
    return result;
}


//! Function writes strings to file
//! \param filename pointer to string of path to file
//! \param data pointer to array of strings, whose will be written in file
//! \param n_strings number of strings to write
//! \return number of written strings
//! \note if function cant be able to open file, it will return NULL_FILE_PTR
int write_strings_to_file(char* filename, char** data, int n_strings) {
    assert(filename != NULL);
    assert(data != NULL);
    assert(n_strings > 0);

    FILE* file = open_file(filename, "w");
    if (file == NULL) {
        return NULL_FILE_PTR;
    }

    int n_wr_strings = 0;
    for (n_wr_strings = 0; n_wr_strings < n_strings; n_wr_strings++) {
        if (cmp_string(data[n_wr_strings], "") == 0 || !letters_in_string(data[n_wr_strings])) {
            continue;
        }
        fputs(data[n_wr_strings], file);
        fputs("\n", file);
    }

    return n_wr_strings;
}
