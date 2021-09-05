//
// Created by ivanbrekman on 26.08.2021.
//

#include "string_funcs.h"

enum f_errors { FILE_NOT_FOUND = -1, NULL_FILE_PTR = -2 };

FILE* open_file(c_string filename, char mode[5]);
int count_lines(c_string filename);
c_string* get_strings_from_file(c_string filename, int* n_strings);
int write_strings_to_file(c_string filename, c_string*, int n_strings);
