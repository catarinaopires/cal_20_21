#include "exercises.h"
#include <algorithm>
bool Activity::operator==(const Activity &a2) const {
    return start == a2.start && finish == a2.finish;
}

bool Activity::overlaps(const Activity &a2) const {
    return (start < a2.finish) && (a2.start < finish);
}

bool validCombination(std::vector<Activity> &res){
    for (int i = 0; i < res.size(); i++){
        for (int j = i + 1; j < res.size(); j++){
            if (res[i].overlaps(res[j]))
                return false;
        }
    }
    return true;
}

void activitySelectionBacktrackingREC(std::vector<Activity>& activities, std::vector<Activity> &cur,
                                      std::vector<Activity> &best, int index) {

    if (index == activities.size()) {
        if (cur.size() > best.size()) {
            best = cur;
        }
        return;
    }

    // Add activity
    cur.push_back(activities[index]);
    if (validCombination(cur)) {
        activitySelectionBacktrackingREC(activities, cur, best, index + 1);
    }

    // Do not add activity
    cur.pop_back();
    activitySelectionBacktrackingREC(activities, cur, best, index + 1);
}


std::vector<Activity> activitySelectionBacktracking(std::vector<Activity> A) {
    std::vector<Activity> res, cur;
    activitySelectionBacktrackingREC(A, cur, res, 0);

    return res;
}



/// TESTS ///
#include <gtest/gtest.h>
#include <gmock/gmock.h>

bool noOverlaps(const std::vector<Activity> &acts) {
    for(unsigned int i = 0; i < acts.size(); i++) {
        Activity A1 = acts.at(i);
        for(unsigned int j = i + 1; j < acts.size(); j++) {
            Activity A2 = acts.at(j);
            if(A1.overlaps(A2)) return false;
        }
    }
    return true;
}

TEST(TP2_Ex4, activityScheduling) {
    std::vector<Activity> A = {{10,20}, {30, 35}, {5, 15}, {10, 40}, {40, 50}};
    std::vector<Activity> V = activitySelectionBacktracking(A);
    EXPECT_EQ(V.size(), 3 );
    EXPECT_EQ(noOverlaps(V), true);
}