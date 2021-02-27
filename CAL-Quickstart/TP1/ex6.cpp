// By: Gonçalo Leão

#include "exercises.h"
#include <algorithm>

bool Activity::operator==(const Activity &a2) const {
    return start == a2.start && finish == a2.finish;
}

bool Activity::operator<(const Activity &a2) const {
    return finish < a2.finish;
}

std::vector<Activity> earliestFinishScheduling(std::vector<Activity> A) {
    std::vector<Activity> res;
    Activity lastActivity = A[0];

    std::sort(A.begin(), A.end());

    res.push_back(A[0]);

    for (int i = 1; i < A.size(); i++){
        if (A[i].start >= lastActivity.finish){
            res.push_back(A[i]);
            lastActivity = A[i];
        }
    }

    return res;
}

/// TESTS ///
#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(TP1_Ex6, activityScheduling) {
    std::vector<Activity> A = {{10,20}, {30, 35}, {5, 15}, {10, 40}, {40, 50}};
    std::vector<Activity> V = earliestFinishScheduling(A);
    EXPECT_EQ(V.size(), 3 );
    ASSERT_THAT(V,  ::testing::ElementsAre(Activity(5, 15), Activity(30, 35), Activity(40, 50)));
}
