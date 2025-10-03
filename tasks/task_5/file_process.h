#ifndef FILE_PROCESS_H
#define FILE_PROCESS_H

#include "args.h"
#include "../../include/utils.h"

u_status_t process_file(const char *input_file, const char *output_file, flag_t flag);

u_status_t process_flag_d(FILE *in, FILE *out);
u_status_t process_flag_i(FILE *in, FILE *out);
u_status_t process_flag_s(FILE *in, FILE *out);
u_status_t process_flag_a(FILE *in, FILE *out);

#endif /* FILE_PROCESS_H */
