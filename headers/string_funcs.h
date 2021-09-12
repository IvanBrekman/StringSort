//
// Created by ivanbrekman on 26.08.2021.
//

#define MAX_STRING_LENGTH 80
typedef char* c_string;

int punctuation_symbol(char symbol);
c_string clear_string(c_string string);
int letters_in_string(c_string string);
c_string reverse(c_string string);
int equal_arrays(c_string* array1, int size1, c_string* array2, size_t size2);
c_string* copy_str_array(c_string* source_array, size_t source_size, c_string* dest_array);
void print_array(c_string* array, size_t size);

int cmp_string(const void* string1, const void* string2);
int rev_cmp_string(const void* str1, const void* str2);
void quick_sort(c_string* array, size_t size, int comparator(const void*, const void*));
