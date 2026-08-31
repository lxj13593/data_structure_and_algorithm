#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stack>
#include <queue>
#include <cmath>

using namespace std;

template <class T, class Compare = less<T>>
class BST_Tree
{
private:
    struct Node
    {
        Node(T data = T()) : data(data),
                             left(nullptr),
                             right(nullptr)
        {
        }

        T data;
        Node *left;
        Node *right;
    };
    Node *root;
    Compare comp;

    void pre_traversal(Node *node)
    {
        if (node != nullptr)
        {
            cout << node->data << " ";
            pre_traversal(node->left);
            pre_traversal(node->right);
        }
    }
    void mid_traversal(Node *node)
    {
        if (node != nullptr)
        {
            mid_traversal(node->left);
            cout << node->data << " ";
            mid_traversal(node->right);
        }
    }
    void post_traversal(Node *node)
    {
        if (node != nullptr)
        {
            post_traversal(node->left);
            post_traversal(node->right);
            cout << node->data << " ";
        }
    }
    int level(Node *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        int left = level(node->left);
        int right = level(node->right);
        return left > right ? left + 1 : right + 1;
    }
    int number(Node *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        int left = number(node->left);
        int right = number(node->right);
        return left + right + 1;
    }
    void level_traversal(Node *node, int i)
    {
        if (node == nullptr)
        {
            return;
        }
        if (i == 0)
        {
            cout << node->data << ' ';
            return;
        }
        level_traversal(node->left, i - 1);
        level_traversal(node->right, i - 1);
    }
    void clear(Node *node)
    {
        if (node == nullptr)
        {
            return;
        }
        clear(node->left);
        clear(node->right);
        delete node;
    }
    Node *insert_(Node *node, const T &val)
    {
        if (node == nullptr)
        {
            return new Node(val);
        }
        if (node->data == val)
        {
            return node;
        }
        else if (comp(node->data, val))
        {
            node->right = insert_(node->right, val);
        }
        else
        {
            node->left = insert_(node->left, val);
        }
        return node;
    }
    Node *query(Node *node, const T &val)
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        if (node->data == val)
        {
            return node;
        }
        else if (comp(node->data, val))
        {
            return query(node->right, val);
        }
        else
        {
            return query(node->left, val);
        }
    }
    Node *delete_(Node *node, const T &val)
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        if (node->data == val)
        {
            if (node->left != nullptr && node->right != nullptr)
            {
                Node *pre = node->left;
                while (pre->right != nullptr)
                {
                    pre = pre->right;
                }
                node->data = pre->data;
                node->left = delete_(node->left, pre->data);
            }
            else
            {
                if (node->left != nullptr)
                {
                    Node *t = node->left;
                    delete node;
                    return t;
                }
                else if (node->right != nullptr)
                {
                    Node *t = node->right;
                    delete node;
                    return t;
                }
                else
                {
                    delete node;
                    return nullptr;
                }
            }
        }
        else if (comp(node->data, val))
        {
            node->right = delete_(node->right, val);
        }
        else
        {
            node->left = delete_(node->left, val);
        }
        return node;
    }
    void search_val(Node *node, vector<int> &v, int i, int j)
    {
        if (node == nullptr)
        {
            return;
        }
        if (node->data > i)
        {
            search_val(node->left, v, i, j);
        }
        if (node->data >= i && node->data <= j)
        {
            v.push_back(node->data);
        }
        if (node->data < j)
        {
            search_val(node->right, v, i, j);
        }
    }
    bool is_BST(Node *node, Node *&pre)
    {
        if (node == nullptr)
        {
            return true;
        }
        if (!is_BST(node->left, pre))
        {
            return false;
        }
        if (pre != nullptr)
        {
            if (!comp(pre->data, node->data))
            {
                return false;
            }
        }
        pre = node;
        return is_BST(node->right, pre);
    }
    bool is_BST_subtree(Node *f, Node *c)
    {
        if (f == nullptr && c == nullptr)
        {
            return true;
        }
        if (f == nullptr)
        {
            return false;
        }
        if (c == nullptr)
        {
            return false;
        }
        if (f->data != c->data)
        {
            return false;
        }
        return is_BST_subtree(f->left, c->left) && is_BST_subtree(f->right, c->right);
    }
    friend void test_2();
    friend void test_4();
    Node *recent_common_ancestor(Node *node, int val1, int val2)
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        if (comp(node->data, val1) && comp(node->data, val2))
        {
            return recent_common_ancestor(node->right, val1, val2);
        }
        else if (comp(val1, node->data) && comp(val2, node->data))
        {
            return recent_common_ancestor(node->left, val1, val2);
        }
        else
        {
            return node;
        }
    }
    void mirror1(Node *node)
    {
        if (node == nullptr)
        {
            return;
        }
        Node *tmp = node->left;
        node->left = node->right;
        node->right = tmp;
        mirror1(node->left);
        mirror1(node->right);
    }
    bool mirror2(Node *node1, Node *node2)
    {
        if (node1 == nullptr && node2 == nullptr)
        {
            return true;
        }
        if (node1 == nullptr)
        {
            return false;
        }
        if (node2 == nullptr)
        {
            return false;
        }
        if (node1->data != node2->data)
        {
            return false;
        }
        return mirror2(node1->left, node2->right) && mirror2(node1->right, node2->left);
    }
    Node *_rebuild(int *pre, int i, int j, int *in, int m, int n)
    {
        if (i > j || m > n)
        {
            return nullptr;
        }
        Node *node = new Node(pre[i]);
        for (int k = m; k <= n; k++)
        {
            if (in[k] == pre[i])
            {
                node->left = _rebuild(pre, i + 1, i + k - m, in, m, k - 1);
                node->right = _rebuild(pre, i + k - m + 1, j, in, k + 1, n);
                return node;
            }
        }
        return node;
    }
    bool isbalance(Node *node)
    {
        if (node == nullptr)
        {
            return true;
        }
        if (!isbalance(node->left))
        {
            return false;
        }
        if (!isbalance(node->right))
        {
            return false;
        }
        int left = level(node->left);
        int right = level(node->right);
        return abs(left - right) <= 1;
    }
    int isbalance_(Node *node,int l,int &flag)
    {
        if(node==nullptr)
        {
            return l;
        }
        int left=isbalance_(node->left,l+1,flag);
        if(!flag)
        {
            return left;
        }
        int right=isbalance_(node->right,l+1,flag);
        if(!flag)
        {
            return right;
        }
        if(abs(left-right)>1)
        {
            flag=false;
        }
        return max(left,right);
    }
    Node* get_last_k_mid(Node *node,int &i,int k)
    {
        if(node==nullptr)
        {
            return nullptr;
        }
        Node *right=get_last_k_mid(node->right,i,k);
        if(right!=nullptr)
        {
            return right;
        }
        i++;
        if(i==k)
        {
            return node;
        }
        return get_last_k_mid(node->left,i,k);
    }
    Node*get_last_k_pre(Node *node,int &i,int k)
    {
        if(node==nullptr)
        {
            return nullptr;
        }
        Node *right=get_last_k_pre(node->right,i,k);
        if(right!=nullptr)
        {
            return right;
        }
        Node *left=get_last_k_pre(node->left,i,k);
        if(left!=nullptr)
        {
            return left;
        }
        i++;
        if(i==k)
        {
            return node;
        }
        return nullptr;
    }
    Node *get_last_k_post(Node *node,int &i,int k)
    {
        if(node==nullptr)
        {
            return nullptr;
        }
        i++;
        if(i==k)
        {
            return node;
        }
        Node *right=get_last_k_post(node->right,i,k);
        if(right!=nullptr)
        {
            return right; 
        }
        return get_last_k_post(node->left,i,k);
    }
