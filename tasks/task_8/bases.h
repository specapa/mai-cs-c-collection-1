#ifndef BASES_H
#define BASES_H

#include "../../include/utils.h"

u_status_t parse_unsigned_short(const char *s, unsigned short *out_value, unsigned short min_allowed, unsigned short max_allowed);
u_status_t parse_n_base_to_ll(const char *s, long long *out_value, unsigned long long base);
u_status_t convert_ll_to_n_base(long long input_value, char **output_string, unsigned long long base);

#endif // BASES_H