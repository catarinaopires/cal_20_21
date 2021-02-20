// By: Gonçalo Leão

#include "exercises.h"

#include <algorithm>
#include <vector>

double minimumAverageCompletionTime(std::vector<unsigned int> tasks, std::vector<unsigned int> &orderedTasks) {
    unsigned int currentTime = 0;
    double averageTime = 0.0;
    std::sort(tasks.begin(), tasks.end());

    for (int i = 0; i < tasks.size(); i++){
        orderedTasks.push_back(tasks[i]);
        currentTime += tasks[i];
        averageTime += currentTime;
    }
    averageTime = (double) averageTime / tasks.size();
    return averageTime;
}

/// TESTS ///
#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(TP1_Ex7, taskOrdering) {
    std::vector<unsigned int> tasks = {15, 8, 3, 10};
    std::vector<unsigned int> orderedTasks;
    double averageTime = minimumAverageCompletionTime(tasks, orderedTasks);
    EXPECT_EQ(orderedTasks.size(), 4 );
    ASSERT_NEAR(averageTime, 17.75, 0.00001);
    ASSERT_THAT(orderedTasks,  ::testing::ElementsAre(3,8,10,15));
}