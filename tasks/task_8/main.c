#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "../../include/utils.h"
#include "bases.h"

#define MAX_PROGRAM_ITERATION 128

static inline int iteration_error_processing(u_status_t status, char **string) {
    u_status_print(stderr, status, u_status_to_string);
    free(*string);
    *string = NULL;
    return 0;
}

int main() {
    u_status_t status;
    char *string = NULL;
    short base;

    status = read_string(stdin, &string);
    if (status != U_OK) {
        u_status_print(stderr, status, u_status_to_string);
        free(string);
        return status;
    }

    status = parse_unsigned_short(string, &base, 2, 36);
    if (status != U_OK) {
        fprintf(stderr, "At base parse: ");
        u_status_print(stderr, status, u_status_to_string);
        free(string);
        return status;
    }
    free(string);
    string = NULL;

    long long temp_value;
    long long max_abs_value = -1;
    unsigned long long i = 0;

    while (i < MAX_PROGRAM_ITERATION) {
        status = read_string(stdin, &string);

        if (status != U_OK) {
            fprintf(stderr, "At read_string: ");
            iteration_error_processing(status, &string);
            continue;
        }

        if (strcmp(string, "Stop") == 0) break;

        status = parse_n_base_to_ll(string, &temp_value, base);
        free(string);
        string = NULL;
        if (status != U_OK) {
            fprintf(stderr, "At parse_n_base_to_ll: ");
            iteration_error_processing(status, &string);
            continue;
        }

        if (abs(temp_value) > max_abs_value) max_abs_value = temp_value;

        ++i;
        if (i == MAX_PROGRAM_ITERATION) fprintf(stderr, "Main cycle finished at %lld iteration", i);
    }

    if(max_abs_value == -1) {
        fprintf(stderr, "Empty input error");
        return 1;
    }

    char *result_string = NULL;
    status = convert_ll_to_n_base(max_abs_value, &result_string, base);
    if (status != U_OK) {
        fprintf(stderr, "At convert_ll_to_n_base: ");
        u_status_print(stderr, status, u_status_to_string);
    }

    fprintf(stdout, "%s in %d base <=> %lld in 10 base\n", result_string, base, max_abs_value);

    free(result_string);
    result_string = NULL;
    
    for (unsigned int i = 1; i < 5; ++i) {
        status = convert_ll_to_n_base(max_abs_value, &result_string, i * 9);
        if (status != U_OK) {
            fprintf(stderr, "At convert_ll_to_%d_base: ", i * 9);
            u_status_print(stderr, status, u_status_to_string);
        }
        
        fprintf(stdout, "%lld converted to %d base: %s\n", max_abs_value, i * 9, result_string);

        free(result_string);
        result_string = NULL;
        
    }

    free(result_string);
    free(string);
    return 0;
}
