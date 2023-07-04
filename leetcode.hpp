/************************************************************************\
|*      _      _                    _       _                           *|
|*     / \    | | __   __ _   ___  | |__   (_)    LeetCode with C++     *|
|*    / _ \   | |/ /  / _` | / __| | '_ \  | |    data:    2023-4-5     *|
|*   / ___ \  |   <  | (_| | \__ \ | | | | | |    author:  Akashi       *|
|*  /_/   \_\ |_|\_\  \__,_| |___/ |_| |_| |_|    version: 0.0.2        *|
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

#include <type_traits>      // type_traits

// C lib
#include <cstdio>            
#include <cstring>           
#include <cstdlib>           
#include <cctype>            
#include <climits>           

namespace LC {

using namespace std;

namespace ERR {
    const string BRACKET_MISMATCH = "����������ƥ��";
    const string QUOTE_MISMATCH = "���Ų�ƥ��";
    const string NOT_INTEGER = "��������";
    const string NOT_NUMBER = "��������";
    const string NOT_CHAR = "�����ַ�";
    const string INCORRECT_FORMAT = "��ʽ����ȷ";
    const string UNKNOWN_TYPE = "δ֪������";
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

bool __isNumber_LC__(string num) {
    while (!num.empty() && num.back() == ' ')
        num.pop_back();
    if (num.empty()) return false;
    if (!isdigit(num.back()) && num.back() != '.') return false;
    bool hasE = false, hasDot = false, hasDigit = false;
    size_t sz = num.size(), i = 0;
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

std::vector<int> _range_(int start, int stop, int step = 1) {
    std::vector<int> result;
    for (int i = start; i < stop; i += step) {
        result.push_back(i);
    }
    return result;
}

std::vector<int> _range_(int stop) {
    return _range_(0, stop, 1);
}


/*************************************  vector  ****************************************/


// �� LeetCode �б���һ�� T ���͵� vector
//
// --------------------------------- Example ---------------------------------
//
// // ���б� [1,2,3,4] ת��Ϊ vector<int>
//
// vector<int> vi = build_vector<int>("[1,2,3,4]");
// 
// vector<string> vs = build_vector<string>(R"(["akashi","neko"])");
// 
// vector<char> vc = build_vector<char>(R"(["c","+","+"])");
//
// ---------------------------------------------------------------------------


// get vector values type
template<typename T>
struct VectorTraits { using ValueType = T; };
template<typename T>
struct VectorTraits<std::vector<T>> { using ValueType = T; };


// is_vector
template<typename T>
struct is_vector { constexpr static bool value = false; };
template<typename T>
struct is_vector<std::vector<T>> { constexpr static bool value = true; };


// build vector
template <typename T>
vector<T> build_vector(string data) {
    vector<string> elems = __splitList_LC__(__preproccess_LC__(data));
    if (data == "[]") return {};
    vector<T> result;
    for (const string& elem : elems) {
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
            value = elem.substr(1, elem.size() - 2);
        }
        else if constexpr (is_same_v<T, char>) {
            __assert_LC__(elem.size() == 3, ERR::NOT_CHAR);
            value = elem.at(1);
        }
        else if constexpr (is_vector<T>::value) {
            using type = VectorTraits<T>::template ValueType;
            value = build_vector<type>(elem);
        }
        result.push_back(value);
    }
    return result;
}



// �� LeetCode �б���һ�� int ���͵� vector
//
// --------------------------------- Example ---------------------------------
//
// // ���б� [1,2,3,4] ת��Ϊ vector<int>
// 
// auto v = "[1,2,3,4]"_vector_int;
//
// ---------------------------------------------------------------------------

inline vector<int> operator""_vector_int(const char* arg, size_t n) {
    string s(arg, n);
    return build_vector<int>(s);
}



// �� LeetCode �б���һ�� long long ���͵� vector
//
// --------------------------------- Example ---------------------------------
//
// // ���б� [10000000000,20000000000] ת��Ϊ vector<long long>
//
// auto v = "[10000000000,20000000000]"_vector_long_long;
//
// ---------------------------------------------------------------------------

inline vector<long long> operator""_vector_long_long(const char* arg, size_t n) {
    string s(arg, n);
    return build_vector<long long>(s);
}



// �� LeetCode �б���һ�� float ���͵� vector
//
// --------------------------------- Example ---------------------------------
//
// // ���б� [3.14,2.71,1.41,0.5] ת��Ϊ vector<float>
//
// auto v = "[3.14,2.71,1.41,0.5]"_vector_float;
//
// ---------------------------------------------------------------------------

inline vector<float> operator""_vector_float(const char* arg, size_t n) {
    string s(arg, n);
    return build_vector<float>(s);
}



