#include "exercises.h"
#include <numeric>
using namespace std;

int findIndexCoins(unsigned int C[], unsigned n, int value){
    for (unsigned i = 0; i < n; i++ ){
        if (value == C[i])
            return i;
    }
    return -1;
}

bool changeMakingBacktrackingREC(vector<int> coins, int index, int T, unsigned int curCoins[], unsigned int bestCoins[], unsigned int C[], unsigned n) {

    if (T == 0) {

        if (accumulate(curCoins, curCoins + n, 0) < accumulate(bestCoins, bestCoins + n, 0)) {
            for (int i = 0; i < n; i++) {
                bestCoins[i] = curCoins[i];
            }
        }
        return true;
    }

    if (index < 0 || T < 0)
        return false;

    curCoins[findIndexCoins(C, n, coins[index])] += 1;

    // Allow for the 2 options to run
    bool withCoin = false, withoutCoin = false;

    // Add coin
    withCoin = changeMakingBacktrackingREC(coins, index - 1, T - coins[index], curCoins, bestCoins, C, n);

    curCoins[findIndexCoins(C, n, coins[index])] -= 1;

    // Do not add coin
    withoutCoin = changeMakingBacktrackingREC(coins, index - 1, T, curCoins, bestCoins, C, n);

    return withCoin || withoutCoin;
}

bool changeMakingBacktracking(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    unsigned int curCoins[n];
    for (int i = 0; i < n; i++){
        usedCoins[i] = 9999999;
        curCoins[i] = 0;
    }

    std::vector<int> coins;
    for (int i= 0; i < n; i++){
        for(int j = 0; j < Stock[i]; j++){
            coins.push_back(C[i]);
        }
    }

    return changeMakingBacktrackingREC(coins,coins.size() - 1, T, curCoins, usedCoins, C, n);
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP2_Ex3, hasBFChangeCanonical) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {1,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingBacktracking(C,Stock,n,13,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);

    unsigned int Stock2[] = {1,2,4,2};
    EXPECT_EQ(changeMakingBacktracking(C,Stock2,n,38,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 3);
    EXPECT_EQ(usedCoins[3], 2);

    unsigned int Stock3[] = {10,2,4,2};
    EXPECT_EQ(changeMakingBacktracking(C,Stock3,n,10,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);
}

TEST(TP2_Ex3, hasBFChangeNonCanonical) {
    unsigned int C[] = {1,4,5};
    unsigned int Stock[] = {2,2,1};
    unsigned int n = 3;
    unsigned int usedCoins[3];

    EXPECT_EQ(changeMakingBacktracking(C,Stock,n,6,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingBacktracking(C,Stock,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);

    unsigned int Stock2[] = {8,2,1};
    EXPECT_EQ(changeMakingBacktracking(C,Stock2,n,7,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 2);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingBacktracking(C,Stock2,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);
}

TEST(TP2_Ex3, hasNoBFChange) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {0,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingBacktracking(C,Stock,n,18,usedCoins), false);
    EXPECT_EQ(changeMakingBacktracking(C,Stock,n,1,usedCoins), false);
}