#include "exercises.h"

bool changeMakingUnlimitedDP(unsigned int C[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    unsigned int minCoins[T + 1];
    unsigned int lastCoin[T + 1];

    minCoins[0] = 0; lastCoin[0] = 0;
    for(int i = 1; i < T + 1; i++) {
        minCoins[i] = 9999;
        lastCoin[i] = 0;
    }

    // Reset usedCoins
    for(int i = 0; i < n; i++) {
        usedCoins[i] = 0;
    }

    // Go through the coins
    for (int i = 0; i < n ; i++) {
        // Go through the target value
        // Values starts at the value of the coin
        for (int k = C[i]; k <= T; k++) {

            if (minCoins[k - C[i]] < minCoins[k]) {
                lastCoin[k] = i;
                minCoins[k] = 1 + minCoins[k - C[i]];       // Add coin
            }
        }

    }

    // Out of boundaries
    if (minCoins[T] >= T + 1)
        return false;

    // Add solution to usedCoins
    for (int k = T; k > 0; k = k - C[lastCoin[k]]) {
        usedCoins[lastCoin[k]]++;
    }

	return true;
}

// T(O) = n*T
// S(n) = n


/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex2, hasChangeCanonical) {
    unsigned int C[] = {1,2,5,10};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,13,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,38,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 1);
    EXPECT_EQ(usedCoins[3], 3);

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,10,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);
}

TEST(TP4_Ex2, hasChangeNonCanonical) {
    unsigned int C[] = {1,4,5};
    unsigned int n = 3;
    unsigned int usedCoins[3];

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,6,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,7,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 2);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);
}

TEST(TP4_Ex2, hasNoChange) {
    unsigned int C[] = {5,10};
    unsigned int n = 2;
    unsigned int usedCoins[2];

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,1,usedCoins), false);
}