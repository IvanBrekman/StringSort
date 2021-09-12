#include <assert.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include "headers/test.h"
#include "headers/standard_str_func.h"
#include "headers/string_funcs.h"
#include "headers/file_funcs.h"
#include "headers/errorlib.h"

const char HOME_DIR[] = "/home/ivanbrekman/CLionProjects/StringSort/text_files/"; // try to fix

int main(int argc, char** argv) {
    //test_string_sort();
    print_array(argv, argc);

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

    int n_strings = -1;
    char** data = get_strings_from_file(in_path, &n_strings);
    print_array(data, n_strings);

    assert(n_strings > 0);
    assert(data != NULL);

    for (int i = 0; i < n_strings; i++) printf("%p ", data[i]); //
    printf("\n"); //

    quick_sort(data, n_strings, rev_cmp_string);
    int n_wr_str = write_strings_to_file(out_path, data, n_strings);

    for (int i = 0; i < n_strings; i++) printf("%p ", data[i]); //
    dbg();

    for (int i = 0; i < n_strings; i++) {
        dbg(printf("%p\n", data[i]););
        dbg();
        free(data[i]);
    }
    free(data);

    assert(n_strings == n_wr_str);

    printf("Текст отсортирован и записан в файл: %s", out_path);

    return 0;
}
