#include "exercises.h"

bool sum3(unsigned int T, unsigned int nums[3]) {
    for (int i = 9; i > 0; i--){
        for (int j = 9; j > 0; j--){
            for (int k = 9; k > 0; k--){
                if (i + j + k == T){
                    nums[0] = i; nums[1] =  j; nums[2] = k;
                    return true;
                }
                else {
                    continue;
                }
            }
        }
    }
    return false;
}

bool sum3_a(unsigned int T, unsigned int nums[3]) {

    int l, r;
    for (int i = 1; i <= 9; i++){
        l = i + 1;
        r = 8; // Size_array - 1
        while (l < r) {
            if (i + l + r == T){
                nums[0] = i; nums[1] = l; nums[2] = r;
                return true;
            }
            else if (i + l + r < T){
                l++;
            }
            else{ // i + l + r > T
                r--;
            }
        }
    }
    return false;
}

/// TESTS ///
#include <gtest/gtest.h>

void compareSums(unsigned int selected[3], unsigned int expectedSum) {
    EXPECT_EQ(selected[0] + selected[1] + selected[2], expectedSum);
}

TEST(TP1_Ex1, 3sumExists) {
    unsigned int selected[3];

    unsigned int T = 10;
    EXPECT_EQ(sum3(T,selected), true);
    compareSums(selected,T);

    T = 18;
    EXPECT_EQ(sum3(T,selected), true);
    compareSums(selected,T);
}

TEST(TP1_Ex1, 3sumNotExists) {
    unsigned int selected[3];

    unsigned int T = 1;
    EXPECT_EQ(sum3(T,selected), false);
}