public:
    BST_Tree(Compare c=Compare()) : root(nullptr), comp(c)
    {

    }
    // ~BST_Tree()
    // {
    //     clear(root);
    // }
    ~BST_Tree()
    {
        if(root!=nullptr)
        {
            queue<Node*> q;
            q.push(root);
            while(!q.empty())
            {
                Node *front=q.front();
                q.pop();
                if(front->left!=nullptr)
                {
                    q.push(front->left);
                }
                if(front->right!=nullptr)
                {
                    q.push(front->right);
                }
                delete front;
            }
        }
    }
    void n_insert(T val)
    {
        if (root == nullptr)
        {
            root = new Node(val);
            return;
        }

        Node *parent = nullptr;
        Node *cur = root;
        while (cur != nullptr)
        {
            if (comp(val, cur->data))
            {
                parent = cur;
                cur = cur->left;
            }
            else if (comp(cur->data, val))
            {
                parent = cur;
                cur = cur->right;
            }
            else
            {
                return;
            }
        }
        if (comp(parent->data, val))
        {
            parent->right = new Node(val);
        }
        else if (comp(val, parent->data))
        {
            parent->left = new Node(val);
        }
    }
    void n_delete(const T &val)
    {
        Node *parent = nullptr;
        Node *cur = root;
        while (cur != nullptr)
        {
            if (comp(val, cur->data))
            {
                parent = cur;
                cur = cur->left;
            }
            else if (comp(cur->data, val))
            {
                parent = cur;
                cur = cur->right;
            }
            else
            {
                break;
            }
        }
        if (cur == nullptr)
        {
            return;
        }

        if (cur->left != nullptr && cur->right != nullptr)
        {
            parent = cur;
            Node *cur1 = cur->left;
            while (cur1->right != nullptr)
            {
                parent = cur1;
                cur1 = cur1->right;
            }
            cur->data = cur1->data;
            cur = cur1;
        }
        Node *child = cur->left;
        if (child == nullptr)
        {
            child = cur->right;
        }
        if (parent == nullptr)
        {
            root = child;
        }
        else
        {
            if (parent->left == cur)
            {
                parent->left = child;
            }
            else
            {
                parent->right = child;
            }
        }
        delete cur;
    }
    bool n_query(const T &val)
    {
        Node *cur = root;
        while (cur != nullptr)
        {
            if (comp(val, cur->data))
            {
                cur = cur->left;
            }
            else if (comp(cur->data, val))
            {
                cur = cur->right;
            }
            else
            {
                return true;
            }
        }
        return false;
    }
    void pre_traversal()
    {
        pre_traversal(root);
        cout << endl;
    }
    void mid_traversal()
    {
        mid_traversal(root);
        cout << endl;
    }
    void post_traversal()
    {
        post_traversal(root);
        cout << endl;
    }
    int level()
    {
        return level(root);
    }
    int number()
    {
        return number(root);
    }
    void level_traversal()
    {
        cout << "层序遍历：";
        int h = level(root);
        for (int i = 0; i < h; i++)
        {
            level_traversal(root, i);
        }
        cout << endl;
    }
    void insert_(const T &val)
    {
        root = insert_(root, val);
    }
    bool query(const T &val)
    {
        return query(root, val) != nullptr;
    }
    void delete_(const T &val)
    {
        root = delete_(root, val);
    }
    void n_pre_traversal()
    {
        stack<Node *> s;
        if (root == nullptr)
        {
            return;
        }
        s.push(root);
        while (!s.empty())
        {
            Node *t = s.top();
            s.pop();
            cout << t->data << " ";
            if (t->right != nullptr)
            {
                s.push(t->right);
            }
            if (t->left != nullptr)
            {
                s.push(t->left);
            }
        }
        cout << endl;
    }
    void n_mid_traversal()
    {
        stack<Node *> s;
        if (root == nullptr)
        {
            return;
        }
        Node *cur = root;
        while (!s.empty() || cur != nullptr)
        {
            if (cur != nullptr)
            {
                s.push(cur);
                cur = cur->left;
            }
            else
            {
                Node *t = s.top();
                s.pop();
                cout << t->data << " ";
                cur = t->right;
            }
        }
    }
    void n_post_traversal()
    {
        stack<Node *> s;
        stack<Node *> s1;
        if (root == nullptr)
        {
            return;
        }
        s.push(root);
        while (!s.empty())
        {
            Node *t = s.top();
            s1.push(t);
            s.pop();
            if (t->left != nullptr)
            {
                s.push(t->left);
            }
            if (t->right != nullptr)
            {
                s.push(t->right);
            }
        }
        while (!s1.empty())
        {
            cout << s1.top()->data << " ";
            s1.pop();
        }
        cout << endl;
    }
    void n_level_traversal()
    {
        queue<Node *> q;
        if (root == nullptr)
        {
            return;
        }
        Node *cur = root;
        q.push(cur);
        while (!q.empty())
        {
            Node *t = q.front();
            q.pop();
            cout << t->data << " ";
            if (t->left != nullptr)
            {
                q.push(t->left);
            }
            if (t->right != nullptr)
            {
                q.push(t->right);
            }
        }
        cout << endl;
    }
    void search_val(vector<int> &v, int i, int j)
    {
        search_val(root, v, i, j);
    }
    // 判断一棵树是否是二叉搜索树
    bool is_BST()
    {
        Node *pre = nullptr;
        return is_BST(root, pre);
    }
    // 判断一棵树是不是子树
    bool is_BST_subtree(const BST_Tree<T, Compare> &child)
    {
        if (child.root == nullptr)
        {
            return true;
        }
        Node *cur = root;
        while (cur != nullptr)
        {
            if (cur->data == child.root->data)
            {
                break;
            }
            else if (comp(cur->data, child.root->data))
            {
                cur = cur->right;
            }
            else
            {
                cur = cur->left;
            }
        }
        if (cur == nullptr)
        {
            return false;
        }
        return is_BST_subtree(cur, child.root);
    }
    // 求最近公共祖先
    int recent_common_ancestor(int val1, int val2)
    {
        Node *node = recent_common_ancestor(root, val1, val2);
        if (node == nullptr)
        {
            throw "no father";
        }
        return node->data;
    }
    void mirror1()
    {
        mirror1(root);
    }
    bool mirror2()
    {
        if (root == nullptr)
        {
            return true;
        }
        return mirror2(root->left, root->right);
    }
    // 根据前序和中序遍历重建二叉树
    void rebuild(int *pre, int i, int j, int *in, int m, int n)
    {
        root = _rebuild(pre, i, j, in, m, n);
    }
    // 判断二叉树是否是平衡二叉树
    bool isbalance()
    {
        return isbalance(root);
    }
    bool isbalance_()
    {
        int l=0;
        int flag=true;
        isbalance_(root,l,flag);
        return flag;
    }
    // 求中序遍历倒数第K个节点
    int get_last_k_mid(int k)
    {
        int i=0;
        Node *node=get_last_k_mid(root,i,k);
        if(node!=nullptr)
        {
            return node->data;
        }
        else
        {
            throw "fault";
        }
    }
    // 求前序遍历倒数第K个节点
    int get_last_k_pre(int k)
    {
        int i=0;
        Node *node=get_last_k_pre(root,i,k);
        if(node!=nullptr)
        {
            return node->data;
        }
        else
        {
            throw "fault";
        }
    }
    // 求后序遍历倒数第K个节点
    int get_last_k_post(int k)
    {
        int i=0;
        Node *node=get_last_k_post(root,i,k);
        if(node!=nullptr)
        {
            return node->data;
        }
        else
        {
            throw "fault";
        }
    }
};

