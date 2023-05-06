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

namespace ERR {
    const string BRACKET_MISMATCH = "括号数量不匹配";
    const string QUOTE_MISMATCH = "引号不匹配";
    const string NOT_INTEGER = "不是整数";
    const string NOT_NUMBER = "不是数字";
    const string NOT_CHAR = "不是数字";
    const string INCORRECT_FORMAT = "格式不正确";
    const string UNKNOWN_TYPE = "未知的类型";
}

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

/***************************************************************************************/

const struct Error {
    ostream& operator<<(const string& errInfo) const {
        return cerr << "ERROR: " << errInfo << endl;
    }
}LC_Error;

inline void __assert_LC__(bool assert, const string& errInfo) {
    if (!assert) {
        LC_Error << errInfo;
        exit(1);
    }
}

inline bool __isDigit_LC__(char ch) {
    switch (ch) {
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    case '-': return true;
    default: return false;
    }
}

inline bool __isDigit_LC__(const string& num) {
    for (const char& ch : num) {
        if (!__isDigit_LC__(ch))
            return false;
    }
    return true;
}

inline vector<string> __splitList_LC__(string str) {
    size_t i = 0, j = 0, sz = str.size(), stk = 0;
    str.front() = ',';
    str.back() = ',';
    vector<string> ans;
    while (i < sz - 1) {
        size_t stk = 0;
        for (j = i + 1; j < sz && (str[j] != ',' || stk > 0); ++j) {
            if (str[j] == '[')
                ++stk;
            else if (str[j] == ']')
                --stk;
        }
        ans.push_back(str.substr(i + 1, j - i - 1));
        i = j;
    }
    return ans;
}

inline string __preproccess_LC__(const string& str) {
    __assert_LC__(str.front() == '[' && str.back() == ']', ERR::INCORRECT_FORMAT);
    string ans;
    bool inQuote = false;
    size_t stk = 0, sz = str.size();
    for (size_t i = 0; i < sz; ++i) {
        if (str[i] == '\"')
            inQuote = !inQuote;
        if (!inQuote) {
            switch (str[i]) {
            case ' ': continue;
            case '[': ++stk; break;
            case ']':
                __assert_LC__(stk > 0, ERR::BRACKET_MISMATCH);
                --stk; break;
            case ',':
                __assert_LC__(stk > 0, ERR::INCORRECT_FORMAT);
                break;
            default: break;
            }
        }
        ans += str[i];
    }
    __assert_LC__(!inQuote, ERR::QUOTE_MISMATCH);
    __assert_LC__(stk == 0, ERR::BRACKET_MISMATCH);
    return ans;
}

bool __isNumber_LC__(string& num) {
    while (!num.empty() && num.back() == ' ')
        num.pop_back();
    if (num.empty()) return false;
    if (!isdigit(num.back()) && num.back() != '.') return false;
    bool hasE = false, hasDot = false, hasDigit = false;
    int sz = num.size(), i = 0;
    while (num[i] == ' ') ++i;
    if (num[i] == '+' || num[i] == '-') ++i;
    while (i < sz) {
        switch (num[i]) {
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            hasDigit = true;
            break;
        case '+': case '-':
            if (i && num[i - 1] != 'e')
                return false;
            break;
        case 'e': case 'E':
            if (!hasDigit || hasE)
                return false;
            num[i] = 'e';
            hasE = true;
            break;
        case '.':
            if (hasE || hasDot)
                return false;
            hasDot = true;
            break;
        default:
            return false;
        }
        ++i;
    }
    if (!hasDigit) return false;
    return true;
}

/*************************************  vector  ****************************************/


// 从 LeetCode 列表构造一个 T 类型的 vector
//
// --------------------------------- Example ---------------------------------
//
// // 将列表 [1,2,3,4] 转换为 vector<int>
//
// vector<int> vi = build_vector<int>("[1,2,3,4]");
// 
// vector<string> vs = build_vector<string>(R"(["akashi","neko"])");
// 
// vector<char> vc = build_vector<char>(R"(["c","+","+"])");
//
// ---------------------------------------------------------------------------

