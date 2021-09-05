//
// Created by ivanbrekman on 26.08.2021.
//

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/string_funcs.h"

/*
 * \brief Функция сравнивает 2 массива строк на равенство элементов.
 * \param [in] array1 - указатель на первый массив строк.
 * \param [in] size1  - int количество элементов в первом массиве.
 * \param [in] array2 - указатель на второй массив строк.
 * \param [in] size2  - int количество элементов во втором массиве.
 * \return            - 1, если массивы равны, иначе 0.
 */
int equal_arrays(c_string* array1, int size1, c_string* array2, int size2) {
    if (size1 != size2) return 0;
    for (int i = 0; i < size1; i++) {
        if (cmp_string(array1[i], array2[i]) != 0) return 0;
    }
    return 1;
}

/*
 * \brief Функция поэлементно копирует массив строк
 * \param [in] source_array - указатель на массив-источник строк
 * \param [in] source_size  - int размер массива-источника
 * \param [in] dest_array   - указатель на массив-адресат строк
 * \return                  - указатель на новый скопированный массив (не совпадает с указателем dest_array)
 * \note Функция изменяет dest_array
 */
c_string* copy_str_array(c_string* source_array, int source_size, c_string* dest_array) {
    c_string* cpy_array = calloc(source_size, sizeof(c_string));
    for (int i = 0; i < source_size; i++) {
        dest_array[i] = source_array[i];
        cpy_array[i] = source_array[i];
    }

    return cpy_array;
}

/*
 * \brief Функция печатает массив строк
 * \param [in] array - массив строк, которые необходимо распечатать
 * \param [in] size  - размер печатаемого массива
 * \note Ничего не возвращает
 */
void print_array(c_string* array, int size) {
    printf("[ ");
    for (int i = 0; i < size; i++) {
        printf("%s ", array[i]);
    }
    printf("]");
}

/*
 * \brief Функция сравнивает строки
 * \param [in] string1 - первая сравниваемая строка
 * \param [in] string2 - вторая сравниваемая строка
 * \return             - возвращает 1, если string1 > string2,
 *                                 -1, если string1 < string2,
 *                                  0, если string1 == string2
 */
int cmp_string(c_string string1, c_string string2) {

    assert(string1 != NULL && string2 != NULL);

    c_string small_string = strlen(string1) < strlen(string2) ? string1 : string2;

    for (int i = 0; i < strlen(small_string); i++) {
        if (string1[i] > string2[i]){
            return 1;
        }
        if (string1[i] < string2[i]) return -1;
    }

    if (strlen(string1) == strlen(string2)) return 0;

    return (small_string == string1 ? -1 : 1);
}

/*
 * \brief Функция выполняет быструю сортировку массива строк array (меняет сам массив)
 * \param [in] array - указатель на массив строк
 * \param [in] size  - int размер массива
 * \param [in] first - индекс начала (должен быть -1 по умолчанию)
 * \param [in] last  - индекс конца  (должен быть  0 по умолчанию)
 * \note Изменяет сам массив array
 */
void quick_sort(c_string* array, int size, int first, int last) {
    if (first >= last) return;

    first = first < 0 ? 0 : first;
    last = last == 0 ? size - 1: last;

    int index = first + rand() % (last - first);
    c_string barrier = array[index];

    int i = first;
    int j = last;

    while (i < j) {
        while (cmp_string(array[i], barrier) == -1) i++;
        while (cmp_string(array[j], barrier) ==  1) j--;

        if (i <= j) {
            c_string tmp = array[i];
            array[i] = array[j];
            array[j] = tmp;

            i++;
            j--;
        }
    }

    quick_sort(array, size, first, j);
    quick_sort(array, size, i, last);
}
