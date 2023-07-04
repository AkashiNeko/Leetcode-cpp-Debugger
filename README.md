# LeetCode Debugger

##### 力扣题目C++调试库

使用C++17标准，编译时请加上选项 `-std=c++17` 。

本项目处于测试阶段，可能会有一些bug，如果发现了请及时向我反馈。

## 1. vector - 顺序表

#### 1.1 构造vector

##### (1) `build_vector<T>`

构造一个vector。参数data为力扣测试用例列表，如 `"[1,2,3,4]"`。

需要构造何种类型的vector，只需将类型写在 `build_` 之后，如 `build_vector<vector<int>>` 即构造一个二维的vector。

~~~cpp
vector<T> build_vector(string data);
~~~

示例

~~~cpp
vector<int> vec1 = build_vector<int>("[1,2,3,4]");
// 高维vector同理
auto vec2 = build_vector<vector<int>>("[[1,2],[3,4],[5]]");
~~~

##### (2) `""_vector..`（不推荐）

~~~cpp
vector<int> operator""_vector_int(const char* arg, size_t n);
vector<long long> operator""_vector_long_long(const char* arg, size_t n);
vector<float> operator""_vector_float(const char* arg, size_t n);
vector<double> operator""_vector_double(const char* arg, size_t n);
vector<string> operator""_vector_string(const char* arg, size_t n);
vector<char> operator""_vector_char(const char* arg, size_t n);
~~~

示例

~~~cpp
auto vi = "[1,2,3,4]"_vector_int;
auto vl = "[1,2]"_vector_long_long;
auto vf = "[3.14,2.71,1.41,0.5]"_vector_float;
auto vd = "[3.1415926,2.71828]"_vector_double;
auto vs = R"(["akashi","neko"])"_vector_string;
auto vc = R"(["a","b","c","d"])"_vector_char;
~~~

#### 1.2 查看vector

##### (1) `show_vector<T>`

查看一个vector中的所有元素。参数vec为要查看的vector，参数newLine表示打印后是否换行，默认为换行。

~~~cpp
void show_vector(vector<T>& vec, bool newLine = true);
~~~

示例

~~~cpp
vector<int> vi = {1, 2, 3};
show_vector(vi);
vector<string> vs = {"akashi", "neko"};
show_vector(vs);
~~~

输出

~~~
1 2 3
[0]: "akashi"
[1]: "neko"
~~~

##### (2) `cout <<` 输出

~~~cpp
ostream& operator<<(ostream& cout, vector<T> vec);
~~~

示例

~~~cpp
vector<int> vec = {1, 2, 3};
cout << vec << endl;
~~~

输出

~~~
1 2 3
~~~



## 2. tree - 二叉树

❗ 注意：此处的tree为力扣定义的二叉树。力扣二叉树定义如下

~~~cpp
// LeetCode Binary tree
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
~~~

#### 2.1 构造tree（反序列化）

##### (1) `build_tree`

力扣使用带 `null` 的**层序遍历**序列化二叉树，同时删去层序遍历结果末尾的所有 `null` 。比如序列`"[1,2,3,null,null,4,5]"`表示的二叉树如下图所示。

![二叉树](images/tree.svg)

从力扣列表反序列化二叉树。参数data为力扣测试用例列表。

~~~cpp
TreeNode* build_tree(string data);
~~~

##### (2) `""_tree`

~~~cpp
TreeNode* operator""_tree(const char* arg, size_t n);
~~~

示例

~~~cpp
TreeNode* root = "[1,2,3,null,null,4,5]"_tree;
~~~


#### 2.2 序列化tree

##### (1) `tree2str`

将二叉树序列化为Leetcode字符串。参数root为二叉树的根节点。

~~~cpp
string tree2str(TreeNode* root);
~~~

示例

~~~cpp
auto root = "[1,2,3,null,null,4,5]"_tree;
string str = tree2str(root)
cout << str << endl;
~~~

输出

~~~cpp
[1,2,3,null,null,4,5]
~~~

#### 2.3 查看二叉树

##### (1) `cout << ` 输出

~~~cpp
ostream& operator<<(ostream& cout, TreeNode* root);
~~~

示例

~~~cpp
auto root = "[1,2,3,null,null,4,5]"_tree;
cout << root << endl;
~~~

输出

~~~cpp
[1,2,3,null,null,4,5]
~~~



## 3. queue - 队列

#### 3.1 查看队列

##### (1) `show_queue`

查看一个队列中的所有元素。参数q为要查看的队列，参数newLine表示打印后是否换行，默认为换行。

~~~cpp
void show_queue(queue<T>& q, bool newLine = true);
~~~

示例

~~~cpp
queue<int> q({1, 2, 3});
show_queue(q);
~~~

输出

~~~
<- 1 - 2 - 3 <- queue
~~~

##### (2) `cout <<` 输出

~~~cpp
ostream& operator<<(ostream& cout, queue<T> q);
~~~

示例

~~~cpp
queue<int> q({1, 2, 3});
cout << q << endl;
~~~

输出

~~~
<- 1 - 2 - 3 <- queue
~~~



## 4. stack - 栈

#### 4.1 查看队列

##### (1) `show_stack`

查看一个栈中的所有元素。其中参数stk为要查看的栈，参数newLine表示打印后是否换行，默认为换行。

~~~cpp
void show_stack(stack<T> stk, bool newLine = true);
~~~

示例

~~~cpp
stack<int> stk({1, 2, 3});
show_stack(stk);
~~~

输出

~~~
| 1 - 2 - 3 <-stack
~~~

##### (2) `cout <<` 输出

~~~cpp
ostream& operator<<(ostream& cout, stack<int>& stk);
~~~

示例

~~~cpp
stack<int> stk({1, 2, 3}); 
cout << stk << endl;
~~~

输出

~~~
| 1 - 2 - 3 <-stack
~~~



## 5. list - 链表

❗ 注意：此处的list为力扣定义的链表，而非STL链表！力扣链表定义如下

~~~cpp
// LeetCode List
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
~~~

#### 5.1 构造list

##### (1) `build_list`

构造一个list。参数data为力扣测试用例列表，如 `"[1,2,3,4]"`。

~~~cpp
ListNode* build_list(string data)
~~~

示例

~~~cpp
ListNode* head = build_list("[1,2,3]");
~~~

##### (2) `""_list`

~~~cpp
ListNode* operator""_list(const char* arg, size_t n);
~~~

示例

~~~cpp
ListNode* head = "[1,2,3]"_list;
~~~

#### 5.2 查看list

##### (1) `show_list`

查看一个list中的所有元素。参数head为list的头节点，参数newLine表示打印后是否换行，默认为换行。

~~~cpp
void show_list(ListNode* ls, bool newLine = true);
~~~

示例

~~~cpp
auto head = "[1,2,3]"_list;
show_list(head);
~~~

输出

~~~
1 -> 2 -> 3 -> null
~~~

##### (2) `cout <<` 输出

~~~cpp
ostream& operator<<(ostream& cout, ListNode* head);
~~~

示例

~~~cpp
auto head = "[1,2,3]"_list;
cout << head << endl;
~~~

输出

~~~
1 -> 2 -> 3 -> null
~~~