void test_1()
{
    BST_Tree<int> t;
    vector<int> v{50, 30, 70, 20, 40, 60, 80, 35, 45, 65};
    for (auto val : v)
    {
        t.insert_(val);
    }
    // t.n_delete(45);
    // t.pre_traversal();
    // t.mid_traversal();
    t.post_traversal();
    // cout << t.level() << endl;
    // cout << t.number() << endl;
    t.level_traversal();
    // cout << t.query(30) << endl;
    // t.delete_(50);
    // t.mid_traversal();
    t.n_post_traversal();
    t.n_level_traversal();
    vector<int> v1;
    t.search_val(v1, 10, 60);
    for (int val : v1)
    {
        cout << val << ' ';
    }
    cout << endl;
}

// 测试是否是子树
void test_2()
{
    // 初始树
    using Node = BST_Tree<int>::Node;
    BST_Tree<int> t;
    vector<int> v{50, 30, 70, 20, 40, 60, 80, 35, 45, 65};
    for (auto val : v)
    {
        t.insert_(val);
    }
    // 构建子树
    BST_Tree<int> t1;
    Node *node0 = new Node(70);
    t1.root = node0;
    Node *node1 = new Node(60);
    Node *node2 = new Node(80);
    Node *node3 = new Node(65);
    node0->left = node1;
    node0->right = node2;
    node1->right = node3;

    // 判断
    cout << t.is_BST_subtree(t1) << endl;
}

