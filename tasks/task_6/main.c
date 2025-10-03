#include <stdio.h>
#include <stdlib.h>
#include "integral.h"
#include "limits.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Use with one arg: {epsilon}\n");
        return 1;
    }

    double eps;
    u_status_t s = parse_double(argv[1], &eps, 0, __DBL_MAX__);
    if (s != U_OK) {
        fprintf(stderr, "On parsing epsilon: ");
        u_status_print(stderr, s, u_status_to_string);
        return s;
    }

    double a, b, c, d;
    u_status_t st;
    st = integral_a(eps, &a);
    if (st == U_OK) {
        printf("a = %.15f\n", a);
    } else {
        u_status_print(stderr, st, u_status_to_string);
    }
    st = integral_b(eps, &b);
    if (st == U_OK) {
        printf("b = %.15f\n", b);
    } else {
        u_status_print(stderr, st, u_status_to_string);
    }
    st = integral_c(eps, &c);
    if (st == U_OK) {
        printf("c = %.15f\n", c);
    } else {
        u_status_print(stderr, st, u_status_to_string);
    }
    st = integral_d(eps, &d);
    if (st == U_OK) {
        printf("d = %.15f\n", d);
    } else {
        u_status_print(stderr, st, u_status_to_string);
    }

    return 0;
}
