#include <gtest/gtest.h>
#include <climits>

extern "C" {
    #include "prime_at_n.h"
}

// ---------- compute_limit ----------
TEST(PrimeAtN, ComputeLimit_SmallN) {
    uint64_t out = 0;
    EXPECT_EQ(compute_limit(5, &out), STATUS_OK);
    EXPECT_EQ(out, 12ULL); // для n < 6
}

TEST(PrimeAtN, ComputeLimit_Normal) {
    uint64_t out = 0;
    EXPECT_EQ(compute_limit(10, &out), STATUS_OK);
    EXPECT_GT(out, 0ULL);
}

TEST(PrimeAtN, ComputeLimit_InvalidArgs) {
    uint64_t out;
    EXPECT_EQ(compute_limit(0, &out), STATUS_INVALID_ARGUMENT);
    EXPECT_EQ(compute_limit(1, &out), STATUS_INVALID_ARGUMENT);
    EXPECT_EQ(compute_limit(10, nullptr), STATUS_INVALID_ARGUMENT);
}

// ---------- prime_with_eratosphen ----------
TEST(PrimeAtN, Eratosphen_Basic) {
    uint64_t out = 0;
    EXPECT_EQ(prime_with_eratosphen(5, 50, &out), STATUS_OK);
    EXPECT_EQ(out, 11ULL);
}

TEST(PrimeAtN, Eratosphen_RangeError) {
    uint64_t out = 0;
    EXPECT_EQ(prime_with_eratosphen(20, 10, &out), STATUS_RANGE_ERROR);
}

TEST(PrimeAtN, Eratosphen_MemoryErrorCheck) {
    uint64_t out = 0;
    EXPECT_EQ(prime_with_eratosphen(1, 10, &out), STATUS_OK);
    EXPECT_EQ(out, 2ULL);
}

// ---------- find_prime_number_by_number ----------
TEST(PrimeAtN, FindPrime_Normal) {
    uint64_t out = 0;
    EXPECT_EQ(find_prime_number_by_number(1, &out), STATUS_OK);
    EXPECT_EQ(out, 2ULL);

    EXPECT_EQ(find_prime_number_by_number(5, &out), STATUS_OK);
    EXPECT_EQ(out, 11ULL);
}

TEST(PrimeAtN, FindPrime_InvalidArgs) {
    uint64_t out = 0;
    EXPECT_EQ(find_prime_number_by_number(0, &out), STATUS_INVALID_ARGUMENT);
    EXPECT_EQ(find_prime_number_by_number(10, nullptr), STATUS_INVALID_ARGUMENT);
}

TEST(PrimeAtN, FindPrime_Bigger) {
    uint64_t out = 0;
    // 10-е простое = 29
    EXPECT_EQ(find_prime_number_by_number(10, &out), STATUS_OK);
    EXPECT_EQ(out, 29ULL);
}
