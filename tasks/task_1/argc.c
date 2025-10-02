#include "args.h"
#include "../../include/utils.h"
#include <string.h>
#include <stdio.h>

int parse_flag(const char *s, flag_t *out_flag) {
    if (s == NULL || out_flag == NULL) return 0;
    if (s[0] != '-' && s[0] != '/') return 0;
    if (s[2] != '\0') return 0;
    char c = s[1];
    switch (c) {
        case 'h': *out_flag = FLAG_H; return 1;
        case 'p': *out_flag = FLAG_P; return 1;
        case 's': *out_flag = FLAG_S; return 1;
        case 'e': *out_flag = FLAG_E; return 1;
        case 'a': *out_flag = FLAG_A; return 1;
        case 'f': *out_flag = FLAG_F; return 1;
        default: return 0;
    }
}

status_t run_command(long long x, flag_t flag, FILE *out) {
    switch (flag) {
        case FLAG_H:
            if (x == 0) return STATUS_INVALID_ARGUMENT;
            return op_multiples_up_to_100(x, out);
        case FLAG_P: {
            int kind = 0;
            status_t s = op_prime_test(x, &kind);
            if (s != STATUS_OK) return s;
            if (kind == 1) fprintf(out, "%lld is prime\n", x);
            else fprintf(out, "%lld is composite\n", x);
            return STATUS_OK;
        }
        case FLAG_S:
            return op_split_hex_digits(x, out);
        case FLAG_E:
            return op_print_power_table((int)x, out);
        case FLAG_A: {
            unsigned long long sum;
            status_t s = op_sum_1_to_x(x, &sum);
            if (s != STATUS_OK) return s;
            fprintf(out, "%llu\n", sum);
            return STATUS_OK;
        }
        case FLAG_F: {
            unsigned long long fact;
            status_t s = op_factorial(x, &fact);
            if (s != STATUS_OK) return s;
            fprintf(out, "%llu\n", fact);
            return STATUS_OK;
        }
        default:
            return STATUS_INVALID_ARGUMENT;
    }
}
