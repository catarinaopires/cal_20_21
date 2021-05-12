#include "exercises.h"

#include <vector>
#include <fstream>

std::vector<int> compute_prefix(std::string pattern) {

    int m = pattern.length();
    std::vector<int> pi(m);
    pi[0] = 0;
    int k = 0;

    for (int q = 1; q < m; q++) {
        while(k > 0 && pattern[k] != pattern[q])
            k = pi[k-1];

        if (pattern[k] == pattern[q])
            k++;

        pi[q] = k;
    }
    return pi;
}

int kmpMatcher(std::string text, std::string pattern) {
    int n = text.length();
    int m = pattern.length();
    std::vector<int> pi = compute_prefix(pattern);
    int q = 0;

    int total = 0;
    for (int i = 0; i < n; i++) {

        while (q > 0 && pattern[q] != text[i])
            q = pi[q-1];

        if (pattern[q] == text[i])
            q++;
        if (q == m) {
            total++;
            q = pi[q-1];
        }
    }
    return total;
}

int numStringMatching(std::string filename, std::string toSearch) {
    std::ifstream ifs(filename);
    if (!ifs.is_open()) return 0;
    std::string line;
    int total = 0;
    while(getline(ifs, line)) {
        total += kmpMatcher(line, toSearch);
    }

    ifs.close();
    return total;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP10_Ex1, testKmpMatcher) {
    EXPECT_EQ(3, kmpMatcher("aaabaabaacaabaa", "aabaa"));

    EXPECT_EQ(0, kmpMatcher("", "a"));
    EXPECT_EQ(1, kmpMatcher("a", "a"));
}

#define REL_PATH std::string("../TP10/") // relative path to the tests

TEST(TP10_Ex1, testNumStringMatching) {
    int num1 = numStringMatching(REL_PATH + "text1.txt", "estrutura de dados");
    EXPECT_EQ(3, num1);

    int num2=numStringMatching(REL_PATH +"text2.txt", "estrutura de dados");
    EXPECT_EQ(2,num2);
}