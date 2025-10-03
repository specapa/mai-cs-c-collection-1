#ifndef PRIME_AT_H
#define PRIME AT_H

#include <stdio.h>
#include <stdint.h>

typedef enum {
    STATUS_OK = 0,
    STATUS_INVALID_ARGUMENT,
    STATUS_OVERFLOW,
    STATUS_MEMORY_ERROR,
    STATUS_RANGE_ERROR
} status_t;

status_t find_prime_number_by_number(uint64_t, uint64_t *);
status_t prime_with_eratosphen(uint64_t n, uint64_t limit, uint64_t *out);
status_t compute_limit(uint64_t n, uint64_t *out);
const char *status_to_string(int st);

#endif // PRIME_AT_H