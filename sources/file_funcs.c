//
// Created by ivanbrekman on 26.08.2021.
//

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <wchar.h>
#include <sys/stat.h>

#include "../headers/string_funcs.h"
#include "../headers/file_funcs.h"
#include "../headers/errorlib.h"


void free_text(struct Text* data) {
    data->data = NULL;
    data->data_size = -1;

    for (int i = 0; i < data->lines; i++) {
        free_string(&(data->text[i]));
    }
    data->text = NULL;
    data->lines = -1;

    data = NULL;
}
void free_string(struct String* string) {
    string->string_ptr = NULL;
    string->len = -1;

    string = NULL;
}

//! Function prints text from struct
//! \param data pointer to struct
void print_text(const struct Text* data) {
    assert(data != NULL);

    printf("[\n");
    for (int i = 0; i < data->lines; i++) {
        printf(" %ls\n", data->text[i].string_ptr);
    }
    printf("]\n");
}

//! Function load pointers of beginnings of strings to an array
//! \param dest_array pointer to array of String structures, where string will be written
//! \param data       analyzed data
//! \param data_size  data size
//! \return           1
int load_string_pointers(struct Text* text) {
    assert(text->text != NULL);
    assert(text->data != NULL);

    wchar_t* start_ptr = (wchar_t*)text->data;

    for (int i = 0, str_index = 0; i < text->data_size && str_index < text->lines; i++) {
        if (text->data[i] == L'\0') {
            wchar_t* end_ptr = NULL;
            end_ptr = (wchar_t*)&(text->data[i]);

            struct String string = {
                    start_ptr,
                    (int)(end_ptr - start_ptr)
            };
            text->text[str_index++] = string;

            start_ptr = (wchar_t*)&(text->data[i + 1]);
        }
    }

    return 1;
}

//! Function opens file
//! \param filename path to file to open (absolute or relative)
//! \param mode     mode with which open file
//! \return         pointer to opened file (FILE*)
//! \note call assert if function cannot open file on the path filename
FILE* open_file(const char* filename, const char mode[]) {
    assert(filename != NULL);

    FILE* file = fopen(filename, mode);

    assert(file != NULL);

    return file;
}

//! Function defines size of file
//! \param filename path to file (absolute or relative)
//! \return         size of file (in bytes)
int file_size(const char* filename) {
    assert(filename != NULL);

    struct stat buff = {};
    stat(filename, &buff);

    return (int)buff.st_size;
}

//! Function reads strings from file
//! \param filename pointer to string of path to file
//! \return         object of Text structure
struct Text get_text_from_file(const char* filename) {
    assert(filename != NULL);

    FILE* file = open_file(filename, "r");

    int f_size = file_size(filename);

    char* data = (char*)calloc(f_size + 1, sizeof(char));
    int bytes = (int)fread(data, sizeof(char), f_size, file);
    f_size = f_size > bytes ? bytes : f_size;

    if (data[f_size - 1] != '\n') {
        data[f_size] = '\n';
        f_size++;
    } else {
        data[f_size] = '\1';
        f_size++;
    }

    wchar_t* wdata = (wchar_t*)calloc(f_size + 1, sizeof(wchar_t));
    int fw_size = (int)mbstowcs(wdata, data, f_size) + 1;
    free(data);

    struct Text text = {};
    text.data = wdata;
    text.data_size = fw_size;
    text.lines = replace(wdata, f_size, L'\n', L'\0', -1);

    text.text = calloc(text.lines, sizeof(struct String));
    load_string_pointers(&text);

    fclose(file);
    return text;
}

//! Function writes strings to file (from Text->text)
//! \param filename pointer to string of path to file (absolute or relative)
//! \param mode     mode with which open file
//! \param data     pointer to object of Text structure, where will strings come from
//! \return         number of written strings
int write_text_to_file(const char* filename, const char mode[], const struct Text* data) {
    assert(filename != NULL);
    assert(mode != NULL);
    assert(data != NULL);

    FILE* file = open_file(filename, mode);

    if (data->lines == 0) {
        fputs("", file);
        return 0;
    }

    int n_wr_strings = 0;
    for (n_wr_strings = 0; n_wr_strings < data->lines; n_wr_strings++) {
        fputws(data->text[n_wr_strings].string_ptr, file);
        fputws(L"\n", file);
    }

    fclose(file);
    return n_wr_strings;
}

//! Function writes strings to file (from Text->buffer)
//! \param filename pointer to string of path to file (absolute or relative)
//! \param mode     mode with which open file
//! \param data     pointer to object of Text structure, where will strings come from
//! \return         number of written strings
//! \note '\0' indicates line ending in buffer, so all lines in buffer must end in '\0'
int write_buffer_to_file(const char* filename, const char mode[], const struct Text* data) {
    assert(filename != NULL);
    assert(mode != NULL);
    assert(data != NULL);

    FILE* file = open_file(filename, mode);

    if (data->data_size == 0) {
        fputs("", file);
        return 0;
    }

    int n_wr_strings = 0;
    wchar_t* start_ptr = data->data;
    for (n_wr_strings = 0; n_wr_strings < data->lines; n_wr_strings++) {
        fputws(start_ptr, file);
        fputws(L"\n", file);

        wchar_t* end_ptr = wcschr(start_ptr, '\0');
        start_ptr = end_ptr + 1;
    }

    fclose(file);
    return n_wr_strings;
}

//! Function writes strings to file (from array of char*)
//! \param filename  pointer to string of path to file (absolute or relative)
//! \param mode      mode with which open file
//! \param data      pointer to array of char*
//! \param n_strings number of elements in data
//! \return          number of written strings
int write_strings_to_file(const char* filename, const char mode[], const char** data, int n_strings) {
    assert(filename != NULL);
    assert(mode != NULL);
    assert(data != NULL);

    FILE* file = open_file(filename, mode);

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
