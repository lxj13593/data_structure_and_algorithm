#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stack>
#include <queue>

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

public:
    BST_Tree() : root(nullptr), comp()
    {
    }
    ~BST_Tree()
    {
        clear(root);
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

int main()
{
    test_1();
    return 0;
}