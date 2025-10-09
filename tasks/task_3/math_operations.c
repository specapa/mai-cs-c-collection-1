#include <stdlib.h>
#include "math_operations.h"
#include "math.h"


const char *status_to_string(int st) {
    switch (st) {
        case STATUS_OK:
            return "OK";
        case STATUS_INVALID_ARGUMENT:
            return "Invalid argument";
        case STATUS_OVERFLOW:
            return "Overflow";
        case STATUS_MEMORY_ALLOCATE_ERROR:
        case STATUS_MEMORY_REALLOCATE_ERROR:
            return "Memory error";
        case STATUS_NEGATIVE_NOT_ALLOWED:
            return "Negative not allowed";
        case STATUS_RANGE_ERROR:
            return "Range error";
        case STATUS_MATH_ERROR:
            return "Math error";
        case STATUS_DIVIDE_BY_ZERO:
            return "Divide by zero";
        case STATUS_NOT_IMPLEMENTED:
            return "Not implemented";
        default:
            return "Unknown status";
    }
}

const char *solution_type_to_string(root_t root_type) {
    switch (root_type) {
        case NO_ROOTS:
            return "No roots";
        case ONE_ROOT:
            return "One root";
        case TWO_ROOTS:
            return "Two roots";
        case INF_ROOTS:
            return "Infinity roots";
        default:
            return "??? roots";
    }
}

const char *solution_to_string(quad_solution_t *s, FILE *file) {
    fprintf(file, "%lfx^2 + %lfx + %lf = 0 ", s->coeffs[0], s->coeffs[1], s->coeffs[2]);
    fprintf(file, "has %s", solution_type_to_string(s->root_type));
    switch (s->root_type) {
        case ONE_ROOT: 
            fprintf(file, ": %lf", s->roots[0]);
            break;
        case TWO_ROOTS:
            fprintf(file, ": %lf and %lf", s->roots[0], s->roots[1]);
            break;
    }
    fputc('\n', file);
}

status_t solve_quadratic(double a, double b, double c, double eps, quad_solution_t **out_solution) {
    if (out_solution == NULL) return STATUS_INVALID_ARGUMENT;
    quad_solution_t *solution = (quad_solution_t*) calloc(1, sizeof(quad_solution_t));
    if (!solution) return STATUS_MEMORY_ALLOCATE_ERROR;

    solution->coeffs[0] = a;
    solution->coeffs[1] = b;
    solution->coeffs[2] = c;
    solution->root_type = NO_ROOTS;
    solution->roots[0] = 0.0;
    solution->roots[1] = 0.0;

    // a = 0
    if (fabs(a) < eps) {
        // b = 0
        if (fabs(b) < eps) {
            // c = 0
            if (fabs(c) < eps) {
                solution->root_type = INF_ROOTS;
                *out_solution = solution;
                return STATUS_OK;
            }
            solution->root_type = NO_ROOTS;
            *out_solution = solution;
            return STATUS_OK;
        }
        solution->roots[0] = -c / b;
        solution->root_type = ONE_ROOT;
        *out_solution = solution;
        return STATUS_OK;
    }
    double D = b * b - 4.0 * a * c;
    if (D > eps) {
        double sqrtD = sqrt(D);
        solution->root_type = TWO_ROOTS;
        double x_1 = (-b - sqrtD) / (2.0*a);
        double x_2 = (-b + sqrtD) / (2.0*a);
        if (x_1 > x_2) {
            solution->roots[0] = x_2; 
            solution->roots[1] = x_1;
        } else {
            solution->roots[0] = x_1; 
            solution->roots[1] = x_2;
        }
    } else if (fabs(D) <= eps) {
        solution->root_type = ONE_ROOT;
        solution->roots[0] = (-b) / (2.0*a);
    } else {
        solution->root_type = NO_ROOTS;
    }
    *out_solution = solution;
    return STATUS_OK;
}