// 测试公共祖先
void test_3()
{
    BST_Tree<int> t;
    vector<int> v{50, 30, 70, 20, 40, 60, 80, 35, 45, 65};
    for (auto val : v)
    {
        t.insert_(val);
    }
    cout << t.recent_common_ancestor(50, 20) << endl;
}

// 测试
//  mirror1
//  mirror2
void test_4()
{
    // mirror1
    BST_Tree<int> t;
    vector<int> v{50, 30, 70, 20, 40, 60, 80, 35, 45, 65};
    for (auto val : v)
    {
        t.insert_(val);
    }
    t.mid_traversal();
    t.mirror1();
    t.mid_traversal();

    // mirror2
    using Node = BST_Tree<int>::Node;
    BST_Tree<int> t1;
    Node *node0 = new Node(70);
    t1.root = node0;
    Node *node1 = new Node(60);
    Node *node2 = new Node(60);
    Node *node3 = new Node(65);
    Node *node4 = new Node(65);
    Node *node5 = new Node(30);
    Node *node6 = new Node(30);
    node0->left = node1;
    node0->right = node2;
    node1->right = node3;
    node1->left = node5;
    node2->right = node6;
    node2->left = node4;
    cout << t1.mirror2() << endl;
}

// 测试重建二叉树（根据前序和中序遍历）
void test_5()
{
    BST_Tree<int> t;
    int pre[] = {58, 24, 0, 5, 34, 41, 67, 62, 64, 69, 78};
    int in[] = {0, 5, 24, 34, 41, 58, 62, 64, 67, 69, 78};
    t.rebuild(pre, 0, 10, in, 0, 10);
    t.pre_traversal();
    t.mid_traversal();
    t.post_traversal();
}

