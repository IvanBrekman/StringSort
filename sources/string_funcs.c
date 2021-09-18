//
// Created by ivanbrekman on 26.08.2021.
//

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "../headers/string_funcs.h"
#include "../headers/file_funcs.h"
#include "../headers/errorlib.h"

//! Experimental function to detect russian letters in string
//! \param  string pointer to string
//! \return 1 if russian letters in string else 0
int letters_in_string(const char* string, int len) {
    assert(string != NULL);

    for (int i = 0; i < len; i++) {
        int code = (int)string[i];

        if (code < 0) {
            return 1;
        }
    }

    return 0;
}

int has_alnum(const char* string) {
    int i = 0;
    while (string[i] != '\0') {
        if (isalnum(string[i])) {
            return 1;
        }
        i++;
    }

    return 0;
}

//! Function replaces old_symbol ti new_symbol in string n_replace times
//! \param string     pointer to string
//! \param size       size of string
//! \param old_symbol old symbol
//! \param new_symbol new symbol
//! \param n_replace  number or replacements (-1 if you want to replace all old symbols)
//! \return           number of replacements
//! \note function need string size, because if you want to
//!       replace '\0' symbol strlen function wont work correctly
int replace(char* string, size_t size, char old_symbol, char new_symbol, int n_replace) {
    assert(string != NULL);

    int n_rep = 0;

    for (int i = 0; i < size; i++) {
        if (n_rep >= n_replace && n_replace >= 0) {
            break;
        }
        if (string[i] == old_symbol) {
            string[i] = new_symbol;
            n_rep++;
        }
    }

    return n_rep;
}

//! Function checks 2 arrays of strings for equality
//! \param array1 pointer to first array of strings
//! \param size1  size of first array
//! \param array2 pointer ro second array of strings
//! \param size2  size of second array
//! \return       1 if arrays are equal else 0
int equal_strings_array(const char** array1, size_t size1, const char** array2, size_t size2) {
    assert(array1 != NULL);
    assert(array2 != NULL);
    assert(array1 != array2);
    assert(size1 != 0);
    assert(size2 != 0);

    if (size1 != size2) return 0;
    for (int i = 0; i < size1; i++) {
        if (cmp_string_raw(&array1[i], &array2[i]) != 0) return 0;
    }
    return 1;
}

//! Function prints array of strings
//! \param array pointer to array of strings
//! \param size  size of array
void print_strings(const char** array, size_t size) {
    assert(array != 0);

    printf("[ ");
    for (int i = 0; i < size; i++) {
        printf("%s ", array[i]);
    }
    printf("]\n");
}

//! Function compare 2 struct String (element-by-element from the beginning)
//! \param str1 pointer to first string
//! \param str2 pointer to second string
//! \return     1 if string1 should stay after string2
//!            -1 if string1 should stay before string2
//!             0 if string1 equivalent with string2
int cmp_string(const void* str1, const void* str2) {
    assert(str1 != NULL);
    assert(str2 != NULL);

    struct String struct1 = *(struct String*)str1;
    char* string1 = struct1.string_ptr;
    int len1 = struct1.len;

    struct String struct2 = *(struct String*)str2;
    char* string2 = struct2.string_ptr;
    int len2 = struct2.len;

    int index1 = 0, index2 = 0;
    int n_let1 = 0, n_let2 = 0;
    while (index1 < len1 && index2 < len2) {
        if (ispunct(string1[index1])) {
            index1++;
            continue;
        }
        if (ispunct(string2[index2])) {
            index2++;
            continue;
        }

        if (string1[index1] > string2[index2]) {
            return 1;
        }
        if (string1[index1] < string2[index2]) {
            return -1;
        }
        index1++;
        index2++;

        n_let1++;
        n_let2++;
    }

    return n_let1 - n_let2;
}

int cmp_string_raw(const void* str1, const void* str2) {
    assert(str1 != NULL);
    assert(str2 != NULL);

    char* string1 = *((char**)str1);
    char* string2 = *((char**)str2);

    int len1 = (int)strlen(string1), len2 = (int)strlen(string2);
    int index1 = 0, index2 = 0;
    int n_let1 = 0, n_let2 = 0;
    while (index1 < len1 && index2 < len2) {
        if (ispunct(string1[index1])) {
            index1++;
            continue;
        }
        if (ispunct(string2[index2])) {
            index2++;
            continue;
        }

        if (string1[index1] > string2[index2]) {
            return 1;
        }
        if (string1[index1] < string2[index2]) {
            return -1;
        }
        index1++;
        index2++;

        n_let1++;
        n_let2++;
    }

    if      (index1 < len1 && has_alnum(string1)) return 1;
    else if (index2 < len2 && has_alnum(string2)) return -1;
    else                                          return 0;
}

//! Function compare 2 strings (element-by-element from the END)
//! \param str1 pointer to first string
//! \param str2 pointer to second string
//! \return 1 if string1 should stay after string2
//!        -1 if string1 should stay before string2
//!         0 if string1 equivalent with string2
int rev_cmp_string(const void* str1, const void* str2) {
    assert(str1 != NULL);
    assert(str2 != NULL);

    const struct String struct1 = *(const struct String*)str1;
    char* string1 = struct1.string_ptr;

    struct String struct2 = *(struct String*)str2;
    char* string2 = struct2.string_ptr;

    int index1 = (int)(struct1.len) - 1, index2 = (int)(struct2.len) - 1;
    int n_let1 = 0, n_let2 = 0;
    while (index1 >= 0 && index2 >= 0) {
        if (ispunct(string1[index1])) {
            index1--;
            continue;
        }
        if (ispunct(string2[index2])) {
            index2--;
            continue;
        }

        if (string1[index1] > string2[index2]){
            return 1;
        }
        if (string1[index1] < string2[index2]) {
            return -1;
        }
        index1--;
        index2--;

        n_let1++;
        n_let2++;
    }

    return n_let1 - n_let2;
}

