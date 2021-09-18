//
// Created by ivanbrekman on 17.09.2021.
//

#ifndef STRINGSORT_CLEAR_FILE_H
#define STRINGSORT_CLEAR_FILE_H

int clear_text_file(const char* input_filename, const char* output_filename, int filter(const char*, int));
int text_file(const char* input_filename, const char* output_filename);

#endif //STRINGSORT_CLEAR_FILE_H