template <class T>
vector<T> build_vector(string data) {
    vector<string> elems = __splitList_LC__(__preproccess_LC__(data));
    vector<T> result;
    for (string& elem : elems) {
        T value;
        if constexpr (is_same_v<T, int> || is_same_v<T, unsigned>) {
            __assert_LC__(__isDigit_LC__(elem), ERR::NOT_NUMBER);
            value = stoi(elem);
        }
        else if constexpr (is_same_v<T, long long>) {
            __assert_LC__(__isDigit_LC__(elem), ERR::NOT_NUMBER);
            value = stoll(elem);
        }
        else if constexpr (is_same_v<T, unsigned long long>) {
            __assert_LC__(__isDigit_LC__(elem), ERR::NOT_NUMBER);
            value = stoull(elem);
        }
        else if constexpr (is_same_v<T, float>) {
            __assert_LC__(__isNumber_LC__(elem), ERR::NOT_INTEGER);
            value = stof(elem);
        }
        else if constexpr (is_same_v<T, double>) {
            __assert_LC__(__isNumber_LC__(elem), ERR::NOT_INTEGER);
            value = stod(elem);
        }
        else if constexpr (is_same_v<T, string>) {
            value = elem;
        }
        else if constexpr (is_same_v<T, char>) {
            __assert_LC__(elem.size() == 1, ERR::NOT_CHAR);
            value = elem.back();
        }
        else if constexpr (is_same_v<T, vector<int>> || is_same_v<T, vector<unsigned>>) {
            value = build_vector<int>(elem);
        }
        else if constexpr (is_same_v<T, vector<long long>>) {
            value = build_vector<long long>(elem);
        }
        else if constexpr (is_same_v<T, vector<unsigned long long>>) {
            value = build_vector<unsigned long long>(elem);
        }
        else if constexpr (is_same_v<T, vector<float>>) {
            value = build_vector<float>(elem);
        }
        else if constexpr (is_same_v<T, vector<double>>) {
            value = build_vector<double>(elem);
        }
        else if constexpr (is_same_v<T, vector<string>>) {
            value = build_vector<double>(string);
        }
        else if constexpr (is_same_v<T, vector<char>>) {
            value = build_vector<char>(elem);
        }
        else if constexpr (is_same_v<T, vector<vector<char>>>) {
            value = build_vector<vector<char>>(elem);
        }
        result.push_back(value);
    }
    return result;
}



// 从 LeetCode 列表构造一个 int 类型的 vector
//
// --------------------------------- Example ---------------------------------
//
// // 将列表 [1,2,3,4] 转换为 vector<int>
// 
// auto v = "[1,2,3,4]"_vector_int;
//
// ---------------------------------------------------------------------------

inline vector<int> operator""_vector_int(const char* arg, size_t n) {
    string s(arg, n);
    return build_vector<int>(s);
}



// 从 LeetCode 列表构造一个 long long 类型的 vector
//
// --------------------------------- Example ---------------------------------
//
// // 将列表 [10000000000,20000000000] 转换为 vector<long long>
//
// auto v = "[10000000000,20000000000]"_vector_long_long;
//
// ---------------------------------------------------------------------------

inline vector<long long> operator""_vector_long_long(const char* arg, size_t n) {
    string s(arg, n);
    return build_vector<long long>(s);
}



// 从 LeetCode 列表构造一个 float 类型的 vector
//
// --------------------------------- Example ---------------------------------
//
// // 将列表 [3.14,2.71,1.41,0.5] 转换为 vector<float>
//
// auto v = "[3.14,2.71,1.41,0.5]"_vector_float;
//
// ---------------------------------------------------------------------------

inline vector<float> operator""_vector_float(const char* arg, size_t n) {
    string s(arg, n);
    return build_vector<float>(s);
}



// 从 LeetCode 列表构造一个 double 类型的 vector
//
// --------------------------------- Example ---------------------------------
//
// // 将列表 [3.1415926,2.71828] 转换为 vector<double>
//
// auto v = "[3.1415926,2.71828]"_vector_double;
//
// ---------------------------------------------------------------------------

