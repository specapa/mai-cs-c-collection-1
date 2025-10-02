#ifndef ARGS_H
#define ARGS_H

#include "math_operations.h"
#include <stdio.h>

typedef enum {
    FLAG_NONE = 0,
    FLAG_Q,
    FLAG_M,
    FLAG_T
} flag_t;

int parse_flag(const char *s, flag_t *out_flag);
status_t run_command(flag_t flag, char *argv[], FILE *out);

#endif /* ARGS_H */