// �� LeetCode �б���һ�� double ���͵� vector
//
// --------------------------------- Example ---------------------------------
//
// // ���б� [3.1415926,2.71828] ת��Ϊ vector<double>
//
// auto v = "[3.1415926,2.71828]"_vector_double;
//
// ---------------------------------------------------------------------------

inline vector<double> operator""_vector_double(const char* arg, size_t n) {
    string s(arg, n);
    return build_vector<double>(s);
}



// �� LeetCode �б���һ�� string ���͵� vector
//
// --------------------------------- Example ---------------------------------
//
// // �ַ����е�˫������Ҫ���Ϸ�б��
// 
// auto v1 = "[\"akashi\",\"neko\"]"_vector_string;
// 
// // v1 ������Ϊ vector<string>��ֵΪ { "akashi", "neko" }
// 
// // ��Ҳ����ʹ�� R"()" ԭʼ�ַ�������ʽ
// 
// auto v2 = R"(["akashi","neko"])"_vector_string;
// 
// ---------------------------------------------------------------------------

inline vector<string> operator""_vector_string(const char* arg, size_t n) {
    string s(arg, n);
    return build_vector<string>(s);
}



// �� LeetCode �б���һ�� char ���͵� vector
// 
// ��Ҫע�⣺LeetCode �ַ��б��е��ַ���ʹ�õ���˫���Ŷ��ǵ�����
// 
// �� ["a","b","c","d"]
//
// --------------------------------- Example ---------------------------------
// 
// // �ַ����е�˫������Ҫ���Ϸ�б��
// 
// auto v1 = "[\"a\",\"b\",\"c\",\"d\"]"_vector_char;
// 
// // v1 ������Ϊ vector<char>��ֵΪ { 'a', 'b', 'c', 'd' }
// 
// // ��Ҳ����ʹ�� R"()" ԭʼ�ַ�������ʽ
// 
// auto v2 = R"(["a","b","c","d"])"_vector_char;
//
// ---------------------------------------------------------------------------

inline vector<char> operator""_vector_char(const char* arg, size_t n) {
    string s(arg, n);
    return build_vector<char>(s);
}



// ��ӡһ�� vector
// 
// --------------------------------- Example ---------------------------------
//
// vector<int> vi = {1, 2, 3};
// show_vector(vi);
//
// vector<string> vs = {"akashi", "neko"};
// show_vector(vs);
//
// ���:
//
// 1 2 3
// [0]: "akashi"
// [1]: "neko"
//
// ---------------------------------------------------------------------------
// 
// ��Ҳ����ʹ�� "cout << vectorObject" ��ӡ vector

