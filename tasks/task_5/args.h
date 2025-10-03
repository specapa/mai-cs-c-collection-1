#ifndef ARGS_H
#define ARGS_H

#include <stdio.h>
#include "../../include/utils.h"

typedef enum {
    FLAG_NONE = 0,
    FLAG_D,
    FLAG_ND,
    FLAG_I,
    FLAG_NI,
    FLAG_S,
    FLAG_NS,
    FLAG_A,
    FLAG_NA
} flag_t;

u_status_t parse_flag(const char *s, flag_t *out_flag);
static inline short is_n_flag(flag_t flag) {
    return flag % 2;
}

#endif /* ARGS_H */
