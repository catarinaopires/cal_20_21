#ifndef BACKTRACKING_EXERCISES_H
#define BACKTRACKING_EXERCISES_H

using namespace std;
// Exercise 1
vector<vector<int>> perm(vector<int> v);
void permREC(vector<int> v, vector<vector<int>> &permV, int i, vector<int> &cur);


// Exercise 3
vector<string> permutationsUl(string s);
void permutationsUlREC(string s, int index, vector<string>& total);


#endif //BACKTRACKING_EXERCISES_H
