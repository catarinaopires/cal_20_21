#include <iostream>
#include <vector>
#include <numeric>
#include <string>
#include <set>
#include "exercises.h"

using namespace std;

// This is correct but takes its time
/*void generateRec(int n, string cur, vector<string> &res) {
    if (n == 0) {
        res.push_back(cur);
        return;
    }

    for (int i = 0; i <= cur.size(); i++) {

        // Add
        string temp = cur.substr(0, i);
        temp += "()" + cur.substr(i, cur.size());

        generateRec(n - 1, temp, res);
    }
}


vector<string> generateParenthesis(int n) {
    if (n == 0)
        return {""};

    else if (n == 1)
        return {"()"};

    vector<string> res;
    generateRec(n - 1, "()", res);

    set<string> t(res.begin(), res.end());
    res = vector<string>(t.begin(), t.end());

    return res;

}*/

// Better solution
void generateRec(int n, string cur, vector<string> &res, int open, int close, int max) {
    if (n == 0) {
        res.push_back(cur);
        return;
    }

    if(open < max) generateRec(n-1, cur+"(", res, open+1, close, max);
    if(close < open) generateRec(n-1, cur+")", res, open, close+1, max);
}


vector<string> generateParenthesis(int n) {

    vector<string> res;
    generateRec(n *2, "", res, 0,0, n);

    return res;
}


void balancing(int sum, vector<int> masses, int i, vector<int>& curr, bool& withOption){
    /*if (sum < 0) {
        return;
    }*/

    if (sum == 0) {
        withOption = true;
        for (int j = 0; j < curr.size(); j++) {
            cout << curr[j];
            if (j != curr.size() - 1)
                cout << " + ";
        }
        cout << endl;
        return;
    }

    for (int j = i; j < masses.size(); j++) {

        if (sum - masses[j] < 0)
            continue;

        if (j != i && masses[j] == masses[j - 1])
            continue;

        curr.push_back(masses[j]);

        balancing(sum - masses[j], masses, j+1, curr, withOption);

        curr.pop_back();

    }

}


int main() {
/*    vector<string> v = permutationsUl("0");
    cout << "[";
    for (int i= 0; i < v.size(); i++) {
        cout << v[i] ;

        if (i != v.size() - 1)
            cout << " , ";
    }
    cout << "]\n";
    return 0;*/

    /*vector<vector<int>> v = perm({1, 2, 3});
    for (int i = 0; i < v.size(); i++) {
        cout << "[";
        for (int j= 0; j < v[i].size(); j++) {
            cout << v[i][j] << ", ";

        }
        cout << "]\n";
    }*/

    /*vector<string> v = generateParenthesis(3);
    cout << "[";
    for (int i= 0; i < v.size(); i++) {
        cout << v[i] ;

        if (i != v.size() - 1)
            cout << " , ";
    }
    cout << "]\n";
    return 0;*/

    int M = 7, n = 8;

    vector<int> masses = {6, 5, 3, 2, 2, 1, 1, 1, 1};

    vector<int> temp;
    bool withOptions = false;
    cout << "Weights for " << M << ":" << endl;
    balancing(M, masses, 0, temp, withOptions);

    if (!withOptions) {
        cout << "No solutions";
    }
    /*set<vector<int>> s(res.begin(), res.end());
    res = vector<vector<int>>(s.begin(), s.end());*/



    /*if (res.empty()) {
        cout << "No solutions";
    }
    else {
        for (int i = 0; i < res.size(); i++) {
            for (int j = 0; j < res[i].size(); j++) {
                if (j == res[i].size() - 1)
                    cout << res[i][j];
                else {
                    cout << res[i][j] << " + ";
                }

            }
            cout << endl;
        }
    }*/

}
