#ifndef BASES_H
#define BASES_H

#include "../../include/utils.h"

u_status_t parse_unsigned_short(const char *s, unsigned short *out_value, unsigned short min_allowed, unsigned short max_allowed);
u_status_t parse_n_base_to_ll(const char *s, long long *out_value, long long min_allowed, long long max_allowed);

#endif // BASES_H