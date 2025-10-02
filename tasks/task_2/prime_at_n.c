#include <stdlib.h>
#include <math.h>
#include "prime_at_n.h"

const char *status_to_string(int st) {
    switch (st) {
        case STATUS_OK:                return "OK";
        case STATUS_INVALID_ARGUMENT:  return "Invalid argument";
        case STATUS_OVERFLOW:          return "Overflow";
        case STATUS_MEMORY_ERROR:      return "Can't allocate memory";
        case STATUS_RANGE_ERROR:       return "Index out of range";
        default:                       return "Unexpected error";
    }
}

status_t prime_with_eratosphen(uint64_t n, uint64_t limit, uint64_t *out) {
    char *is_prime = calloc(limit + 1, sizeof(uint8_t));
    if (!is_prime) {
        return STATUS_MEMORY_ERROR;
    } 
    is_prime[2] = 1;
    for (uint64_t i = 3; i <= limit; i += 2) is_prime[i] = 1;
    for (uint64_t i = 3; i * i <= limit; i += 2) {
        if (is_prime[i]) {
            for (uint64_t j = i * i; j <= limit; j += i) {
                is_prime[j] = 0;
            }
        }
    }
    uint64_t prime_count = 0;
    uint64_t l = 2;
    while (l < limit && prime_count != n) {
        if (is_prime[l]) {
            ++prime_count;
            if (prime_count == n) break;
        }
        ++l;
    }    
    if (prime_count == n) {
        *out = l;
        free(is_prime);
        return STATUS_OK;
    }
    free(is_prime);
    return STATUS_RANGE_ERROR;
}

status_t compute_limit(uint64_t n, uint64_t *out) {
    if (!out) return STATUS_INVALID_ARGUMENT;

    if (n < 6) {
        *out = 12;
        return STATUS_OK;
    }

    if (n <= 1) return STATUS_INVALID_ARGUMENT;

    double val = log((double)n) + log(log((double)n));
    if (val < 0) return STATUS_INVALID_ARGUMENT;

    double prod = (double)n * val;

    if (prod > (double)UINT64_MAX) {
        return STATUS_OVERFLOW;
    }

    *out = (uint64_t)prod;
    return STATUS_OK;
}

status_t find_prime_number_by_number(uint64_t n, uint64_t *out) {
    status_t s_calc;
    status_t s_limit;
    if (n == 0) return STATUS_INVALID_ARGUMENT;
    if (n == 1) {
        *out = 2;
        return STATUS_OK;
    }
    uint64_t limit;
    s_limit = compute_limit(n, &limit);
    if(s_limit != 0) return s_limit;
    s_calc = prime_with_eratosphen(n, limit, out);
    return s_calc;
}