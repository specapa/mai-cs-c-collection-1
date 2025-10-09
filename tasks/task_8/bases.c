#include "bases.h"
#include <ctype.h>
#include "../../include/utils.h"

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
    unsigned long long acc = 0ULL;
    while (*p) {
        if (!isdigit((unsigned char)*p)) return U_INVALID_FORMAT;
        int d = *p - '0';
        if (acc > (SHRT_MAX / 10ULL)) return U_OVERFLOW;
        acc = acc * 10ULL + (unsigned long long)d;
        ++p;
    }
    if (acc < min_allowed || acc > max_allowed) return U_INVALID_FORMAT;
    *out_value = acc;
    return U_OK;
}

u_status_t parse_n_base_to_ll(const char *s, long long *out_value, long long min_allowed, long long max_allowed) {
    return U_INVALID_FORMAT;
}