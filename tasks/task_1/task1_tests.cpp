#include <gtest/gtest.h>
#include <cmath>
#include <climits>

extern "C" {
    #include "math_operations.h"
    #include "args.h"
}

// -------- op_multiples_up_to_100 --------
TEST(MathOperations, Multiples_InvalidArgs) {
    EXPECT_EQ(op_multiples_up_to_100(0, stdout), STATUS_INVALID_ARGUMENT);
    EXPECT_EQ(op_multiples_up_to_100(5, nullptr), STATUS_INVALID_ARGUMENT);
}

// -------- op_prime_test --------
TEST(MathOperations, PrimeTest) {
    int kind = 0;
    EXPECT_EQ(op_prime_test(13, &kind), STATUS_OK);
    EXPECT_EQ(kind, 1);  // prime

    EXPECT_EQ(op_prime_test(12, &kind), STATUS_OK);
    EXPECT_EQ(kind, 2);  // composite
}

TEST(MathOperations, PrimeTest_Invalid) {
    int kind;
    EXPECT_EQ(op_prime_test(1, &kind), STATUS_INVALID_ARGUMENT);
    EXPECT_EQ(op_prime_test(-5, &kind), STATUS_INVALID_ARGUMENT);
    EXPECT_EQ(op_prime_test(7, nullptr), STATUS_INVALID_ARGUMENT);
}

// -------- op_sum_1_to_x --------
TEST(MathOperations, Sum1toX) {
    unsigned long long sum = 0;
    EXPECT_EQ(op_sum_1_to_x(10, &sum), STATUS_OK);
    EXPECT_EQ(sum, 55ULL);
}

TEST(MathOperations, Sum1toX_Invalid) {
    unsigned long long sum;
    EXPECT_EQ(op_sum_1_to_x(0, &sum), STATUS_INVALID_ARGUMENT);
    EXPECT_EQ(op_sum_1_to_x(-5, &sum), STATUS_INVALID_ARGUMENT);
    EXPECT_EQ(op_sum_1_to_x(5, nullptr), STATUS_INVALID_ARGUMENT);
}

// -------- op_factorial --------
TEST(MathOperations, Factorial) {
    unsigned long long fact = 0;
    EXPECT_EQ(op_factorial(5, &fact), STATUS_OK);
    EXPECT_EQ(fact, 120ULL);
}

TEST(MathOperations, Factorial_Zero) {
    unsigned long long fact = 0;
    EXPECT_EQ(op_factorial(0, &fact), STATUS_OK);
    EXPECT_EQ(fact, 1ULL);
}

TEST(MathOperations, Factorial_Invalid) {
    unsigned long long fact;
    EXPECT_EQ(op_factorial(-1, &fact), STATUS_INVALID_ARGUMENT);
    EXPECT_EQ(op_factorial(3, nullptr), STATUS_INVALID_ARGUMENT);
}