void swap(void* f_el, void* s_el, size_t el_size) {
    for (int i = 0; i < el_size; i++) {
        char tmp = *((char*)(f_el + i));
        *((char*)(f_el + i)) = *((char*)(s_el + i));
        *((char*)(s_el + i)) = tmp;
    }
}
int max_num_length(const int* data, size_t size) {
    int max_el = data[0];

    for (int i = 1; i < size; i++) {
        int number = data[i];

        if (number < 0) {
            number = -(number * 10);
        }

        if (number > max_el) max_el = number;
    }

    int length = 0;
    while (max_el > 0) {
        max_el /= 10;
        length++;
    }

    return length;
}

//! Function sorts array of strings in place
//! \param array pointer to array of strings
//! \param el_size el_size of array
//! \param first start index of sorted sequence (call function with first < 0)
//! \param last end index of sorted sequence (call function with
//! \note Function sorts elements in place
void quick_sort(void* array, size_t el_number, size_t el_size, int comparator(const void*, const void*)) {
    assert(array != NULL);

    if (el_number < 2) return;

    int left = 0;
    int right = (int)el_number - 1;

    int bar_index = (int)el_number / 2;

    qsort_debug_tex(array, el_number, left, right, bar_index, "Старт быстрой сортировки\n");
    do {
        while(comparator(array + left * el_size, array + bar_index * el_size) < 0) {
            assert(left < el_number);
            left++;
            //printf("Результат сравнения: %d (строк \"%s\" \"%s\")\n", comparator(array + left * el_size, array + bar_index * el_size), *(char**)(array + left * el_size), *(char**)(array + bar_index * el_size));
            //qsort_debug_str(array, el_number, left, right, bar_index, "Сравниваю левую границу с барьером\n");
        }
        qsort_debug_tex(array, el_number, left, right, bar_index, "Сдвинули левую границу\n");
        while(comparator(array + right * el_size, array + bar_index * el_size) > 0) {
            assert(right >= 0);
            right--;
        }
        qsort_debug_tex(array, el_number, left, right, bar_index, "Сдвинули правую границу\n");

        if (left <= right) {
            if      (bar_index == left)  bar_index = right;
            else if (bar_index == right) bar_index = left;

            swap(array + left * el_size, array + right * el_size, el_size);
            qsort_debug_tex(array, el_number, left, right, bar_index, "Меняем местами элементы\n");

            left++;
            right--;
            qsort_debug_tex(array, el_number, left, right, bar_index, "Меняем границы\n");
        }
    } while (left <= right);

    if (right > 0) {
        quick_sort(array, right + 1, el_size, comparator);
    }
    if (left < el_number) {
        quick_sort(array + left * el_size, el_number - left, el_size, comparator);
    }
}

void qsort_debug_int(const void* array, size_t el_num, int left, int right, int barrier, const char reason[]) {
    const int* int_array = (const int*)array;
    int max_len = max_num_length(int_array, el_num);

    printf("%s", reason);
    for (int i = 0; i < el_num; i++) {
        printf("%*d ", max_len, i);
    }
    printf("\n");
    for (int i = 0; i < el_num; i++) {
        int color = 37;
        if (i == left)         color = 32; // green
        else if (i == right)   color = 34; // blue
        else if (i == barrier) color = 35; // magenta

        printf("\033[1;%dm%*d\033[0m ", color, max_len, int_array[i]);
    }
    printf("\n");
    printf("left_el: %d, right_el: %d, barrier_el: %d\n", int_array[left], int_array[right], int_array[barrier]);
    printf("el_num: %zd, left: %d, right: %d, barrier: %d\n\n", el_num, left, right, barrier);
}
void qsort_debug_str(const void* array, size_t el_num, int left, int right, int barrier, const char reason[]) {
    const char** chr_array = (const char**)array;
    int max_len = 1;

    printf("%s", reason);
    for (int i = 0; i < el_num; i++) {
        printf("%*d ", max_len, i);
    }
    printf("\n");
    for (int i = 0; i < el_num; i++) {
        int color = 37;
        if (i == left)         color = 32; // green
        else if (i == right)   color = 34; // blue
        else if (i == barrier) color = 35; // magenta

        printf("\033[1;%dm%*s\033[0m ", color, max_len, chr_array[i]);
    }
    printf("\n");
    printf("left_el: %s, right_el: %s, barrier_el: %s\n", chr_array[left], chr_array[right], chr_array[barrier]);
    printf("el_num: %zd, left: %d, right: %d, barrier: %d\n\n", el_num, left, right, barrier);
}
void qsort_debug_tex(const void* array, size_t el_num, int left, int right, int barrier, const char reason[]) {
    const struct String* chr_array = (const struct String*)array;
    int max_len = 10;

    printf("%s", reason);
    for (int i = 0; i < el_num; i++) {
        printf("%*d ", max_len, i);
    }
    printf("\n");
    for (int i = 0; i < el_num; i++) {
        int color = 37;
        if (i == left)         color = 32; // green
        else if (i == right)   color = 34; // blue
        else if (i == barrier) color = 35; // magenta

        printf("\033[1;%dm%*s\033[0m ", color, max_len, chr_array[i].string_ptr);
    }
    printf("\n");
    printf("left_el: %s, right_el: %s, barrier_el: %s\n", chr_array[left].string_ptr, chr_array[right].string_ptr, chr_array[barrier].string_ptr);
    printf("el_num: %zd, left: %d, right: %d, barrier: %d\n\n", el_num, left, right, barrier);
}
