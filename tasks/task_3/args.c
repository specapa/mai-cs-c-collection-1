#include <string.h>
#include <stdio.h>
#include <math.h>
#include "../../include/utils.h"
#include "args.h"
#include "math_operations.h"
#include "stdlib.h"

int parse_flag(const char *s, flag_t *out_flag) {
    if (s == NULL || out_flag == NULL) return 0;
    if (s[0] != '-' && s[0] != '/') return 0;
    if (s[2] != '\0') return 0;
    char c = s[1];
    switch (c) {
        case 'q': *out_flag = FLAG_Q; return 1;
        case 'm': *out_flag = FLAG_M; return 1;
        case 't': *out_flag = FLAG_T; return 1;
        default: return 0;
    }
}

status_t run_command(flag_t flag, char *argv[], FILE *out) {
    switch (flag) {
        case FLAG_M: {
                short error = 0;
                long long int a, b;
                u_status_t s_a, s_b;
                s_a = parse_signed_ll(argv[2], &a, LLONG_MIN, LLONG_MAX);
                s_b = parse_signed_ll(argv[3], &b, LLONG_MIN, LLONG_MAX);
                if (s_a != U_OK) {
                    fprintf(stderr, "On parse first arg: ");
                    return s_a;
                }
                if (s_b != U_OK) {
                    fprintf(stderr, "On parse second arg: ");
                    return s_b;
                }
                int is_m;
                status_t result = is_multiple(a, b, &is_m);
                if (result != STATUS_OK) {
                    return result;
                }
                if (is_m) {
                    fprintf(out, "%lld is a multiple of %lld\n", a, b);
                } else {
                    fprintf(out, "%lld is not a multiple of %lld\n", a, b);
                }
                return STATUS_OK;
            }
        case FLAG_T:
        case FLAG_Q:
            {
                short error = 0;
                double e, a, b, c;
                u_status_t s_e, s_a, s_b, s_c;
                s_e = parse_double(argv[2], &e, -INFINITY, INFINITY);
                s_a = parse_double(argv[3], &a, -INFINITY, INFINITY);
                s_b = parse_double(argv[4], &b, -INFINITY, INFINITY);
                s_c = parse_double(argv[5], &c, -INFINITY, INFINITY);
                if (s_e != U_OK) {
                    fprintf(stderr, "On parse first arg {e}: ");
                    return s_e;
                }
                if (s_a != U_OK) {
                    fprintf(stderr, "On parse second arg {a}: ");
                    return s_a;
                }
                if (s_b != U_OK) {
                    fprintf(stderr, "On parse third arg {b}: ");
                    return s_b;
                }
                if (s_c != U_OK) {
                    fprintf(stderr, "On parse forth arg {c}: ");
                    return s_c;
                }
                if (error) return STATUS_INVALID_ARGUMENT;
                if (flag == FLAG_T) {
                    int is_rt;
                    const double sides[] = {a, b, c};
                    status_t result = is_right_triangle(sides, e, &is_rt);
                    if (result != STATUS_OK) {
                        return result;
                    }
                    if (is_rt) {
                        fprintf(out, "Right triangle: True\n");
                    } else {
                        fprintf(out, "Right triangle: False\n");
                    }
                    return STATUS_OK;
                } else {
                    quad_solution_t **solutions = (quad_solution_t **)NULL;
                    size_t out_count;
                    double coeffs[3] = {a, b, c};
                    status_t result = quad_solve_all_permutations(coeffs, e, &solutions, &out_count);
                    if (result != STATUS_OK) {
                        return result;
                    }
                    fprintf(out, "Find %lu solution%s in next equalation:\n", out_count, out_count == 1 ? "" : "s");
                    for (int i = 0; i < out_count; ++i) {
                        solution_to_string(solutions[i], out);
                        free(solutions[i]);
                    }
                    free(solutions);
                    return STATUS_OK;
                }
                return STATUS_NOT_IMPLEMENTED;
            }
        default:
            return STATUS_INVALID_ARGUMENT;
    }
}