template <class T>
void show_vector(vector<T>& vec, bool newLine = true) {
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



// ��ӡһ�� vector
// 
// �����һά�� vector, ����������ݲ����Զ�����
// ����Ҫ������� "<< endl"
//
// --------------------------------- Example ---------------------------------
//
// vector<int> vi = {1, 2, 3};
// cout << vi << endl;
//
// vector<string> vs = {"akashi", "neko"};
// cout << vs << endl;
//
// ���:
//
// 1 2 3
// [0]: "akashi"
// [1]: "neko"
//
// ---------------------------------------------------------------------------
//
// ��Ҳ����ʹ�� "show_vector(vectorObject)" ��ӡ vector

template <class T>
inline ostream& operator<<(ostream& cout, vector<T> vec) {
    show_vector<T>(vec, false);
    return cout;
}



// �����������л�Ϊ LeetCode �б�
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
// string str = tree2str(root)
// 
// cout << str << endl;
// 
// ���:
// 
// [1,2,3,null,null,4,5]
//
// ---------------------------------------------------------------------------

string tree2str(TreeNode* root) {
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
            if (cur->left) q.push(cur->left);
            seq.push_back(cur->left);
            if (cur->right) q.push(cur->right);
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



// �����������л�Ϊ LeetCode �б����
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
// ���:
// 
// [1,2,3,null,null,4,5]
//
// ---------------------------------------------------------------------------

inline ostream& operator<<(ostream& cout, TreeNode* root) {
    return cout << tree2str(root);
}



// �� LeetCode �б��������
// 
// --------------------------------- Example ---------------------------------
// 
// TreeNode* root = build_tree("[1,2,3,null,null,4,5]");
// 
// // root -> 1
// //        / \
// //       2   3
// //          / \
// //         4   5
//
// ---------------------------------------------------------------------------

TreeNode* build_tree(string data) {
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



// �� LeetCode �б��������
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
    return build_tree(s);
}



/***************************************  queue  ***************************************/

// �鿴һ�������е�����Ԫ��
// 
// ����һ���µĶ��У���Ԫ�����γ��Ӳ���ӡ����Ӱ��ԭ����
//
// --------------------------------- Example ---------------------------------
// 
// queue<int> q({1, 2, 3});
// 
// show_queue(q);
//
// ���:
//
// <- 1 - 2 - 3 <- queue
// 
// ---------------------------------------------------------------------------
// 
// ��Ҳ����ʹ�� "cout << queueObject" �鿴�����е�Ԫ��

template<class T>
void show_queue(queue<T>& q, bool newLine = true) {
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



// �鿴һ�������е�����Ԫ��
// 
// ����һ���µĶ��У���Ԫ�����γ��Ӳ���ӡ����Ӱ��ԭ����
//
// --------------------------------- Example ---------------------------------
// 
// queue<int> q({1, 2, 3});
// 
// cout << q << endl;
//
// ���:
//
// <- 1 - 2 - 3 <- queue
// 
// ---------------------------------------------------------------------------
// 
// ��Ҳ����ʹ�� "show_queue(queueObject)" �鿴�����е�Ԫ��

template <class T>
inline ostream& operator<<(ostream& cout, queue<T> q) {
    show_queue<T>(q, false);
    return cout;
}



/***************************************  stack  ***************************************/

// �鿴һ��ջ�е�����Ԫ��
//
// ����һ���µ�ջ��Ȼ��Ԫ�����γ�ջ����Ӱ��ԭջ
//
// --------------------------------- Example ---------------------------------
//
// stack<int> stk({1, 2, 3});
//
// show_stack(stk);
//
// ���:
//
// | 1 - 2 - 3 <-stack
//
// ---------------------------------------------------------------------------
//
// ��Ҳ����ʹ�� "cout << stackObject" �鿴ջ�е�Ԫ��

template <class T>
void show_stack(stack<T> stk, bool newLine = true) {
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
    cout << " <-stack";
    if (newLine)
        cout << endl;
}



// �鿴һ��ջ�е�����Ԫ��
//
// ����һ���µ�ջ��Ȼ��Ԫ�����γ�ջ����Ӱ��ԭջ
//
// --------------------------------- Example ---------------------------------
//
// stack<int> stk({1, 2, 3});
//
// cout << stk << endl;
//
// ���:
//
// | 1 - 2 - 3 <-stack
//
// ---------------------------------------------------------------------------
//
// ��Ҳ����ʹ�� "show_stack(stackObject)" �鿴ջ�е�Ԫ��

template <class T>
inline ostream& operator<<(ostream& cout, stack<int>& stk) {
    show_stack<T>(stk, false);
    return cout;
}



// �� LeetCode �б���һ����������
//
// --------------------------------- Example ---------------------------------
//
// ListNode* head = build_list("[1,2,3]");
//
// // head --> +---------.  .--> +---------.  .--> +---------.
// //          | val : 1 |  |    | val : 2 |  |    | val : 3 |
// //          | next: -----'    | next: -----'    | next: ----> nullptr
// //          '---------'       '---------'       '---------'
//
// ---------------------------------------------------------------------------

ListNode* build_list(string data) {
    static unordered_set<char> chars = { '[', ']', ',', '-' };
    __assert_LC__(data.front() == '[' && data.back() == ']', "����� LeetCode �б��Ϸ�");
    size_t sz = data.size(), cnt = 0;
    for (size_t i = 0, j = 0; i < sz && j < sz; ++i, ++j) {
        while (j < sz && data[j] == ' ') {
            ++j; ++cnt;
        }
        if (i != j) {
            data[i] = data[j];
        }
        __assert_LC__(__isDigit_LC__(data[i]) || chars.count(data[i]), "�б��к��зǷ��ַ�");
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
        __assert_LC__(j != i, "����� LeetCode �б��Ϸ�, ��������֮��û������");
        int cur = stoi(data.substr(i, j - i));
        p->next = new ListNode(cur);
        p = p->next;
    }
    return headPre.next;
}



// �� LeetCode �б���һ����������
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
    return build_list(string(arg, n));
}


// �鿴һ�� LeetCode �����е�����Ԫ��
//
// --------------------------------- Example ---------------------------------
//
// auto head = "[1,2,3]"_list;
//
// show_list(head);
//
// ���:
//
// 1 -> 2 -> 3 -> null
//
// ---------------------------------------------------------------------------
//
// ��Ҳ����ʹ�� "cout << headPointer" �鿴ջ�е�Ԫ��

void show_list(ListNode* ls, bool newLine = true) {
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



// �鿴һ�� LeetCode �����е�����Ԫ��
//
// --------------------------------- Example ---------------------------------
//
// auto head = "[1,2,3]"_list;
//
// cout << head << endl;
//
// ���:
//
// 1 -> 2 -> 3 -> null
//
// ---------------------------------------------------------------------------
//
// ��Ҳ����ʹ�� "show_list(headPointer)" �鿴ջ�е�Ԫ��

ostream& operator<<(ostream& cout, ListNode* head) {
    show_list(head, false);
    return cout;
}



} // namespace LC

#endif // _LEETCODE_AKASHI_HPP_