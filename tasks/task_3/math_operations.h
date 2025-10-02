#ifndef MATH_OPS_H
#define MATH_OPS_H

#include <stddef.h>
#include <stdio.h>

typedef enum {
    STATUS_OK = 0,
    STATUS_INVALID_ARGUMENT,
    STATUS_OVERFLOW,
    STATUS_MEMORY_ALLOCATE_ERROR,
    STATUS_MEMORY_REALLOCATE_ERROR,
    STATUS_NEGATIVE_NOT_ALLOWED,
    STATUS_RANGE_ERROR,
    STATUS_MATH_ERROR,
    STATUS_DIVIDE_BY_ZERO,
    STATUS_NOT_IMPLEMENTED,
} status_t;

typedef enum {
    NO_ROOTS = 0,
    ONE_ROOT,
    TWO_ROOTS,
    INF_ROOTS,
} root_t;

typedef struct {
    double coeffs[3];
    root_t root_type;
    double roots[2];
} quad_solution_t;

const char *status_to_string(int st);
const char *solution_to_string(quad_solution_t *, FILE *);

status_t quad_solve_all_permutations(double a[3], double eps, quad_solution_t ***out_solutions, size_t *out_count);
status_t solve_quadratic(double a, double b, double c, double eps, quad_solution_t **out_solution);
status_t is_multiple(long numerator, long denominator, int *is_multiple);
status_t is_right_triangle(const double sides[3], double eps, int *is_right_triangle);

static void sort3(double a[3]);

#endif /* MATH_OPS_H */