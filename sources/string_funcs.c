//
// Created by ivanbrekman on 26.08.2021.
//

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/string_funcs.h"
#include "../headers/standard_str_func.h"

char PUNCTUATION_SYMBOLS[] = ",. -!@*()<>:;'\"\n";

//! Function checks if symbol is punctuation symbol
//! \param symbol tested symbol
//! \return 1 if symbol is punctuation symbol else 0
int punctuation_symbol(char symbol) {
    for (int i = 0; i < sizeof(PUNCTUATION_SYMBOLS) - 1; i++) {
        if (symbol == PUNCTUATION_SYMBOLS[i]) {
            return 1;
        }
    }
    return 0;
}

//! Function copies string to new string without punctuation symbols
//! \param string pointer to source string
//! \return pointer to new string without punctuation symbols
//! \note function allocate memory for new string itself (sizeof(new string) == (sizeof(string))
c_string clear_string(c_string string) {
    int size = my_strlen(string);
    c_string clear_string = (c_string) calloc(size, sizeof(char));

    int j = 0;
    for (int i = 0; i < size; i++) {
        if (!punctuation_symbol(string[i])) {
            clear_string[j] = string[i];
            j++;
        }
    }
    clear_string[j] = '\0';

    return clear_string;
}

//! Experimental function to detect russian letters in string
//! \param string pointer to string
//! \return 1 if russian letters in string else 0
int letters_in_string(c_string string) {
    int n = my_strlen(string);
    for (int i = 0; i < n; i++) {
        int code = (int)string[i];

        if (code < 0) {
            return 1;
        }
    }

    return 0;
}

//! Function checks 2 arrays of strings for equality
//! \param array1 pointer to first array of strings
//! \param size1 size of first array
//! \param array2 pointer ro second array of strings
//! \param size2 size of second array
//! \return 1 if arrays are equal else 0
int equal_arrays(c_string* array1, int size1, c_string* array2, size_t size2) {
    assert(array1 != NULL);
    assert(array2 != NULL);
    assert(array1 != array2);
    assert(size2 != 0);

    if (size1 != size2) return 0;
    for (int i = 0; i < size1; i++) {
        if (cmp_string(array1[i], array2[i]) != 0) return 0;
    }
    return 1;
}

//! Function copies strings from source_array to dest_array (element-by-element)
//! \param source_array pointer to source_array of strings
//! \param source_size size of source_array
//! \param dest_array pointer to dest_array.
//!                   You should allocate memory for dest array before using this function
//! \return pointer to dest_array with strings
c_string* copy_str_array(c_string* source_array, size_t source_size, c_string* dest_array) {
    assert(source_array != NULL);
    assert(dest_array != NULL);
    assert(source_array != dest_array);
    assert(source_size != 0);

    for (int i = 0; i < source_size; i++) {
        dest_array[i] = source_array[i];
    }

    return dest_array;
}

//! Function prints array of strings
//! \param array pointer to array of strings
//! \param size size of array
void print_array(c_string* array, size_t size) {
    assert(array != 0);
    assert(size != 0);

    printf("[ ");
    for (int i = 0; i < size; i++) {
        printf("%s ", array[i]);
    }
    printf("]");
}

//! Function compare 2 strings (element-by-element from the beginning)
//! \param str1 pointer to first string
//! \param str2 pointer to second string
//! \return 1 if string1 should stay after string2
//!        -1 if string1 should stay before string2
//!         0 if string1 equivalent with string2
int cmp_string(const void* str1, const void* str2) {
    assert(str1 != NULL);
    assert(str2 != NULL);

    c_string string1 = (c_string) str1;
    c_string string2 = (c_string) str2;

    c_string small_string = strlen(string1) < strlen(string2) ? string1 : string2;

    for (int i = 0; i < strlen(small_string); i++) {
        if (string1[i] > string2[i]){
            return 1;
        }
        if (string1[i] < string2[i]) {
            return -1;
        }
    }

    if (strlen(string1) == strlen(string2)) {
        return 0;
    }

    return (small_string == string1 ? -1 : 1);
}


//! Function compare 2 strings (element-by-element from the END)
//! \param str1 pointer to first string
//! \param str2 pointer to second string
//! \return 1 if string1 should stay after string2
//!        -1 if string1 should stay before string2
//!         0 if string1 equivalent with string2
int rev_cmp_string(const void* str1, const void* str2) {
    return cmp_string(reverse((c_string)str1), reverse((c_string)str2));
}

//! Function reverses string
//! \param string pointer to string
//! \return pointer to new reversed string
c_string reverse(c_string string) {
    int n = my_strlen(string);
    c_string new_string = calloc(n, sizeof(char));

    for (int i = n - 1, j = 0; i >= 0; i--, j++) {
        new_string[j] = string[i];
    }

    return new_string;
}

//! Function sorts array of strings in place
//! \param array pointer to array of strings
//! \param size size of array
//! \param first start index of sorted sequence (call function with first < 0)
//! \param last end index of sorted sequence (call function with
//! \note Function sorts elements in place
void quick_sort(c_string* array, size_t size, int comparator(const void*, const void*)) {
    assert(array != NULL);
    assert(size != 0);

    int i = 0;
    int j = (int)size - 1;

    int index = 0;
    if (i != j) {
        index = i + (rand() % (j - i));
    }
    c_string barrier = clear_string(array[index]);

    do {
        while (comparator(clear_string(array[i]), barrier) == -1) i++;
        while (comparator(clear_string(array[j]), barrier) ==  1) j--;

        if (i <= j) {
            c_string tmp = array[i];
            array[i] = array[j];
            array[j] = tmp;

            i++;
            j--;
        }
    } while (i <= j);

    if (j > 0)    quick_sort(array, j + 1, comparator);
    if (i < size) quick_sort(&array[i], size - i, comparator);
}
