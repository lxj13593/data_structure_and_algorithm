#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

template <class T>
class AVL_Tree
{
private:
    struct Node
    {
        Node(T t = T()) : data(t), left(nullptr), right(nullptr), height(1)
        {
        }
        T data;
        Node *left;
        Node *right;
        int height;
    };
    Node *root;
    int height(Node *node)
    {
        return node == nullptr ? 0 : node->height;
    }
    Node *right_rotate(Node *node)
    {
        Node *child = node->left;
        node->left = child->right;
        child->right = node;
        node->height = max(height(node->left), height(node->right)) + 1;
        child->height = max(height(child->left), height(child->right)) + 1;
        return child;
    }
    Node *left_rotate(Node *node)
    {
        Node *child = node->right;
        node->right = child->left;
        child->left = node;
        node->height = max(height(node->left), height(node->right)) + 1;
        child->height = max(height(child->left), height(child->right)) + 1;
        return child;
    }
    Node *left_balance(Node *node)
    {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }
    Node *right_balance(Node *node)
    {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }
    Node *insert_(Node *node, const T &val)
    {
        if (node == nullptr)
        {
            return new Node(val);
        }
        if (node->data > val)
        {
            node->left = insert_(node->left, val);
        }
        else if (node->data < val)
        {
            node->right = insert_(node->right, val);
        }
        else
        {
            return node;
        }
        if (height(node->left) - height(node->right) > 1)
        {
            if (height(node->left->left) >= height(node->left->right))
            {
                node = right_rotate(node);
            }
            else
            {
                node = left_balance(node);
            }
        }
        else if (height(node->right) - height(node->left) > 1)
        {
            if (height(node->right->right) >= height(node->right->left))
            {
                node = left_rotate(node);
            }
            else
            {
                node = right_balance(node);
            }
        }
        node->height = max(height(node->left), height(node->right)) + 1;
        return node;
    }
    Node *delete_(Node *node, const T &val)
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        if (node->data < val)
        {
            node->right = delete_(node->right, val);
        }
        else if (node->data > val)
        {
            node->left = delete_(node->left, val);
        }
        else
        {
            Node *p = node;
            if (node->left != nullptr && node->right != nullptr)
            {
                p = node->left;
                while (p->right != nullptr)
                {
                    p = p->right;
                }
                node->data = p->data;
                node->left = delete_(node->left, p->data);
            }
            else
            {
                Node *child = node->left;
                if (child == nullptr)
                {
                    child = node->right;
                }
                delete node;
                return child;
            }
        }
        if (height(node->left) - height(node->right) > 1)
        {
            if (height(node->left->left) >= height(node->left->right))
            {
                node = right_rotate(node);
            }
            else
            {
                node = left_balance(node);
            }
        }
        else if (height(node->right) - height(node->left) > 1)
        {
            if (height(node->right->right) >= height(node->right->left))
            {
                node = left_rotate(node);
            }
            else
            {
                node = right_balance(node);
            }
        }
        node->height = max(height(node->left), height(node->right)) + 1;
        return node;
    }

public:
    AVL_Tree() : root(nullptr)
    {
    }
    ~AVL_Tree()
    {
        if (root != nullptr)
        {
            queue<Node *> q;
            q.push(root);
            while (!q.empty())
            {
                Node *front = q.front();
                q.pop();
                if (front->left != nullptr)
                {
                    q.push(front->left);
                }
                if (front->right != nullptr)
                {
                    q.push(front->right);
                }
                delete front;
            }
        }
    }
    void insert_(const T &val)
    {
        root = insert_(root, val);
    }
    void delete_(const T &val)
    {
        root = delete_(root, val);
    }
};

void test_1()
{
    AVL_Tree<int> at;
    int arr[] = {30, 20, 10, 40, 50, 25, 27, 5, 4};
    for (int val : arr)
    {
        at.insert_(val);
    }
}

int main()
{
    test_1();
    return 0;
}