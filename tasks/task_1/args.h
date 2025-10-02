#ifndef ARGS_H
#define ARGS_H

#include "math_operations.h"
#include <stdio.h>

typedef enum {
    FLAG_NONE = 0,
    FLAG_H,
    FLAG_P,
    FLAG_S,
    FLAG_E,
    FLAG_A,
    FLAG_F
} flag_t;

int parse_flag(const char *s, flag_t *out_flag);

status_t run_command(long long x, flag_t flag, FILE *out);

#endif /* ARGS_H */
