#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "args.h"

int main(int argc, char *argv[]) {
    if (argc == 1) {
        fprintf(stderr, 
"Usage: %s <flag> <1>...<n>\n\
Flags:\n\
-q <epsilon> <a> <b> <c> - are a,b,c coefficients of the quadratic equation? Solution with shafting.\n\
-m <x> <y> - y %% x <> 0?\n\
-t <epsilon> <a> <b> <c> - are a,b,c sides of the triangle?\n\
", argv[0]);
        return 1;
    }

    const char *s_flag = argv[1];
    const char *s_x = argv[1];

    flag_t flag;
    if (!parse_flag(s_flag, &flag)) {
        print_error_prefix(stderr);
        fprintf(stderr, "unknown flag '%s'\n", s_flag);
        return 2;
    }

    /* Validate flag-specific input */
    if (flag == FLAG_Q) {
        if (argc != 6) {
            print_error_prefix(stderr);
            fprintf(stderr, "Use -q with <epsilon> <a> <b> <c>\n");
            return 3;
        }
    } else if (flag == FLAG_M) {
        if (argc != 4) {
            print_error_prefix(stderr);
            fprintf(stderr, "Use -m with <x> <y>\n");
            return 3;
        }
    } else if (flag == FLAG_T) {
        if (argc != 6) {
            print_error_prefix(stderr);
            fprintf(stderr, "Use -t with <epsilon> <a> <b> <c>\n");
            return 3;
        }
    }
    status_t s = run_command(flag, argv, stdout);
    if (s == STATUS_OK) return 0;
    u_status_print(stderr, s, status_to_string);
    return s;
}
