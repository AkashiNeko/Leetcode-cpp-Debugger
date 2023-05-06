#include "leetcode.hpp"
using namespace LC;

int main() {
    auto vec = build_vector<int>("[1,2,3]");
    buildTree(vec);
    cout << vec << endl;
    return 0;
}