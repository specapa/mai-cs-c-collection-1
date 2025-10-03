#ifndef STR_CON_H
#define STR_CON_H

#include <stdio.h>
#include "../../include/utils.h"

u_status_t concatenate(const char *str1, const char *str2, char **result);
u_status_t add_out_prefix(const char *file_prefix, const char *path, char **result);

#endif /* STR_CON_H */