//测试是否是平衡二叉树
void test_06()
{
    // isbalance()
    BST_Tree<int> t;
    int arr[] = {58, 24, 0, 5, 34, 41, 67, 62, 64, 69, 78};
    for (int val : arr)
    {
        t.insert_(val);
    }
    cout<<t.isbalance()<<endl;
    // t.insert_(12);
    cout<<t.isbalance()<<endl;

    //isbalance_()
    cout<<t.isbalance_()<<endl;
    t.insert_(12);
    cout<<t.isbalance_()<<endl;
}

//测试求前中后序遍历倒数第K个节点
void test_07()
{
    BST_Tree<int> t;
    int arr[] = {58, 24, 0, 5, 34, 41, 67, 62, 64, 69, 78};
    for (int val : arr)
    {
        t.insert_(val);
    }
    t.mid_traversal();
    cout<<t.get_last_k_mid(3)<<endl;
    t.pre_traversal();
    cout<<t.get_last_k_pre(3)<<endl;
    t.post_traversal();
    cout<<t.get_last_k_post(3)<<endl;
}

//自定义比较器
void test_08()
{
    
}

int main()
{
    // test_1();
    // test_2();
    // test_3();
    // test_4();
    // test_5();
    // test_06();
    // test_07();
    test_08();
    return 0;
}