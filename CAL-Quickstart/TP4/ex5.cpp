#include "exercises.h"
#include <numeric>

unsigned long s_recursive(unsigned int n, unsigned int k) {
    if (k > 1 && k < n)
        return s_recursive(n-1, k-1) + k * s_recursive(n-1, k);
    if (k == 1 || k == n)
        return 1;

}

unsigned long b_recursive(unsigned int n) {
    unsigned long b = 0;

    for (int k = 1; k <= n; k++) {
        b += s_recursive(n , k);
    }
    return b;
}

unsigned long s_dynamic(unsigned int n, unsigned int k) {
    unsigned long values[n-k+1];

    for (int j = 0; j < n - k + 1; j++) {
        values[j] = 1;
    }

    for (int i = 2; i <= k; i++) {              // k
        for (int j = 1; j < n - k + 1; j++) {
            values[j] += i * values[j - 1];
        }
    }
    return values[n-k];
}

unsigned long b_dynamic(unsigned int n) {
    unsigned long values[n+1];

    for (int i = 1; i <= n; i++) {
        values[i] = 1;
        for (int k = i-1; k > 1; k--) {
            values[k] = values[k-1] + k * values[k];
        }
    }

    return std::accumulate(values + 1, values + n + 1, 0);
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex5, testPartitioningRecursive) {
    EXPECT_EQ(1,s_recursive(3,3));
    EXPECT_EQ(3025,s_recursive(9,3));
    EXPECT_EQ(22827,s_recursive(10,6));

    EXPECT_EQ(5,b_recursive(3));
    EXPECT_EQ(203,b_recursive(6));
    EXPECT_EQ(1382958545,b_recursive(15));
}

TEST(TP4_Ex5, testPartitioningDynamic) {
    EXPECT_EQ(1,s_dynamic(3,3));
    EXPECT_EQ(3025,s_dynamic(9,3));
    EXPECT_EQ(22827,s_dynamic(10,6));

    EXPECT_EQ(5,b_dynamic(3));
    EXPECT_EQ(203,b_dynamic(6));
    EXPECT_EQ(1382958545,b_dynamic(15));
}