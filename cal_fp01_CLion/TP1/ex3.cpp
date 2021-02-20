// By: Gonçalo Leão

#include "exercises.h"
#include <set>
using namespace std;

// Brute Force algorithm for the changing making problem:
// Place in vector all possible combinations for the change
// Choose the better combination that satisfies the given amount
// With less number of coins

set<vector<unsigned int>> generateCombinations(vector<unsigned int> stock){
    unsigned currentIndex = 0;
    vector<unsigned int> current(stock.size(), 0);
    set<vector<unsigned int>> results;

    while (current != stock){
        results.insert(current);

        // If there is stock left, add for new combination
        if (current[currentIndex] < stock[currentIndex])
            current[currentIndex]++;
        else{
            // If there is no stock left, find the next value that is not full yet
            while (current[currentIndex] == stock[currentIndex])
                currentIndex++;

            current[currentIndex]++;

            // Reset the other values for new combinations
            while (currentIndex != 0) {
                currentIndex--;
                current[currentIndex] = 0;
            }
        }
    }
    results.insert(current);
    return results;
}

unsigned int totalSum(unsigned int C[], vector<unsigned int> stock){
    unsigned int sum = 0;

    for( int i = 0; i < stock.size(); i++){
        sum += C[i] * stock[i];
    }
    return sum;
}

bool changeMakingBF(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    vector<unsigned int> stock(Stock, Stock + n);
    set<vector<unsigned int>> combinations = generateCombinations(stock);
    vector<unsigned int> result;

    for (auto comb: combinations){
        // If combination of coins satisfies the value check if it is a better solution than the previous ones
        // Better solution: If the combinations gives less coins
        if (totalSum(C, comb) == T){
            if (result.empty() || comb.size() < result.size())
                result = comb;
        }
    }

    if (result.empty()) return false;
    else{
        // Assign the quantities of coins to the solution
        for (int i = 0; i < n; i++) {
            usedCoins[i] = result[i];
        }
        return true;
    }
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP1_Ex3, hasBFChangeCanonical) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {1,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingBF(C,Stock,n,13,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);

    unsigned int Stock2[] = {1,2,4,2};
    EXPECT_EQ(changeMakingBF(C,Stock2,n,38,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 3);
    EXPECT_EQ(usedCoins[3], 2);
}

TEST(TP1_Ex3, hasBFChangeNonCanonical) {
    unsigned int C[] = {1,4,5};
    unsigned int Stock[] = {2,2,1};
    unsigned int n = 3;
    unsigned int usedCoins[3];

    EXPECT_EQ(changeMakingBF(C,Stock,n,6,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingBF(C,Stock,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);
}

TEST(TP1_Ex3, hasNoBFChange) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {0,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingBF(C,Stock,n,18,usedCoins), false);
    EXPECT_EQ(changeMakingBF(C,Stock,n,1,usedCoins), false);
}