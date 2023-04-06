/************************************************************************\
|*      _      _                    _       _                           *|
|*     / \    | | __   __ _   ___  | |__   (_)    LeetCode with C++     *|
|*    / _ \   | |/ /  / _` | / __| | '_ \  | |    data:    2023-4-5     *|
|*   / ___ \  |   <  | (_| | \__ \ | | | | | |    author:  Akashi       *|
|*  /_/   \_\ |_|\_\  \__,_| |___/ |_| |_| |_|    version: 0.0.1        *|
|*                                                                      *|
|*     github:  https://github.com/AkashiNeko/LeetCode-Debugger         *|
|*                                                                      *|
|*                                                                      *|
|*  This is a library for easy input/output and viewing of test cases   *|
|*  when debugging LeetCode problems locally.                           *|
\************************************************************************/

#ifndef _LEETCODE_AKASHI_HPP_
#define _LEETCODE_AKASHI_HPP_

// stream                    
#include <iostream>          // cin cout endl...
#include <fstream>           
#include <iomanip>           

// STL                       
#include <algorithm>         // sort min max...
#include <vector>            // vector...
#include <string>            // string to_string stoi...
#include <queue>             // queue...
#include <stack>             // stack...
#include <unordered_map>     // unordered_map...
#include <unordered_set>     // unordered_set...
#include <map>               // map...
#include <set>               // set...

#include <functional>        // function...
#include <utility>           // pair...
#include <bitset>            // bitset...
#include <tuple>             // tuple...

// C lib
#include <cstdio>            
#include <cstring>           
#include <cstdlib>           
#include <cctype>            
#include <climits>           

namespace LC {

using namespace std;

// LeetCode List
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// LeetCode Binary tree
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/*************************************  vector  ****************************************/

template <class T>
void showVector(vector<T>& vec) {
    if (vec.empty()) {
        cout << "vector<" << typeid(T).name() << ">: []" << endl;
        return;
    }
    auto sz = vec.size();
    if constexpr (is_same_v<T, int> || is_same_v<T, unsigned> 
        || is_same_v<T, float> || is_same_v<T, double>
        || is_same_v<T, long long> || is_same_v<T, unsigned long long>
        || is_same_v<T, char> || is_same_v<T, short>) {
        for (size_t i = 0; i < sz; ++i) {
            cout << vec[i] << ' ';
        }
    }
    else if constexpr (is_same_v<T, bool>) {
        for (size_t i = 0; i < sz; ++i) {
            cout << "[" << i << "]" << (vec[i] ? " True   " : " False  ");
        }
    }
    else if constexpr (is_same_v<T, string>) {
        for (size_t i = 0; i < sz; ++i) {
            cout << "[" << i << "]: \"" << vec[i] << '\"' << endl;
        }
    }
    else if constexpr (is_same_v<T, TreeNode*> || is_same_v<T, ListNode*>) {
        for (size_t i = 0; i < sz; ++i) {
            cout << vec[i]->val << ' ';
        }
    }
    else if constexpr (is_same_v<T, vector<int>> || is_same_v<T, vector<unsigned>>
        || is_same_v<T, vector<float>> || is_same_v<T, vector<double>>
        || is_same_v<T, vector<long long>> || is_same_v<T, vector<unsigned long long>>
        || is_same_v<T, vector<char>> || is_same_v<T, vector<short>>) {
        for (size_t i = 0; i < sz; ++i) {
            cout << "[" << i << "]:";
            if (vec[i].empty()) {
                cout << "[]";
            }
            else {
                for (const auto& e : vec[i]) {
                    cout << setw(4) << e;
                }
            }
            cout << endl;
        }
    }
    else if constexpr (is_same_v<T, vector<bool>>) {
        for (size_t i = 0; i < sz; ++i) {
            cout << "[" << i << "]: ";
            if (vec[i].empty()) {
                cout << "[]";
            }
            else {
                for (const bool& e : vec[i]) {
                    cout << (e ? " T" : " F");
                }
            }
            cout << endl;
        }
    }
    else if constexpr (is_same_v<T, vector<TreeNode*>> || is_same_v<T, vector<ListNode*>>) {
        for (size_t i = 0; i < sz; ++i) {
            cout << "[" << i << "]: ";
            if (vec[i].empty()) {
                cout << "[]";
            } else {
                for (const auto& e : vec[i]) {
                    cout << e->val << ' ';
                }
            }
            cout << endl;
        }
    }
    else {
        cout << "Unknown type: " << typeid(T).name() << endl;
        exit(1);
    }
}

// cout << vector<T>
template <class T>
ostream& operator<<(ostream& cout, vector<T> vec) {
    showVector<T>(vec);
    return cout;
}

}

#endif // _LEETCODE_AKASHI_HPP_