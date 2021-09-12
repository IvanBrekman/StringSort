#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include "headers/test.h"
#include "headers/standard_str_func.h"
#include "headers/string_funcs.h"
#include "headers/file_funcs.h"

const char HOME_DIR[] = "/home/ivanbrekman/CLionProjects/StringSort/text_files/";
const char* BLOCK_DELIMITERS[] = {
        "**************************************************************************************************************************************************",
        "==================================================================================================================================================",
        "**************************************************************************************************************************************************"
};

int main(int argc, char** argv) {
    test_string_sort();

    char* in_filename = (char*)calloc(80, sizeof(char));
    char* out_filename = (char*)calloc(80, sizeof(char));

    if (argc > 1) {
        in_filename = argv[1];
        out_filename = argv[2];
    } else {
        printf("Введите имя входного файла\n");
        scanf("%s", in_filename);

        printf("Введите имя выходного файла\n");
        scanf("%s", out_filename);
    }

    char* in_path = (char*)calloc(strlen(HOME_DIR) + strlen(in_filename) + 1, sizeof(char));
    in_path = my_strcpy(in_path, HOME_DIR);
    in_path = my_strcat(in_path, in_filename);

    char* out_path = (char*)calloc(strlen(HOME_DIR) + strlen(out_filename) + 1, sizeof(char));
    out_path = my_strcpy(out_path, HOME_DIR);
    out_path = my_strcat(out_path, out_filename);

    free(in_filename);
    free(out_filename);


    int f_size = -1, n_strings = -1;
    char* data = get_data_from_file(in_path, &f_size);
    n_strings = replace(data, f_size, '\n', '\0', -1);

    char** strings = (char**)calloc(n_strings, sizeof(char*));
    load_string_pointers(strings, data, f_size);

    int new_size = -1;
    char** clear_strings = clear_string_data(strings, n_strings, &new_size);
    free(strings);


    quick_sort(clear_strings, new_size, cmp_string);
    write_strings_to_file(out_path, "w", clear_strings, new_size);
    write_strings_to_file(out_path, "a", (char**)BLOCK_DELIMITERS, 3);

    quick_sort(clear_strings, new_size, rev_cmp_string);
    write_strings_to_file(out_path, "a", clear_strings, new_size);
    write_strings_to_file(out_path, "a", (char**)BLOCK_DELIMITERS, 3);

    char** ptr_to_orig = &data;
    replace(data, f_size, '\0', '\n', -1);
    write_strings_to_file(out_path, "a", ptr_to_orig, 1);


    printf("Текст отсортирован и записан в файл: %s\n", out_path);

    free(clear_strings);
    free(data);

    return 0;
}
