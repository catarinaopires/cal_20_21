#include <vector>
#include <string>
#include <set>
using namespace std;

void permutationsUlREC(string s, int index, vector<string>& total) {

    if (index >= s.length()) {
        total.push_back(s);
        return ;
    }

    // Uppercase curr letter
    s[index] = toupper(s[index]);
    permutationsUlREC(s, index + 1, total);

    // Lowercase curr letter
    s[index] = tolower(s[index]);
    permutationsUlREC(s, index + 1, total);

}

vector<string> permutationsUl(string s) {
    vector<string> total;
    permutationsUlREC(s, 0, total);

    set<string> t(total.begin(), total.end());
    total = vector<string>(t.begin(), t.end());

    return total;
}
