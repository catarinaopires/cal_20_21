#include "exercises.h"
#include <vector>
using namespace std;

bool changeMakingDP(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    int inf = 999999999;
    vector<vector <unsigned int>> dp(n + 1, vector<unsigned>(T+1, inf));
    vector<vector <unsigned int>> prev(n + 1, vector<unsigned>(T+1, -1));

    dp[0][0] = 0;

    // Reset usedCoins
    fill(usedCoins, usedCoins + n , 0);

    // Go through the coins
    for (int i = 0; i < n ; i++) {
        // Go through the target value
        // Values starts at the value of the coin
        for (int k = 0; k <= T; k++) {

            if (dp[i][k] == inf) {
                continue;
            }

            for (int numCoins = 0; numCoins <= Stock[i]; numCoins++) {
                int newK = k + numCoins * C[i];

                if (newK > T)
                    break;

                if (dp[i][k] + numCoins < dp[i + 1][newK]) {
                    dp[i + 1][newK] = dp[i][k] + numCoins;      // New combination with numCoins of C[i]
                    prev[i + 1][newK] = k;
                }
            }
        }

    }

    if (dp[n][T] == inf)
        return false;

    // Add solution to usedCoins
    for (int i = n; i > 0; i--) {
        int prevT = prev[i][T];

        // We go from state [i-1][prevT] to state [i][T]
        // Same as in graph dijkstra getPath (end to begin)
        usedCoins[i - 1] = (T - prevT) / C[i - 1];
        T = prevT;
    }

    return T == 0;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex3, hasChangeCanonical) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {1,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingDP(C,Stock,n,13,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);

    unsigned int Stock2[] = {1,2,4,2};
    EXPECT_EQ(changeMakingDP(C,Stock2,n,38,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 3);
    EXPECT_EQ(usedCoins[3], 2);

    unsigned int Stock3[] = {10,2,4,2};
    EXPECT_EQ(changeMakingDP(C,Stock3,n,10,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);
}

TEST(TP4_Ex3, hasChangeNonCanonical) {
    unsigned int C[] = {1,4,5};
    unsigned int Stock[] = {2,2,1};
    unsigned int n = 3;
    unsigned int usedCoins[3];

    EXPECT_EQ(changeMakingDP(C,Stock,n,6,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingDP(C,Stock,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);

    unsigned int Stock2[] = {8,2,1};
    EXPECT_EQ(changeMakingDP(C,Stock2,n,7,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 2);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingDP(C,Stock2,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);
}

TEST(TP4_Ex3, hasNoChange) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {0,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingDP(C,Stock,n,18,usedCoins), false);
    EXPECT_EQ(changeMakingDP(C,Stock,n,1,usedCoins), false);
}