inline vector<double> operator""_vector_double(const char* arg, size_t n) {
    string s(arg, n);
    return build_vector<double>(s);
}



// 从 LeetCode 列表构造一个 string 类型的 vector
//
// --------------------------------- Example ---------------------------------
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
// ---------------------------------------------------------------------------

inline vector<string> operator""_vector_string(const char* arg, size_t n) {
    string s(arg, n);
    return build_vector<string>(s);
}



// 从 LeetCode 列表构造一个 char 类型的 vector
// 
// 需要注意：LeetCode 字符列表中的字符，使用的是双引号而非单引号
// 
// 如 ["a","b","c","d"]
//
// --------------------------------- Example ---------------------------------
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
// ---------------------------------------------------------------------------

inline vector<char> operator""_vector_char(const char* arg, size_t n) {
    string s(arg, n);
    return build_vector<char>(s);
}



// 打印一个 vector
// 
// --------------------------------- Example ---------------------------------
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
// ---------------------------------------------------------------------------
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
        for (size_t i = 0; i < sz; ++i)
            cout << vec[i] << ' ';
    }
    else if constexpr (is_same_v<T, bool>) {
        for (size_t i = 0; i < sz; ++i)
            cout << "[" << i << "]" << (vec[i] ? " True   " : " False  ");
    }
    else if constexpr (is_same_v<T, string>) {
        for (size_t i = 0; i < sz; ++i)
            cout << "[" << i << "]: " << vec[i] << endl;
    }
    else if constexpr (is_same_v<T, TreeNode*> || is_same_v<T, ListNode*>) {
        for (size_t i = 0; i < sz; ++i)
            cout << vec[i]->val << ' ';
    }
    else if constexpr (is_same_v<T, vector<int>> || is_same_v<T, vector<unsigned>>
        || is_same_v<T, vector<float>> || is_same_v<T, vector<double>>
        || is_same_v<T, vector<long long>> || is_same_v<T, vector<unsigned long long>>
        || is_same_v<T, vector<char>> || is_same_v<T, vector<short>>) {
        for (size_t i = 0; i < sz; ++i) {
            cout << "[" << i << "]: ";
            if (vec[i].empty())
                cout << "[]";
            else
                for (const auto& e : vec[i])
                    cout << e << ' ';
            cout << endl;
        }
    }
    else if constexpr (is_same_v<T, vector<bool>>) {
        for (size_t i = 0; i < sz; ++i) {
            cout << "[" << i << "]: ";
            if (vec[i].empty())
                cout << "[]";
            else
                for (const bool& e : vec[i])
                    cout << (e ? " T" : " F");
            cout << endl;
        }
    }
    else if constexpr (is_same_v<T, vector<TreeNode*>> || is_same_v<T, vector<ListNode*>>) {
        for (size_t i = 0; i < sz; ++i) {
            cout << "[" << i << "]: ";
            if (vec[i].empty())
                cout << "[]";
            else
                for (const auto& e : vec[i])
                    cout << e->val << ' ';
            cout << endl;
        }
    }
    else {
        LC_Error << ERR::UNKNOWN_TYPE << typeid(T).name();
    }

    if (newLine)
        cout << endl;
}



// 打印一个 vector
// 
// 如果是一维的 vector, 则输出的内容不会自动换行
// 你需要后面加上 "<< endl"
//
// --------------------------------- Example ---------------------------------
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
// ---------------------------------------------------------------------------
//
// 你也可以使用 "showVector(vectorObject)" 打印 vector

template <class T>
inline ostream& operator<<(ostream& cout, vector<T> vec) {
    showVector<T>(vec, false);
    return cout;
}



// 将二叉树序列化为 LeetCode 列表
//
// --------------------------------- Example ---------------------------------
//
// TreeNode* root = "[1,2,3,null,null,4,5]"_tree;
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
// ---------------------------------------------------------------------------

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

// 将二叉树序列化为 LeetCode 列表输出
//
// --------------------------------- Example ---------------------------------
//
// TreeNode* root = "[1,2,3,null,null,4,5]"_tree;
// 
// // root -> 1
// //        / \
// //       2   3
// //          / \
// //         4   5
// 
// cout << root << endl;
// 
// 输出:
// 
// [1,2,3,null,null,4,5]
//
// ---------------------------------------------------------------------------

