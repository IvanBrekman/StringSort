#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>

#include "headers/test.h"
#include "headers/string_funcs.h"
#include "headers/file_funcs.h"
#include "headers/clear_file.h"

#define FREE(ptr) do { free(ptr); (ptr) = NULL; } while(0)

const char* BLOCK_DELIMITERS[] = {
    "**************************************************************************************************************************************************",
    "==================================================================================================================================================",
    "**************************************************************************************************************************************************"
};

int main(int argc, char** argv) {
    setlocale(LC_ALL, "en_US.utf8");

#if 0
    char arr1[] = {'a', 'h', 'b', 'g', 'c', 'f', 'd', 'k', 'e'};
    int arr[] = {12 ,-12, 2, 5, 9123, -34, 12, 9, 0, -12, 12, 3, 2, 3, 5};

    quick_sort(arr, sizeof(arr)/sizeof(arr[0]), sizeof(int), int_cmp);

    for(int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
#endif
#if 0
//    struct String str1 = {"И все равно: надежда им", 23};
//    struct String str2 = {"Да, видно, почта задержала. -", 29};
//    wchar_t sym =  L'А';
//
//    printf("%d\n", rev_cmp_string(&str1, &str2));
    printf("%d", (char)L'-');
    return 1;
#endif
#if 0
    FILE * pFile;
    wchar_t sentence [256] = L"sdfghjkl";

    pFile = fopen ("mylog.txt","a");
    fputws (sentence,pFile);
    fclose (pFile);
    wprintf(L"asdf");
#endif
    //clear_text_file("/home/ivanbrekman/CLionProjects/StringSort/text_files/origin.txt", "/home/ivanbrekman/CLionProjects/StringSort/text_files/data.txt", letters_in_string);
    //test_string_sort();

    char* in_filename_input  = calloc(80, sizeof(char));
    char* out_filename_input = calloc(80, sizeof(char));

    char* in_filename  = NULL;
    char* out_filename = NULL;

    if (argc > 1) {
        in_filename  = argv[1];
        out_filename = argv[2];
    } else {
        printf("Введите имя входного файла\n");
        scanf("%s", in_filename_input);

        printf("Введите имя выходного файла\n");
        scanf("%s", out_filename_input);

        in_filename  = in_filename_input;
        out_filename = out_filename_input;
    }

    struct Text data = get_text_from_file(in_filename);

    qsort(data.text, data.lines, sizeof(data.text[0]), cmp_string);
    print_text(&data);

    write_text_to_file(out_filename, "w", &data);
    write_strings_to_file(out_filename, "a", BLOCK_DELIMITERS, 3);

    quick_sort(data.text, data.lines, sizeof(data.text[0]), rev_cmp_string);
    write_text_to_file(out_filename, "a", &data);
    write_strings_to_file(out_filename, "a", BLOCK_DELIMITERS, 3);

    write_buffer_to_file(out_filename, "a", &data);

    printf("Текст отсортирован и записан в файл: %s\n", out_filename);

    in_filename  = NULL;
    out_filename = NULL;
    FREE(in_filename_input);
    FREE(out_filename_input);
    free_text(&data);

    return 0;
}

int int_cmp(const void* a, const void* b) {
    return *((const int*)a) - *((const int*)b);
}
/*

/home/ivanbrekman/CLionProjects/StringSort/text_files/test.txt
/home/ivanbrekman/CLionProjects/StringSort/text_files/out.txt

/home/ivanbrekman/CLionProjects/StringSort/text_files/origin.txt
/home/ivanbrekman/CLionProjects/StringSort/text_files/out.txt

/home/ivanbrekman/CLionProjects/StringSort/text_files/data.txt
/home/ivanbrekman/CLionProjects/StringSort/text_files/out.txt

*/
