//
// Created by ivanbrekman on 26.08.2021.
//

#define MAX_STRING_LENGTH 80
typedef char* c_string;

int equal_arrays(c_string* array1, int size1, c_string* array2, int size2);
c_string* copy_str_array(c_string* source_array, int source_size, c_string* dest_array);
void print_array(c_string* array, int size);

int cmp_string(c_string string1, c_string string2);
void quick_sort(c_string* array, int size, int first, int last);
