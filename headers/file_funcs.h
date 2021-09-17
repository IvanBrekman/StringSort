//
// Created by ivanbrekman on 26.08.2021.
//

struct String {
    char* string_ptr;
    int len;
};

struct Text {
    char* data;
    size_t data_size;

    struct String* text;
    size_t lines;
};

void free_text(struct Text* data);
void free_string(struct String* string);

int load_string_pointers(struct String* strings_storage, const char* data, size_t data_size);
void print_text(const struct Text* data);

FILE* open_file(const char* filename, const char mode[]);
int file_size(const char* filename);
struct Text get_text_from_file(const char* filename);

int write_text_to_file(const char* filename, const char mode[], const struct Text* data);
int write_buffer_to_file(const char* filename, const char mode[], const struct Text* data);
int write_strings_to_file(const char* filename, const char mode[], const char** data, int n_strings);