inline ostream& operator<<(ostream& cout, TreeNode* root) {
    return cout << treeToString(root);
}



// 从 LeetCode 列表构造二叉树
// 
// --------------------------------- Example ---------------------------------
// 
// TreeNode* root = buildTree("[1,2,3,null,null,4,5]");
// 
// // root -> 1
// //        / \
// //       2   3
// //          / \
// //         4   5
//
// ---------------------------------------------------------------------------

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



// 从 LeetCode 列表构造二叉树
// 
// --------------------------------- Example ---------------------------------
// 
// TreeNode* root = "[1,2,3,null,null,4,5]"_tree;
// 
// // root -> 1
// //        / \
// //       2   3
// //          / \
// //         4   5
//
// ---------------------------------------------------------------------------

inline TreeNode* operator""_tree(const char* arg, size_t n) {
    string s(arg, n);
    return buildTree(s);
}



/***************************************  queue  ***************************************/

// 查看一个队列中的所有元素
// 
// 复制一个新的队列，将元素依次出队并打印，不影响原队列
//
// --------------------------------- Example ---------------------------------
// 
// queue<int> q({1, 2, 3});
// 
// showQueue(q);
//
// 输出:
//
// <- 1 - 2 - 3 <- queue
// 
// ---------------------------------------------------------------------------
// 
// 你也可以使用 "cout << queueObject" 查看队列中的元素

template<class T>
void showQueue(queue<T>& q, bool newLine = true) {
    if (q.empty()) {
        cout << "queue<" << typeid(T).name() << ">: []" << endl;
        return;
    }
    queue<T> tmp(q);
    cout << '<';
    while (!tmp.empty()) {
        T& cur = tmp.front();
        if constexpr (is_same_v<T, TreeNode*> || is_same_v<T, ListNode*>) { 
            cout << "- " << cur->val << ' ';
        }
        else {
            cout << "- " << cur << ' ';
        }
        tmp.pop();
    }
    cout << "<- queue";
    if (newLine)
        cout << endl;
}



// 查看一个队列中的所有元素
// 
// 复制一个新的队列，将元素依次出队并打印，不影响原队列
//
// --------------------------------- Example ---------------------------------
// 
// queue<int> q({1, 2, 3});
// 
// cout << q << endl;
//
// 输出:
//
// <- 1 - 2 - 3 <- queue
// 
// ---------------------------------------------------------------------------
// 
// 你也可以使用 "showQueue(queueObject)" 查看队列中的元素

template <class T>
inline ostream& operator<<(ostream& cout, queue<T> q) {
    showQueue<T>(q, false);
    return cout;
}



/***************************************  stack  ***************************************/

// 查看一个栈中的所有元素
//
// 复制一个新的栈，然后将元素依次出栈，不影响原栈
//
// --------------------------------- Example ---------------------------------
//
// stack<int> stk({1, 2, 3});
//
// showStack(stk);
//
// 输出:
//
// | 1 - 2 - 3 <<- stack
//
// ---------------------------------------------------------------------------
//
// 你也可以使用 "cout << stackObject" 查看栈中的元素

template <class T>
void showStack(stack<T> stk, bool newLine = true) {
    if (stk.empty()) {
        cout << "stack<" << typeid(T).name() << ">: []" << endl;
        return;
    }
    stack<T> tmp(stk);
    vector<T> v;
    while (!tmp.empty()) {
        v.push_back(tmp.top());
        tmp.pop();
    }
    reverse(v.begin(), v.end());
    cout << "| ";
    if constexpr (is_same_v<T, TreeNode*> || is_same_v<T, ListNode*>) {
        cout << v.front()->val;
    }
    else {
        cout << v.front();
    }
    for (size_t i = 1, sz = v.size(); i < sz; ++i) {
        if constexpr (is_same_v<T, TreeNode*> || is_same_v<T, ListNode*>) {
            cout << " - " << v[i]->val;
        }
        else {
            cout << " - " << v[i];
        }
    }
    cout << " <<- stack";
    if (newLine)
        cout << endl;
}



