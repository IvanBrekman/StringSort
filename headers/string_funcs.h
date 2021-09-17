//
// Created by ivanbrekman on 26.08.2021.
//

int letters_in_string(char* string);
int replace(char* string, size_t size, char old_symbol, char new_symbol, int n_replace);

int equal_strings_array(const char** array1, size_t size1, const char** array2, size_t size2);
void print_strings(const char** array, size_t size);

int cmp_string(const void* string1, const void* string2);
int cmp_string_raw(const void* str1, const void* str2);
int rev_cmp_string(const void* str1, const void* str2);

void swap(void* f_el, void* s_el, size_t el_size);
int max_num_length(const int* data, size_t size);

void quick_sort(void* array, size_t number, size_t el_size, int comparator(const void*, const void*));
void qsort_debug_int(const void* array, size_t el_num, int left, int right, int barrier, const char reason[]);
void qsort_debug_str(const void* array, size_t el_num, int left, int right, int barrier, const char reason[]);

