#include <assert.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include "headers/test.h"
#include "headers/standart_str_func.h"
#include "headers/string_funcs.h"
#include "headers/file_funcs.h"

#define dbg(code) do{ printf("%s:%d\n", __FILE__, __LINE__); code }while(0) // liberror.h (color)

const char HOME_DIR[] = "/home/ivanbrekman/CLionProjects/StringSort/text_files/"; // try to fix

int main() {
    test_string_sort();

    c_string in_filename = calloc(80, sizeof(char));
    c_string out_filename = calloc(80, sizeof(char));

    printf("Введите имя входного файла\n");
    scanf("%s", in_filename);

    printf("Введите имя выходного файла\n");
    scanf("%s", out_filename);

    c_string in_path = calloc(strlen(HOME_DIR) + strlen(in_filename) + 1, sizeof(char));
    in_path = my_strcpy(in_path, HOME_DIR);
    in_path = my_strcat(in_path, in_filename);

    c_string out_path = calloc(strlen(HOME_DIR) + strlen(out_filename) + 1, sizeof(char));
    out_path = my_strcpy(out_path, HOME_DIR);
    out_path = my_strcat(out_path, out_filename);

    int n_strings = -1;
    c_string* data = get_strings_from_file(in_path, &n_strings);

    assert(n_strings > 0 && data != NULL);

    quick_sort(data, n_strings, -1, 0);
    int n_wr_str = write_strings_to_file(out_path, data, n_strings);

    for (int i = 0; i < n_strings; i++) {
        free(data[i]);
    }
    free(data);

    assert(n_strings == n_wr_str);

    printf("Текст отсортирован и записан в файл: %s", out_path);

    return 0;
}
