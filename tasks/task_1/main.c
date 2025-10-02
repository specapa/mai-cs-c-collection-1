#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "args.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <x> <flag>\nFlags: -h -p -s -e -a -f\n", argv[0]);
        return 1;
    }

    const char *s_x = argv[1];
    const char *s_flag = argv[2];

    long long x;
    u_status_t parse_status = parse_signed_ll(s_x, &x, LLONG_MIN, LLONG_MAX);
    if (parse_status != U_OK) {
        print_error_prefix(stderr);
        if (parse_status == U_INVALID_FORMAT) fprintf(stderr, "invalid integer format for x\n");
        else if (parse_status == U_OVERFLOW) fprintf(stderr, "integer out of range for x\n");
        return 2;
    }

    flag_t flag;
    if (!parse_flag(s_flag, &flag)) {
        print_error_prefix(stderr);
        fprintf(stderr, "unknown flag '%s'\n", s_flag);
        return 3;
    }

    /* Validate flag-specific input */
    if (flag == FLAG_E) {
        if (x < 1 || x > 10) {
            print_error_prefix(stderr);
            fprintf(stderr, "for -e, x must be between 1 and 10 inclusive\n");
            return 4;
        }
    }
    if (flag == FLAG_A || flag == FLAG_F) {
        if (x < 0) {
            print_error_prefix(stderr);
            fprintf(stderr, "for -a and -f, x must be non-negative\n");
            return 4;
        }
    }
    if (flag == FLAG_P) {
        if (x <= 1) {
            print_error_prefix(stderr);
            fprintf(stderr, "for -p, x must be > 1 to determine prime/composite\n");
            return 4;
        }
    }

    status_t s = run_command(x, flag, stdout);
    if (s == STATUS_OK) return 0;
     print_error_prefix(stderr);
    switch (s) {
        case STATUS_INVALID_ARGUMENT: fprintf(stderr, "invalid argument or range\n"); break;
        case STATUS_OVERFLOW: fprintf(stderr, "overflow occurred during computation\n"); break;
        case STATUS_MEMORY_ERROR: fprintf(stderr, "memory allocation failed\n"); break;
        case STATUS_RANGE_ERROR: fprintf(stderr, "value out of allowed range\n"); break;
        default: fprintf(stderr, "unknown error\n"); break;
    }
    return 5;
}
