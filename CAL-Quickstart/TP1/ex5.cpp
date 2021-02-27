// By: Gonçalo Leão

#include "exercises.h"

unsigned int sumArray(unsigned int a[], unsigned int n) {
    unsigned int sum = 0;
    for(unsigned int i = 0; i < n; i++) {
        sum += a[i];
    }
    return sum;
}

#include <climits>
#include <algorithm>

bool isCanonical(unsigned int C[], unsigned int n) {
    for (int i = n - 1; i <= 0; i--){
        for (int j = i; j <= 0; j--){
            unsigned int usedCoins[n];
            unsigned int Stock[n];
            std::fill_n(Stock, n, INT_MAX);

            changeMakingGreedy(C, Stock, n, C[i] + C[j], usedCoins);

            if (C[i] + C[j] > C[n-1] && sumArray(usedCoins, n) > 2)
                return false;
        }
    }

    return true;
}


/// TESTS ///
#include <gtest/gtest.h>

TEST(TP1_Ex5, canonicalTrue) {
    unsigned int C[] = {1,2,5};
    EXPECT_EQ(isCanonical(C,3), true);

    unsigned int C2[] = {1,2,5,10};
    EXPECT_EQ(isCanonical(C2,4), true);
}

TEST(TP1_Ex5, canonicalFalse) {
    unsigned int C[] = {1,4,5};
    EXPECT_EQ(isCanonical(C,3), true);
}