// 查看一个栈中的所有元素
//
// 复制一个新的栈，然后将元素依次出栈，不影响原栈
//
// --------------------------------- Example ---------------------------------
//
// stack<int> stk({1, 2, 3});
//
// cout << stk << endl;
//
// 输出:
//
// | 1 - 2 - 3 <<- stack
//
// ---------------------------------------------------------------------------
//
// 你也可以使用 "showStack(stackObject)" 查看栈中的元素

template <class T>
inline ostream& operator<<(ostream& cout, stack<int>& stk) {
    showStack<T>(stk, false);
    return cout;
}



// 从 LeetCode 列表构造一个力扣链表
//
// --------------------------------- Example ---------------------------------
//
// ListNode* head = buildList("[1,2,3]");
//
// // head --> +---------.  .--> +---------.  .--> +---------.
// //          | val : 1 |  |    | val : 2 |  |    | val : 3 |
// //          | next: -----'    | next: -----'    | next: ----> nullptr
// //          '---------'       '---------'       '---------'
//
// ---------------------------------------------------------------------------

ListNode* buildList(string data) {
    static unordered_set<char> chars = { '[', ']', ',', '-' };
    __assert_LC__(data.front() == '[' && data.back() == ']', "输入的 LeetCode 列表不合法");
    size_t sz = data.size(), cnt = 0;
    for (size_t i = 0, j = 0; i < sz && j < sz; ++i, ++j) {
        while (j < sz && data[j] == ' ') {
            ++j; ++cnt;
        }
        if (i != j) {
            data[i] = data[j];
        }
        __assert_LC__(__isDigit_LC__(data[i]) || chars.count(data[i]), "列表中含有非法字符");
    }
    sz -= cnt;
    data.resize(sz);
    if (data.empty() || data == "[]") {
        return nullptr;
    }
    data.back() = ',';
    ListNode headPre;
    ListNode* p = &headPre;
    for (size_t i = 1, j; i < sz; i = j + 1) {
        for (j = i; data[j] != ','; ++j);
        __assert_LC__(j != i, "输入的 LeetCode 列表不合法, 两个逗号之间没有内容");
        int cur = stoi(data.substr(i, j - i));
        p->next = new ListNode(cur);
        p = p->next;
    }
    return headPre.next;
}



// 从 LeetCode 列表构造一个力扣链表
//
// --------------------------------- Example ---------------------------------
//
// ListNode* head = "[1,2,3]"_list;
//
// // head --> +---------.  .--> +---------.  .--> +---------.
// //          | val : 1 |  |    | val : 2 |  |    | val : 3 |
// //          | next: -----'    | next: -----'    | next: ----> nullptr
// //          '---------'       '---------'       '---------'
//
// ---------------------------------------------------------------------------

inline ListNode* operator""_list(const char* arg, size_t n) {
    return buildList(string(arg, n));
}


// 查看一个 LeetCode 链表中的所有元素
//
// --------------------------------- Example ---------------------------------
//
// auto head = "[1,2,3]"_list;
//
// showList(head);
//
// 输出:
//
// 1 -> 2 -> 3 -> null
//
// ---------------------------------------------------------------------------
//
// 你也可以使用 "cout << headPointer" 查看栈中的元素

void showList(ListNode* ls, bool newLine = true) {
    if (!ls) {
        cout << "list: []";
    }
    else {
        while (ls) {
            cout << ls->val << " -> ";
            ls = ls->next;
        }
        cout << "null";
    }
    if (newLine)
        cout << endl;
}



// 查看一个 LeetCode 链表中的所有元素
//
// --------------------------------- Example ---------------------------------
//
// auto head = "[1,2,3]"_list;
//
// cout << head << endl;
//
// 输出:
//
// 1 -> 2 -> 3 -> null
//
// ---------------------------------------------------------------------------
//
// 你也可以使用 "showList(headPointer)" 查看栈中的元素

ostream& operator<<(ostream& cout, ListNode* head) {
    showList(head, false);
    return cout;
}

}

#endif // _LEETCODE_AKASHI_HPP_