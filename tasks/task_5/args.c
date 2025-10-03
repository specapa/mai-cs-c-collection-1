#include "args.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


u_status_t parse_flag(const char *s, flag_t *out_flag) {
    if (s == NULL || out_flag == NULL) return U_INVALID_FORMAT;
    if (s[0] != '-' && s[0] != '/') return U_INVALID_FORMAT;
    int isNFlag = (s[1] == 'n');
    if (s[2 + isNFlag] != '\0') return U_INVALID_FORMAT;
    char c = s[1 + isNFlag];
    switch (c) {
        case 'd': *out_flag = isNFlag ? FLAG_ND : FLAG_D; return U_OK;
        case 'i': *out_flag = isNFlag ? FLAG_NI : FLAG_I; return U_OK;
        case 's': *out_flag = isNFlag ? FLAG_NS : FLAG_S; return U_OK;
        case 'a': *out_flag = isNFlag ? FLAG_NA : FLAG_A; return U_OK;
        default: return U_INVALID_FORMAT;
    }
}
