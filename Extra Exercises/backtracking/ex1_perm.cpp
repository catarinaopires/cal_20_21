#include <vector>
#include <set>

using namespace std;

void permREC(vector<int> v, vector<vector<int>> &permV, int i, vector<int> &cur) {

    if (i == v.size() - 1) {
        permV.push_back(cur);
        return;
    }

    for (int j = 0; j < v.size(); j++) {
        swap(cur[i], cur[j]);

        permREC(v, permV, i+1, cur);

        swap(cur[j], cur[i]);
    }
}


vector<vector<int>> perm(vector<int> v) {
    vector<vector<int>> res;

    permREC(v,res,0, v);
    set<vector<int>> s(res.begin(), res.end());
    return vector<vector<int>>(s.begin(), s.end());

}

