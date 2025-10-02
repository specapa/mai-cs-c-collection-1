#include <gtest/gtest.h>
#include <cmath>

extern "C" {
    #include "math_operations.h"
    #include "args.h"
}

TEST(QuadSolveAllPermutationsTests, SimpleQuadratic) {
    double coeffs[3] = {1, -3, 2};
    double eps = 1e-6;

    quad_solution_t **solutions = nullptr;
    size_t out_count = 0;

    status_t st = quad_solve_all_permutations(coeffs, eps, &solutions, &out_count);

    ASSERT_EQ(st, STATUS_OK);
    ASSERT_GT(out_count, 0u);

    bool found_expected = false;
    for (size_t i = 0; i < out_count; i++) {
        quad_solution_t *sol = solutions[i];
        if (sol->root_type == TWO_ROOTS) {
            double x1 = sol->roots[0];
            double x2 = sol->roots[1];
            if ((fabs(x1 - 1.0) < eps && fabs(x2 - 2.0) < eps) ||
                (fabs(x1 - 2.0) < eps && fabs(x2 - 1.0) < eps)) {
                found_expected = true;
            }
        }
    }

    EXPECT_TRUE(found_expected);

    for (size_t i = 0; i < out_count; i++) {
        free(solutions[i]);
    }
    free(solutions);
}

TEST(QuadSolveAllPermutationsTests, LinearEquation) {
    double coeffs[3] = {0, 2, -4}; // 2x - 4 = 0 => x = 2
    double eps = 1e-6;

    quad_solution_t **solutions = nullptr;
    size_t out_count = 0;

    status_t st = quad_solve_all_permutations(coeffs, eps, &solutions, &out_count);

    ASSERT_EQ(st, STATUS_OK);
    ASSERT_GT(out_count, 0u);

    bool found_expected = false;
    for (size_t i = 0; i < out_count; i++) {
        quad_solution_t *sol = solutions[i];
        if (sol->root_type == ONE_ROOT && fabs(sol->roots[0] - 2.0) < eps) {
            found_expected = true;
        }
    }

    EXPECT_TRUE(found_expected);

    for (size_t i = 0; i < out_count; i++) {
        free(solutions[i]);
    }
    free(solutions);
}

TEST(QuadSolveAllPermutationsTests, NoRoots) {
    double coeffs[3] = {1, 0, 1}; // x^2 + 1 = 0 => нет действительных корней
    double eps = 1e-6;

    quad_solution_t **solutions = nullptr;
    size_t out_count = 0;

    status_t st = quad_solve_all_permutations(coeffs, eps, &solutions, &out_count);

    ASSERT_EQ(st, STATUS_OK);
    ASSERT_GT(out_count, 0u);

    bool found_no_roots = false;
    for (size_t i = 0; i < out_count; i++) {
        if (solutions[i]->root_type == NO_ROOTS) {
            found_no_roots = true;
        }
    }

    EXPECT_TRUE(found_no_roots);

    for (size_t i = 0; i < out_count; i++) {
        free(solutions[i]);
    }
    free(solutions);
}
