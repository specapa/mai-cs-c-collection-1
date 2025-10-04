#include <stdio.h>
#include <stdlib.h>
#include "mathconst.h"
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

    double e, pi, ln2, sqrt2, gamma, real_eps;
    u_status_t st;

    // число e
    st = compute_e_limit(eps, &e, &real_eps);
    if (st == U_OVERFLOW) printf("Attention! Low accuracy: %.15f ", real_eps);
    if (st == U_OK || st == U_OVERFLOW)
        printf("e (предел) = %.15f\n", e);
    else
        u_status_print(stderr, st, u_status_to_string);

    st = compute_e_series(eps, &e, &real_eps);
    if (st == U_OVERFLOW) printf("Attention! Low accuracy: %.15f ", real_eps);
    if (st == U_OK || st == U_OVERFLOW)
        printf("e (ряд) = %.15f\n", e);
    else
        u_status_print(stderr, st, u_status_to_string);

    st = compute_e_equation(eps, &e, &real_eps);
    if (st == U_OVERFLOW) printf("Attention! Low accuracy: %.15f ", real_eps);
    if (st == U_OK || st == U_OVERFLOW)
        printf("e (уравнение) = %.15f\n", e);
    else
        u_status_print(stderr, st, u_status_to_string);

    // число pi
    st = compute_pi_limit(eps, &pi, &real_eps);
    if (st == U_OVERFLOW) printf("Attention! Low accuracy: %.15f ", real_eps);
    if (st == U_OK || st == U_OVERFLOW)
        printf("pi (предел) = %.15f\n", pi);
    else
        u_status_print(stderr, st, u_status_to_string);

    st = compute_pi_limit_ln(eps, &pi, &real_eps);
    if (st == U_OVERFLOW) printf("Attention! Low accuracy: %.15f ", real_eps);
    if (st == U_OK || st == U_OVERFLOW)
        printf("pi (предел через ln) = %.15f\n", pi);
    else
        u_status_print(stderr, st, u_status_to_string);

    st = compute_pi_series(eps, &pi, &real_eps);
    if (st == U_OVERFLOW) printf("Attention! Low accuracy: %.15f ", real_eps);
    if (st == U_OK || st == U_OVERFLOW)
        printf("pi (ряд) = %.15f\n", pi);
    else
        u_status_print(stderr, st, u_status_to_string);

    st = compute_pi_equation(eps, &pi, &real_eps);
    if (st == U_OVERFLOW) printf("Attention! Low accuracy: %.15f ", real_eps);
    if (st == U_OK || st == U_OVERFLOW)
        printf("pi (уравнение) = %.15f\n", pi);
    else
        u_status_print(stderr, st, u_status_to_string);

    // ln2
    st = compute_ln2_limit(eps, &ln2, &real_eps);
    if (st == U_OVERFLOW) printf("Attention! Low accuracy: %.15f ", real_eps);
    if (st == U_OK || st == U_OVERFLOW)
        printf("ln2 (предел) = %.15f\n", ln2);
    else
        u_status_print(stderr, st, u_status_to_string);

    st = compute_ln2_series(eps, &ln2, &real_eps);
    if (st == U_OVERFLOW) printf("Attention! Low accuracy: %.15f ", real_eps);
    if (st == U_OK || st == U_OVERFLOW)
        printf("ln2 (ряд) = %.15f\n", ln2);
    else
        u_status_print(stderr, st, u_status_to_string);

    st = compute_ln2_equation(eps, &ln2, &real_eps);
    if (st == U_OVERFLOW) printf("Attention! Low accuracy: %.15f ", real_eps);
    if (st == U_OK || st == U_OVERFLOW)
        printf("ln2 (уравнение) = %.15f\n", ln2);
    else
        u_status_print(stderr, st, u_status_to_string);

    // sqrt2
    st = compute_sqrt2_limit(eps, &sqrt2, &real_eps);
    if (st == U_OVERFLOW) printf("Attention! Low accuracy: %.15f ", real_eps);
    if (st == U_OK || st == U_OVERFLOW)
        printf("sqrt2 (предел) = %.15f\n", sqrt2);
    else
        u_status_print(stderr, st, u_status_to_string);

    st = compute_sqrt2_series(eps, &sqrt2, &real_eps);
    if (st == U_OVERFLOW) printf("Attention! Low accuracy: %.15f ", real_eps);
    if (st == U_OK || st == U_OVERFLOW)
        printf("sqrt2 (ряд) = %.15f\n", sqrt2);
    else
        u_status_print(stderr, st, u_status_to_string);

    st = compute_sqrt2_equation(eps, &sqrt2, &real_eps);
    if (st == U_OVERFLOW) printf("Attention! Low accuracy: %.15f ", real_eps);
    if (st == U_OK || st == U_OVERFLOW)
        printf("sqrt2 (уравнение) = %.15f\n", sqrt2);
    else
        u_status_print(stderr, st, u_status_to_string);

    // gamma
    st = compute_gamma_limit(eps, &gamma, &real_eps);
    if (st == U_OVERFLOW) printf("Attention! Low accuracy: %.15f ", real_eps);
    if (st == U_OK || st == U_OVERFLOW)
        printf("gamma (предел) = %.15f\n", gamma);
    else
        u_status_print(stderr, st, u_status_to_string);

    st = compute_gamma_series(eps, &gamma, &real_eps, pi);
    if (st == U_OVERFLOW) printf("Attention! Low accuracy: %.15f ", real_eps);
    if (st == U_OK || st == U_OVERFLOW)
        printf("gamma (ряд) = %.15f\n", gamma);
    else
        u_status_print(stderr, st, u_status_to_string);

    st = compute_gamma_equation(eps, &gamma, &real_eps);
    if (st == U_OVERFLOW) printf("Attention! Low accuracy: %.15f ", real_eps);
    if (st == U_OK || st == U_OVERFLOW)
        printf("gamma (уравнение) = %.15f\n", gamma);
    else
        u_status_print(stderr, st, u_status_to_string);

    return 0;
}