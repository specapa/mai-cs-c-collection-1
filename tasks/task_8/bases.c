#include "bases.h"
#include <ctype.h>
#include <stdlib.h>
#include "../../include/utils.h"

static inline short is_ts_digit(char c) {
    return (c >= '0' && c <= '9' || c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z');
}

static inline int ts_digit_to_int(char c) {
    if (c >= 'A' && c <= 'Z') return (int)c - 55;
    if (c >= 'a' && c <= 'z') return (int)c - 87;
    if (c >= '0' && c <= '9') return (int)c - 48;
    return -1;
}

static inline char int_to_ts_digit(int c) {
    if (c >= 10) return c + 87;
    return c + 48;
}

static inline short is_n_base_digit(char c, unsigned int base) {
    int v = ts_digit_to_int(c);
    if (v == -1) return 0;
    return v < base;
}

static inline short ts_cmp(char l, char r) {
    if (l >= 'A' && l <= 'Z') l += 32;
    if (r >= 'A' && r <= 'Z') r += 32;
    return l > r;
}

u_status_t parse_unsigned_short(const char *s, unsigned short *out_value, unsigned short min_allowed, unsigned short max_allowed) {
    if (s == NULL || out_value == NULL) return U_INVALID_FORMAT;
    const char *p = s;
    while (isspace((unsigned char)*p)) ++p;
    int neg = 0;
    if (*p == '+' || *p == '-') {
        if (*p == '-') return U_INVALID_FORMAT;
        ++p;
    }
    if (!isdigit((unsigned char)*p)) return U_INVALID_FORMAT;
    unsigned short acc = (unsigned short)0U;
    while (*p) {
        if (!isdigit((unsigned char)*p)) return U_INVALID_FORMAT;
        int d = *p - '0';
        if (acc > (USHRT_MAX / (unsigned short)10U)) return U_OVERFLOW;
        acc = acc * (unsigned short)10U + (unsigned short)d;
        ++p;
    }
    if (acc < min_allowed || acc > max_allowed) return U_INVALID_FORMAT;
    *out_value = acc;
    return U_OK;
}

u_status_t parse_n_base_to_ll(const char *s, long long *out_value, unsigned long long base) {
    if (s == NULL || out_value == NULL) return U_INVALID_FORMAT;
    const char *p = s;
    while (isspace((unsigned char)*p)) ++p;
    int neg = 0;
    if (*p == '+' || *p == '-') {
        if (*p == '-') neg = 1;
        ++p;
    }
    if (!is_n_base_digit((unsigned char)*p, base)) return U_INVALID_FORMAT;
    unsigned long long acc = 0ULL;
    while (*p) {
        if (!is_n_base_digit((unsigned char)*p, base)) return U_INVALID_FORMAT;
        int d = ts_digit_to_int(*p);
        if (acc > (ULLONG_MAX / base) - (unsigned long long)d) return U_OVERFLOW;
        acc = acc * base + (unsigned long long)d;
        ++p;
    }
    long long val;
    if (neg) {
        unsigned long long max_mag = (unsigned long long)LLONG_MAX + 1ULL; /* == -(LLONG_MIN) */
        if (acc > max_mag) return U_OVERFLOW;
        if (acc == max_mag) {
            val = LLONG_MIN;
        } else {
            val = -(long long)acc;
        }
    } else {
        if (acc > (unsigned long long)LLONG_MAX) return U_OVERFLOW;
        val = (long long)acc;
    }
    *out_value = val;
    return U_OK;
}

u_status_t convert_ll_to_n_base(long long input_value, char **output_string, unsigned long long base) {
    if (base < 2 || base > 36) return U_INVALID_FORMAT;
    if (output_string == NULL) return U_INVALID_FORMAT;

    size_t capacity = 32;
    size_t size = 0;

    char *string = (char *)calloc(capacity, sizeof(char));
    if (string == NULL) return U_MEMORY_ALLOCATE_ERROR;

    if (input_value == 0) {
        string[0] = '0';
        string[1] = '\0';
        *output_string = string;
        return U_OK;
    }

    int is_negative = (input_value < 0);
    unsigned long long abs_value;
    
    if (input_value == LLONG_MIN) {
        abs_value = (unsigned long long)LLONG_MAX + 1ULL;
    } else {
        abs_value = (unsigned long long)(is_negative ? -input_value : input_value);
    }

    while (abs_value > 0) {
        if (size >= capacity - 2) {
            capacity *= 2;
            char *tmp = (char *)realloc(string, capacity);
            if (tmp == NULL) { free(string); return U_MEMORY_REALLOCATE_ERROR; }
            string = tmp;
        }
        string[size++] = int_to_ts_digit(abs_value % base);
        abs_value /= base;
    }

    if (is_negative) {
        if (size >= capacity - 1) {
            capacity++;
            char *tmp = (char *)realloc(string, capacity);
            if (tmp == NULL) { free(string); return U_MEMORY_REALLOCATE_ERROR; }
            string = tmp;
        }
        string[size++] = '-';
    }

    string[size] = '\0';

    for (size_t i = 0; i < size / 2; i++) {
        char temp = string[i];
        string[i] = string[size - 1 - i];
        string[size - 1 - i] = temp;
    }

    *output_string = string;
    return U_OK;
}