status_t quad_solve_all_permutations(double coefs[3], double eps, quad_solution_t ***out_solutions, size_t *out_count) {
    if (coefs == NULL || out_solutions == NULL || out_count == NULL) return STATUS_INVALID_ARGUMENT;
    sort3(coefs);
    int start = 0;
    int end = 2;
    int uni_c = 6;
    if (coefs[0] == coefs[1]) start = 1;
    if (coefs[0] == coefs[2]) start = 2;
    if (coefs[1] == coefs[2] && !start) end = 1;
    switch (end - start) {
        case 0: uni_c = 1; break;
        case 1: uni_c = 3; break;
    }

    status_t s;
    quad_solution_t **sols = (quad_solution_t**) calloc(uni_c, sizeof(quad_solution_t*));
    if (sols == NULL) return STATUS_MEMORY_ALLOCATE_ERROR;

    static const int perms6[6][3] = {
        {0,1,2},
        {0,2,1},
        {1,0,2},
        {1,2,0},
        {2,0,1},
        {2,1,0}
    };
    
    int index = 0;
    if (uni_c == 1) {
        s = solve_quadratic(coefs[0], coefs[0], coefs[0], eps, &sols[index]);
        if (s != STATUS_OK) {
                free(sols);
                fprintf(stderr, "On solving quadric equvalution (%d): ", index);
                return s;
            }
    } else if (uni_c == 3) {
        for (int i = 0; i < 3; ++i) {
            int p0 = perms6[i][0], p1 = perms6[i][1], p2 = perms6[i][2];
            status_t s = solve_quadratic(coefs[p0], coefs[p1], coefs[p2], eps, &sols[index]);
            if (s != STATUS_OK) {
                for (int j = 0; j < index; ++j) free(sols[j]);
                free(sols);
                fprintf(stderr, "On solving quadric equvalution (%d): ", index);
                return s;
            }
            ++index;
        }
    } else {
        for (int i = 0; i < 6; ++i) {
            int p0 = perms6[i][0], p1 = perms6[i][1], p2 = perms6[i][2];
            status_t s = solve_quadratic(coefs[p0], coefs[p1], coefs[p2], eps, &sols[index]);
            if (s != STATUS_OK) {
                for (int j = 0; j < index; ++j) free(sols[j]);
                free(sols);
                fprintf(stderr, "On solving quadric equvalution (%d): ", index);
                return s;
            }
            index++;
        }
    }
    *out_solutions = sols;
    *out_count = (size_t)uni_c;
    return STATUS_OK;
}

status_t is_multiple(long numerator, long denominator, int *is_multiple) {
    if (is_multiple == NULL) return STATUS_INVALID_ARGUMENT;
    if (denominator == 0) return STATUS_DIVIDE_BY_ZERO;
    if (numerator == 0) return STATUS_INVALID_ARGUMENT;
    *is_multiple = numerator / denominator * denominator == numerator;
    return STATUS_OK;
}

static void sort3(double a[3]) {
    if (a[0] > a[1]) { double t = a[0]; a[0] = a[1]; a[1] = t; }
    if (a[1] > a[2]) { double t = a[1]; a[1] = a[2]; a[2] = t; }
    if (a[0] > a[1]) { double t = a[0]; a[0] = a[1]; a[1] = t; }
}

status_t is_right_triangle(const double sides[3], double eps, int *is_right_triangle) {
    if (sides == NULL || is_right_triangle == NULL) return STATUS_INVALID_ARGUMENT;
    double a = sides[0], b = sides[1], c = sides[2];
    if (!(a > eps && b > eps && c > eps)) {
        *is_right_triangle = 0;
        return STATUS_OK;
    }
    double s[3] = {a, b, c};
    sort3(s);
    if (!( (s[0] + s[1]) - s[2] > -eps )) {
        *is_right_triangle = 0;
        return STATUS_OK;
    }
    double lhs = sqrt(s[0]*s[0] + s[1]*s[1]);
    double rhs = s[2];
    if (fabs(lhs - rhs) <= eps) {
        *is_right_triangle = 1;
    } else {
        *is_right_triangle = 0;
    }
    return STATUS_OK;
}