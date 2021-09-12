//
// Created by ivanbrekman on 26.08.2021.
//

int punctuation_symbol(char symbol);
char* clear_string(char* string);
int letters_in_string(char* string);
int count(char* string, char symbol);
int replace(char* string, char old_symbol, char new_symbol, int n_replace);
char* reverse(char* string);

int load_string_pointers(char** dest_array, char* string, size_t data_size);
int equal_arrays(char** array1, int size1, char** array2, size_t size2);
char** copy_str_array(char** source_array, size_t source_size, char** dest_array);
void print_array(char** array, size_t size);

int cmp_string(const void* string1, const void* string2);
int rev_cmp_string(const void* str1, const void* str2);
void quick_sort(char** array, size_t size, int comparator(const void*, const void*));
