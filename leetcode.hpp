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


// 从 LeetCode 列表构造一个 T 类型的 vector
//
// ------------------------ Example ------------------------
//
// // 将列表 [1,2,3,4] 转换为 vector<int>
//
// vector<int> vi = buildVector<int>("[1,2,3,4]");
// 
// vector<double> vd = buildVector<double>("[3.14,2.71,1.41,0.5]");
// 
// vector<string> vs = buildVector<string>(R"(["akashi","neko"])");
// 
// vector<char> vc = buildVector<char>(R"(["c","+","+"])");
//
// ---------------------------------------------------------

template <class T>
vector<T> buildVector(string data) {
    string copy;
    for (char& ch : data) {
        if (ch == ' ') continue;
        copy += ch;
    }
    copy.back() = ',';
    size_t sz = copy.size();
    vector<T> result;
    for (int i = 1, j; i < sz; i = j + 1) {
        for (j = i; copy[j] != ','; ++j);
        string sub;
        if (copy[i] == '\"')
            sub = copy.substr(i + 1, j - i - 2);
        else
            sub = copy.substr(i, j - i);
        T value;
        if constexpr (is_same_v<T, int> || is_same_v<T, unsigned>)
            value = stoi(sub);
        else if constexpr (is_same_v<T, long long>)
            value = stoll(sub);
        else if constexpr (is_same_v<T, unsigned long long>)
            value = stoull(sub);
        else if constexpr (is_same_v<T, float>)
            value = stof(sub);
        else if constexpr (is_same_v<T, double>)
            value = stod(sub);
        else if constexpr (is_same_v<T, string>)
            value = sub;
        else if constexpr (is_same_v<T, char>)
            value = sub.back();
        result.push_back(value);
    }
    return result;
}



// 从 LeetCode 列表构造一个 int 类型的 vector
//
// ------------------------ Example ------------------------
//
// // 将列表 [1,2,3,4] 转换为 vector<int>
// 
// auto v = "[1,2,3,4]"_vector_int;
//
// ---------------------------------------------------------

vector<int> operator""_vector_int(const char* arg, size_t n) {
    string s(arg, n);
    return buildVector<int>(s);
}



// 从 LeetCode 列表构造一个 long long 类型的 vector
//
// ------------------------ Example ------------------------
//
// // 将列表 [10000000000,20000000000] 转换为 vector<long long>
//
// auto v = "[10000000000,20000000000]"_vector_long_long;
//
// ---------------------------------------------------------

vector<long long> operator""_vector_long_long(const char* arg, size_t n) {
    string s(arg, n);
    return buildVector<long long>(s);
}



// 从 LeetCode 列表构造一个 float 类型的 vector
//
// ------------------------ Example ------------------------
//
// // 将列表 [3.14,2.71,1.41,0.5] 转换为 vector<float>
//
// auto v = "[3.14,2.71,1.41,0.5]"_vector_float;
//
// ---------------------------------------------------------

vector<float> operator""_vector_float(const char* arg, size_t n) {
    string s(arg, n);
    return buildVector<float>(s);
}



// 从 LeetCode 列表构造一个 double 类型的 vector
//
// ------------------------ Example ------------------------
//
// // 将列表 [3.1415926,2.71828] 转换为 vector<double>
//
// auto v = "[3.1415926,2.71828]"_vector_double;
//
// ---------------------------------------------------------

vector<double> operator""_vector_double(const char* arg, size_t n) {
    string s(arg, n);
    return buildVector<double>(s);
}



// 从 LeetCode 列表构造一个 string 类型的 vector
//
// ------------------------ Example ------------------------
//
// // 字符串中的双引号需要加上反斜杠
// 
// auto v1 = "[\"akashi\",\"neko\"]"_vector_string;
// 
// // v1 的类型为 vector<string>，值为 { "akashi", "neko" }
// 
// // 你也可以使用 R"()" 原始字符串的形式
// 
// auto v2 = R"(["akashi","neko"])"_vector_string;
// 
// ---------------------------------------------------------

vector<string> operator""_vector_string(const char* arg, size_t n) {
    string s(arg, n);
    return buildVector<string>(s);
}



// 从 LeetCode 列表构造一个 char 类型的 vector
// 
// 需要注意：LeetCode 字符列表中的字符，使用的是双引号而非单引号
// 
// 如 ["a","b","c","d"]
//
// ------------------------ Example ------------------------
// 
// // 字符串中的双引号需要加上反斜杠
// 
// auto v1 = "[\"a\",\"b\",\"c\",\"d\"]"_vector_char;
// 
// // v1 的类型为 vector<char>，值为 { 'a', 'b', 'c', 'd' }
// 
// // 你也可以使用 R"()" 原始字符串的形式
// 
// auto v2 = R"(["a","b","c","d"])"_vector_char;
//
// ---------------------------------------------------------

