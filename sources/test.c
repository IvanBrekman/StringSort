//
// Created by ivanbrekman on 26.08.2021.
//

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/test.h"
#include "../headers/file_funcs.h"
#include "../headers/string_funcs.h"
#include "../headers/standard_str_func.h"

struct compare_data {
    char* string1;
    char* string2;

    int result;
};

struct sort_data {
    char* init_array[10];
    int array_size;

    char* sorted_array[10];
};

int test_string_sort() {
    test_cmp_func();
    test_sort_func();

    printf("End of testing\n---------------------------------------------\n\n");
    return 1;
}

int test_cmp_func() {
    printf("Testing compare function\n");
    struct compare_data data[] = {
            {            "1",         "9", -1 },
            {           "aa",        "ab", -1 },
            {            "a",         "a",  0 },
            { "ghsiduhdfndj", "ghsiduhdf",  3 },
            {     "aaaaaaaa",    "aaaaaa",  2 },
            {         "Test",      "test", -1 },
            {         "TEST",      "TESt", -1 },
            {    "123abc123", "123abc321", -1 },
            {             "",          "",  0 },
            {            "a",          "",  1 }
    };

    size_t n = sizeof(data) / sizeof(data[0]);
    int error_status = 0;

    for (int i = 0; i < n; i++) {
        int return_code = cmp_string_raw(data[i].string1, data[i].string2);

        printf("Test №%d: ", i + 1);
        if (return_code == data[i].result) {
            printf("OK\n");
        } else {
            error_status = 1;
            printf("Failed - expected: %2d,\n"
                   "                       got: %2d.\n"
                   "                Input data: \"%s\", \"%s\"\n",
                   data[i].result, return_code, data[i].string1, data[i].string2);
        }
    }
    printf("\n\n");

    return !error_status;
}

int test_sort_func() {
    printf("Testing sort function\n");
    struct sort_data s_data[] = {
            {
                {"1", "9", "8", "7", "6", "5", "4", "2", "0", "3"},
                10,
                {"b", "a", "c", "d", "e", "r", "w", "x", "y", "z"}
            },
                //{
                //{"KaIPLbxADslJGghf","PyOgCYDeVXSGneOY","KElNEPxvzKTDDrHY","ZGyyIlfqoCadPaxy","YoVZoYBdFVrSMEjT","OBqcrmTDWHUiTwNC","OcoavApvhbsOubrB","ldvxeXTdqwDTleOo","ETVLUOpVsboHYVHm","sBvyNqDMOFcgTJQk"},
                //10,
                //{"ETVLUOpVsboHYVHm","KElNEPxvzKTDDrHY","KaIPLbxADslJGghf","OBqcrmTDWHUiTwNC","OcoavApvhbsOubrB","PyOgCYDeVXSGneOY","YoVZoYBdFVrSMEjT","ZGyyIlfqoCadPaxy","ldvxeXTdqwDTleOo","sBvyNqDMOFcgTJQk"}
                //}
    };
    int n = sizeof(s_data) / sizeof(s_data[0]);
    int error_status = 0;

    for (int i = 0; i < n; i++) {

        int size = s_data[i].array_size;

        char** array = calloc(size, sizeof(char*));
        memcpy(array, s_data[i].init_array, sizeof(s_data[i].init_array));
        print_strings((const char**)array, size);

        qsort(array, size, sizeof(array[0]), cmp_string_raw);

        printf("Test №%d: ", i + 1);
        if (equal_strings_array((const char**)array, size, (const char**)s_data[i].sorted_array, size)) {
            printf("OK\n");
        } else {
            error_status = 1;
            printf("Failed - expected: ");
            print_strings((const char**)s_data[i].sorted_array, size);
            printf(",\n                       got: ");
            print_strings((const char**)array, size);
            printf(".\n                Input data: ");
            print_strings((const char**)s_data[i].init_array, size);
            printf("\n");
        }
    }
    printf("\n\n");

    return !error_status;
}

int test_std_string_func() {
    // test_functinos
    my_puts("hahaha!");
    printf("%d\n", my_strlen("абсдек"));
    printf("%d\n", *my_strchr("abcdefgh", '\0'));

    char* string = calloc(20, sizeof(char));
    my_puts(my_strncpy(string, "I love you!", 5));

    my_puts(my_strcpy(string, "bbbaaaccceee"));
    my_puts(string);
    my_strdup(string);

    my_puts(my_strcat("abcd", "efghi"));
    my_puts(my_strncat("abcd", "efghi", 10));

    FILE * fp = open_file(my_strcat("/home/ivanbrekman/CLionProjects/StringSort/text_files/", "test.txt"), "r");
    free(string);
    string = calloc(20, sizeof(char));

    while (my_fgets(string, 5, fp) != NULL) {
        my_puts(string);
    }
    fseek(fp, 0, SEEK_SET);

    printf("test!!\n");
    my_puts(my_fgets(string, 5, fp));

    getchar();
    getchar();

    return 1;
}
