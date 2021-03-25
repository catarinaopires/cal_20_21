#include "exercises.h"

std::string calcSum(int sequence[], unsigned long n) {
    std::string res;
    int best, index;

    for (int s = 1; s <= n; s++) {     // size
        best = 0, index = 0;

        for (int i = 0; i < s; i++) {
            best += sequence[i];
        }

        int curr_sum = best;

        for (int i = s; i < n; i++) {
            // Remove old and add new index
            // Sum with the same size(s), starting in another index
            curr_sum += -sequence[i - s] + sequence[i];

            if (curr_sum < best) {
                best = curr_sum;
                index = i - s + 1;
            }
        }

        res += std::to_string(best) + ',' + std::to_string(index) + ';';

    }

    return res;
}

void testPerformanceCalcSum() {
    //TODO
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex4, CalcSumArrayTest) {
    int sequence[5] = {4,7,2,8,1};
    int sequence2[9] = {6,1,10,3,2,6,7,2,4};

    EXPECT_EQ("1,4;9,1;11,2;18,1;22,0;",calcSum(sequence, 5));
    EXPECT_EQ("1,1;5,3;11,3;16,1;20,3;24,3;31,1;35,1;41,0;",calcSum(sequence2, 9));
	
	testPerformanceCalcSum();
}