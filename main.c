#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"

#define MAX_INPUT_STRING_LENGTH 22000 //одно число может быть длины порядка 19 символов + пробелы
#define stderr_printf(...) fprintf(stderr, __VA_ARGS__)

struct interval_t {
    long long from;
    long long to;
};

int parse_argv(int argc, char* argv[], struct interval_t* out_interval) {
    if(argc < 3) {
        stderr_printf("Number of params < 2");
        return -1;
    }
    if(argc > 3) {
        stderr_printf("Number of params > 2");
        return -2;
    }
    if(strcmp(argv[1], argv[2]) == 0) {
        stderr_printf("Repeat of params (you must use --from and --to only one time)");
        return -3;
    }

    int from_flag = 0, to_flag = 0;
    for(int i = 1; i < argc; i++) {
        long long number_in_string;
        if(strncmp(argv[i], "--from=", 7) == 0 && !from_flag) {
            number_in_string = strtoll(argv[i] + 7, NULL, 10);
            out_interval->from = number_in_string;
            from_flag = 1;
        }
        else if(strncmp(argv[i], "--to=", 5) == 0 && !to_flag) {
            number_in_string = strtoll(argv[i] + 5, NULL, 10);
            out_interval->to = number_in_string;
            to_flag = 1;
        }
        else {
            stderr_printf("Not valid params");
            return -4;
        }
    }

    return 0;
}

int parse_input_string(char* input_string, struct interval_t interval, long long out_array[]) {
    int size = 0;
    char* pStart = input_string;
    char* pEnd;

    do {
        long long num = strtoll(pStart, &pEnd, 10);

        if(num < interval.from)
            printf("%lli ", num);
        if(num > interval.to)
            stderr_printf("%lli ", num);
        if(num >= interval.from && num <= interval.to) {
            out_array[size] = num;
            size++;
        }

        pStart = pEnd;
    } while (*pEnd != '\0');

    return size;
}

void copy_array(const long long array_from[], long long array_to[], int size) {
    for(int i = 0; i < size; i++)
        array_to[i] = array_from[i];
}

int compare_arrays(const long long array1[], const long long array2[], int size) {
    int difference_count = 0;
    for(int i = 0; i < size; i++) {
        if(array1[i] != array2[i])
            difference_count++;
    }
    return difference_count;
}

int main(int argc, char* argv[]) {

    struct interval_t interval = {0, 0};

    int parse_return_code = parse_argv(argc, argv, &interval);
    if(parse_return_code != 0)
        return parse_return_code;

    int size;
    long long array[100], array_copy[100];
    char input_string[MAX_INPUT_STRING_LENGTH];
    gets(input_string);
    size = parse_input_string(input_string, interval, array);
    copy_array(array, array_copy, size);

    sort(array_copy, array_copy + size);
    int swapped_count = compare_arrays(array, array_copy, size);

    return swapped_count;
}