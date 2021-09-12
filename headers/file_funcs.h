//
// Created by ivanbrekman on 26.08.2021.
//

#include "string_funcs.h"

enum f_errors { FILE_NOT_FOUND = -1, NULL_FILE_PTR = -2 };

FILE* open_file(char* filename, char mode[5]);
char** get_strings_from_file(char* filename, int* n_strings);
int write_strings_to_file(char* filename, char**, int n_strings);