vector<char> operator""_vector_char(const char* arg, size_t n) {
    string s(arg, n);
    return buildVector<char>(s);
}



// 打印一个 vector
// 
// ------------------------ Example ------------------------
//
// vector<int> vi = {1, 2, 3};
// showVector(vi);
//
// vector<string> vs = {"akashi", "neko"};
// showVector(vs);
//
// 输出:
//
// 1 2 3
// [0]: "akashi"
// [1]: "neko"
//
// ---------------------------------------------------------
// 
// 你也可以使用 "cout << vectorObject" 打印 vector

template <class T>
void showVector(vector<T>& vec, bool newLine = true) {
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

    if (newLine)
        cout << endl;
}



// 打印一个 vector
// 
// 如果是一维的 vector, 则输出的内容不会自动换行
// 你需要后面加上 "<< endl"
//
// ------------------------ Example ------------------------
//
// vector<int> vi = {1, 2, 3};
// cout << vi << endl;
//
// vector<string> vs = {"akashi", "neko"};
// cout << vs << endl;
//
// 输出:
//
// 1 2 3
// [0]: "akashi"
// [1]: "neko"
//
// ---------------------------------------------------------
//
// 你也可以使用 "showVector(vectorObject)" 打印 vector

template <class T>
ostream& operator<<(ostream& cout, vector<T> vec) {
    showVector<T>(vec, false);
    return cout;
}



// 将二叉树序列化为 LeetCode 列表
//
// ------------------------ Example ------------------------
//
// TreeNode* root = new TreeNode(1);
// root->left = new TreeNode(2);
// root->right = new TreeNode(3);
// root->right->left = new TreeNode(4);
// root->right0>right = new TreeNode(5);
// 
// // root -> 1
// //        / \
// //       2   3
// //          / \
// //         4   5
// 
// string str = treeToString(root)
// 
// cout << str << endl;
// 
// 输出:
// 
// [1,2,3,null,null,4,5]
//
// ---------------------------------------------------------

string treeToString(TreeNode* root) {
    if (!root)
        return "[]";
    queue<TreeNode*> q;
    q.push(root);
    string ans = "[";
    vector<TreeNode*> seq = {root};
    while (!q.empty()) {
        size_t sz = q.size();
        while (sz--) {
            auto cur = q.front();
            q.pop();
            if (cur->left)
                q.push(cur->left);
            seq.push_back(cur->left);
            if (cur->right)
                q.push(cur->right);
            seq.push_back(cur->right);
        }
    }
    while (!seq.back())
        seq.pop_back();
    for (auto& p : seq) {
        if (p)
            ans += to_string(p->val) + ',';
        else
            ans += "null,";
    }
    ans.back() = ']';
    return ans;
}



// 从 LeetCode 列表构造二叉树
// 
// ------------------------ Example ------------------------
// 
// TreeNode* root = buildTree("[1,2,3,null,null,4,5]");
// 
// // root -> 1
// //        / \
// //       2   3
// //          / \
// //         4   5
//
// ---------------------------------------------------------

TreeNode* buildTree(string data) {
    if (data == "[]") return nullptr;
    size_t sz = data.size();
    data.back() = ',';
    queue<TreeNode*> nodes;
    for (size_t i = 1, j; i < sz; i = j + 1) {
        for (j = i; data[j] != ','; ++j);           
        auto node = data.substr(i, j - i);
        nodes.push(node == "null" ? nullptr : new TreeNode(stoi(node)));
    }
    auto ans = nodes.front();
    queue<TreeNode*> q;
    q.push(nodes.front());
    nodes.pop();
    while (!nodes.empty()) {
        size_t sz = q.size();
        while (sz--) {
            auto cur = q.front();
            q.pop();
            TreeNode* left = nullptr;
            if (!nodes.empty()) {
                left = nodes.front();
                nodes.pop();
                if (left)
                    q.push(left);
            }
            cur->left = left;
            TreeNode* right = nullptr;
            if (!nodes.empty()) {
                right = nodes.front();
                nodes.pop();
                if (right)
                    q.push(right);
            }
            cur->right = right;
        }
    }
    return ans;
}

}

#endif // _LEETCODE_AKASHI_HPP_