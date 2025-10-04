#include "file_process.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

static inline short is_ts_digit(char c) {
    // 48 - '0' // 57 - '9' // 65 - 'A' // 90 - 'Z' // 97 - 'a' // 122 -'z'
    return (c >= '0' && c <= '9' || c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z');
}

static inline int ts_digit_to_int(char c) {
    if (c >= 'A' && c <= 'Z') return c - 55;
    if (c >= 'a' && c <= 'z') return c - 87;
    if (c >= '0' && c <= '9') return c - 48;
    return 0;
}

static inline short ts_cmp(char l, char r) {
    if (l >= 'A' && l <= 'Z') l += 32;
    if (r >= 'A' && r <= 'Z') r += 32;
    return l > r;
}

static u_status_t convert_to_decimal_number_system(int *n, int len, int base, int *result) {
    int temp = 0;
    for (int i = 0; i < len; ++i) {
        if (INT_MAX / base - n[i] >= temp) {
            temp = temp * base + n[i];
        } else {
            return U_OVERFLOW; 
        }
    }
    *result = temp;
    return U_OK;
}

static u_status_t process_number(FILE *out, int *buf, size_t len, int max_c, int negative) {
    if (len == 0) return U_OK;

    int res;
    int base = ts_digit_to_int(max_c) + 1;

    u_status_t st = convert_to_decimal_number_system(buf, len, base, &res);
    if (st != U_OK) {
        fprintf(stderr,
                "At convert_to_decimal_number_system(%p, %zu, %d, %p);\n",
                (void*)buf, len, base, (void*)&res);
        return st;
    }

    fprintf(out, " can be in %d number system -> %d in 10 decimal number system\n", base, negative ? -res : res);
    return U_OK;
}

u_status_t task_processing(FILE *in, FILE *out) {
    size_t size = 128;
    size_t len = 0;
    u_status_t st;

    int *buf = (int *)malloc(size * sizeof(int));
    if (!buf) return U_MEMORY_ALLOCATE_ERROR;

    int c;
    int max_c = 0;
    int number_opened = 0;
    int number_sign = 1;
    int is_negative = 0;

    c = fgetc(in);
    if (c == EOF) return U_INVALID_FORMAT;
    do {
        if (is_ts_digit(c)) {
            if (c == '0' && !number_opened) continue;
            number_opened = 1;
            if (ts_cmp(c, max_c) || !max_c) {
                max_c = c;
            }
            if (number_sign == -1) {
                fputc('-', out);
                number_sign = 1;
                is_negative = 1;
            }
            fputc(c, out);
            if (len + 1 >= size) {
                size *= 2;
                int *tmp = (int *)realloc(buf, size * sizeof(int));
                if (!tmp) { free(buf); return U_MEMORY_REALLOCATE_ERROR; }
                buf = tmp;
            }
            buf[len++] = ts_digit_to_int(c);

        } else {
            if (c == '-') { number_sign *= -1; } else { number_sign = 1; }
            if (number_opened) {
                st = process_number(out, buf, len, max_c, is_negative);
                if (st != U_OK) return st;
                number_opened = 0;
                is_negative = 0;
                len = 0;
                max_c = 0;
            }
            max_c = 0;
            number_opened = 0;
            len = 0;
        }

    } while ((c = fgetc(in)) != EOF);

    if (number_opened) {
        st = process_number(out, buf, len, max_c, is_negative);
        if (st != U_OK) return st;
    }

    free(buf);
    return U_OK;
}

u_status_t process_file(const char *input_file, const char *output_file) {
    FILE *in = fopen(input_file, "r");
    if (!in) {
        fprintf(stderr, "At input file %s opening: ", input_file);
        return U_INVALID_FORMAT;
    }

    FILE *out = fopen(output_file, "w");
    if (!out) {
        fprintf(stderr, "At output file %s opening: ", output_file);
        fclose(in);
        return U_INVALID_FORMAT;
    }

    u_status_t status = task_processing(in, out);

    fclose(out);
    fclose(in);

    return status;
}
