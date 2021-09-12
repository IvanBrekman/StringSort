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
//! \param n_strings pointer to value where will be written size of file
//! \return pointer to array of strings
//! \note if function wont be able to open file NULL_FILE_PTR will be written in n_strings
//!       and function will return NULL
char* get_data_from_file(char* filename, int* f_size) {
    assert(filename != NULL);
    assert(f_size != NULL);

    FILE* file = open_file(filename, "r");
    if (file == NULL) {
        *f_size = NULL_FILE_PTR;
        return NULL;
    }

    struct stat buff;
    stat(filename, &buff);
    *f_size = (int)buff.st_size;

    char* data = (char*)calloc(*f_size + 1, sizeof(char));
    if (data[buff.st_size - 1] != '\n') {
        data[buff.st_size] = '\n';
        (*f_size)++;
    }

    fread(data, sizeof(char), *f_size, file);
    
    fclose(file);
    return data;
}


//! Function writes strings to file
//! \param filename pointer to string of path to file
//! \param data pointer to array of strings, whose will be written in file
//! \param n_strings number of strings to write
//! \return number of written strings
//! \note if function cant be able to open file, it will return NULL_FILE_PTR
int write_strings_to_file(char* filename, char mode[5], char** data, int n_strings) {
    assert(filename != NULL);
    assert(data != NULL);
    assert(n_strings >= 0);

    FILE* file = open_file(filename, mode);
    if (file == NULL) {
        return NULL_FILE_PTR;
    }

    if (n_strings == 0) {
        fputs("", file);
        return 0;
    }

    int n_wr_strings = 0;
    for (n_wr_strings = 0; n_wr_strings < n_strings; n_wr_strings++) {
        fputs(data[n_wr_strings], file);
        fputs("\n", file);
    }

    fclose(file);
    return n_wr_strings;
}
