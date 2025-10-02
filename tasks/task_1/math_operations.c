#include "math_operations.h"
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

static int is_prime_basic(long long n) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0) return 0;
    for (long long i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return 0;
    }
    return 1;
}

status_t op_multiples_up_to_100(long long x, FILE *out) {
    if (out == NULL) return STATUS_INVALID_ARGUMENT;
    if (x == 0) return STATUS_INVALID_ARGUMENT;
    int found = 0;
    long long start = (x > 0) ? x : -x; /* abs */
    for (int n = 1; n <= 100; ++n) {
        if ((n % start) == 0) {
            if (!found) {
                fprintf(out, "%d", n);
                found = 1;
            } else {
                fprintf(out, " %d", n);
            }
        }
    }
    if (!found) {
        fprintf(out, "No natural numbers <=100 divisible by %lld\n", x);
    } else {
        fprintf(out, "\n");
    }
    return STATUS_OK;
}

status_t op_prime_test(long long x, int *out_kind) {
    if (out_kind == NULL) return STATUS_INVALID_ARGUMENT;
    if (x <= 1) return STATUS_INVALID_ARGUMENT;
    if (is_prime_basic(x)) {
        *out_kind = 1; /* prime */
    } else {
        *out_kind = 2; /* composite */
    }
    return STATUS_OK;
}

status_t op_split_hex_digits(long long x, FILE *out) {
    if (out == NULL) return STATUS_INVALID_ARGUMENT;
    unsigned long long val = (x < 0) ? (unsigned long long)(-x) : (unsigned long long)x;
    if (val == 0) {
        fprintf(out, "0\n");
        return STATUS_OK;
    }
    unsigned int digits[32];
    size_t cnt = 0;
    while (val > 0) {
        digits[cnt++] = (unsigned int)(val & 0xF);
        val >>= 4;
    }
    if (x < 0) fprintf(out, "-");
    for (size_t i = 0; i < cnt; ++i) {
        if (i) fprintf(out, " ");
        fprintf(out, "%X", digits[cnt - 1 - i]);
    }
    fprintf(out, "\n");
    return STATUS_OK;
}

status_t op_print_power_table(int x, FILE *out) {
    if (out == NULL) return STATUS_INVALID_ARGUMENT;
    if (x < 1 || x > 10) return STATUS_RANGE_ERROR;
    /* base 1..10, exponent 1..x */
    for (int exp = 1; exp <= x; ++exp) {
        for (int base = 1; base <= 10; ++base) {
            /* base^exp */
            unsigned long long acc = 1ULL;
            for (int e = 0; e < exp; ++e) {
                if (acc > ULLONG_MAX / (unsigned long long)base) return STATUS_OVERFLOW;
                acc *= (unsigned long long)base;
            }
            if (base > 1) fprintf(out, " ");
            fprintf(out, "%llu", (unsigned long long)acc);
        }
        fprintf(out, "\n");
    }
    return STATUS_OK;
}

status_t op_sum_1_to_x(long long x, unsigned long long *out_sum) {
    if (out_sum == NULL) return STATUS_INVALID_ARGUMENT;
    if (x < 1) return STATUS_INVALID_ARGUMENT;
    unsigned long long n = (unsigned long long)x;
    if (n > 0 && (ULLONG_MAX / n) < (n + 1ULL)) return STATUS_OVERFLOW;
    unsigned long long prod = n * (n + 1ULL);
    unsigned long long sum = prod / 2ULL;
    *out_sum = sum;
    return STATUS_OK;
}

status_t op_factorial(long long x, unsigned long long *out_fact) {
    if (out_fact == NULL) return STATUS_INVALID_ARGUMENT;
    if (x < 0) return STATUS_INVALID_ARGUMENT;
    unsigned long long res = 1ULL;
    for (long long i = 2; i <= x; ++i) {
        if (res > ULLONG_MAX / (unsigned long long)i) return STATUS_OVERFLOW;
        res *= (unsigned long long)i;
    }
    *out_fact = res;
    return STATUS_OK;
}
