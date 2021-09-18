//
// Created by ivanbrekman on 17.09.2021.
//

#include <bits/types/FILE.h>
#include <stdio.h>
#include "../headers/file_funcs.h"
#include "../headers/string_funcs.h"

int clear_text_file(const char* input_filename, const char* output_filename, int filter(const char*, int)) {
    struct Text text = get_text_from_file(input_filename);
    int clear_lines = 0;

    FILE* ofile = open_file(output_filename, "w");
    for (int i = 0; i < text.lines; i++) {
        if (filter(text.text[i].string_ptr, text.text[i].len)) {
            fputs(text.text[i].string_ptr, ofile);
            fputs("\n", ofile);
            clear_lines++;
        }
    }

    fclose(ofile);
    return clear_lines;
}

int text_file(const char* input_filename, const char* output_filename) {
    struct Text text = get_text_from_file(input_filename);
    int clear_lines = 0;

    FILE* ofile = open_file(output_filename, "w");
    for (int i = 0; i < text.lines; i++) {
        fputs(text.text[i].string_ptr, ofile);
        fputs("\n", ofile);
        clear_lines++;
    }

    fclose(ofile);
    return clear_lines;
}

int a(const char* input_filename) {
    int f_size = file_size(input_filename);
}
