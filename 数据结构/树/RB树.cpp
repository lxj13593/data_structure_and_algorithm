#include <iostream>
#include <queue>

using namespace std;

template <class T>
class RBTree
{
private:
    enum Color
    {
        BLACK,
        RED
    };
    struct Node
    {
        Node(T data = T(), 
            Node *left = nullptr
            , Node *right = nullptr
            , Node *parent = nullptr
            , Color color = BLACK) 
            : data(data)
            , left(left)
            , right(right)
            , parent(parent)
            , color(color)
        {}
        T data;
        Node *left;
        Node *right;
        Node *parent;
        Color color;
    };
    Node *root;
    void set_color(Node *node, Color color)
    {
        if (node != nullptr)
        {
            node->color = color;
        }
    }
    Color color(Node *node)
    {
        return node == nullptr ? BLACK : node->color;
    }
    Node *parent(Node *node)
    {
        return node == nullptr ? nullptr : node->parent;
    }
    Node *left(Node *node)
    {
        return node == nullptr ? nullptr : node->left;
    }
    Node *right(Node *node)
    {
        return node == nullptr ? nullptr : node->right;
    }

public:
    RBTree() : root(nullptr)
    {
    }
    ~RBTree()
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
    void left_rotate(Node *node)
    {
        Node *child = node->right;

        node->right = child->left;
        child->left = node;

        if (node->right != nullptr)
        {
            node->right->parent = node;
        }

        if (node->parent == nullptr)
        {
            root = child;
            child->parent = nullptr;
            node->parent = child;
        }
        else
        {
            if (node->parent->left == node)
            {
                node->parent->left = child;
                child->parent = node->parent;
                node->parent = child;
            }
            else
            {
                node->parent->right = child;
                child->parent = node->parent;
                node->parent = child;
            }
        }
    }
    void right_rotate(Node *node)
    {
        Node* child=node->left;
        node->left=child->right;
        child->right=node;
        if(node->left!=nullptr)
        {
            node->left->parent=node;
        }
        if(node->parent==nullptr)
        {
            root=child;
            child->parent=nullptr;
            node->parent=child;
        }
        else
        {
            if(node->parent->right==node)
            {
                child->parent=node->parent;
                node->parent->right=child;
                node->parent=child;
            }
            else if(node->parent->left==node)
            {
                child->parent=node->parent;
                node->parent->left=child;
                node->parent=child;
            }
        }
    }
    void adjust_rb_tree_insert(Node *node)
    {
        while(color(parent(node))==RED)
        {
            if(left(parent(parent(node)))==parent(node))
            {
                if(color(right(parent(parent(node))))==RED)
                {
                    set_color(parent(node),BLACK);
                    set_color(right(parent(parent(node))),BLACK);
                    set_color(parent(parent(node)),RED);
                    node=parent(parent(node));
                }
                else
                {
                    if(right(parent(node))==node)
                    {
                        node=parent(node);
                        left_rotate(node);
                    }
                    set_color(parent(node),BLACK);
                    set_color(parent(parent(node)),RED);
                    right_rotate(parent(parent(node)));
                    break;
                }
            }
            else
            {
                if(color(left(parent(parent(node))))==RED)
                {
                    set_color(parent(node),BLACK);
                    set_color(left(parent(parent(node))),BLACK);
                    set_color(parent(parent(node)),RED);
                    node=parent(parent(node));
                }
                else
                {
                    if(left(parent(node))==node)
                    {
                        node=parent(node);
                        right_rotate(node);
                    }
                    set_color(parent(node),BLACK);
                    set_color(parent(parent(node)),RED);
                    left_rotate(parent(parent(node)));
                    break;
                }
            }
        }
        set_color(root,BLACK);
    }
    void insert_(const T &val)
    {
        if(root==nullptr)
        {
            root=new Node(val);
            return;
        }
        Node *parent=nullptr;
        Node *cur=root;
        while(cur!=nullptr)
        {
            if(cur->data>val)
            {
                parent=cur;
                cur=cur->left;
            }
            else if(cur->data<val)
            {
                parent=cur;
                cur=cur->right;
            }
            else
            {
                return;
            }
        }
        Node *node=new Node(val,nullptr,nullptr,parent,RED);
        if(parent->data>val)
        {
            parent->left=node;
        }
        else
        {
            parent->right=node;
        }
        if(color(parent)==RED)
        {
            adjust_rb_tree_insert(node);
        }
    }
    void adjust_rb_tree_delete(Node *node)
    {
        if(parent(node)==nullptr)
        {
            set_color(node,BLACK);
            return;
        }

        while(color(node)==BLACK)
        {
            if(left(parent(node))==node)
            {
                Node *brother=right(parent(node));
                if(color(brother)==RED)
                {
                    set_color(parent(node),RED);
                    set_color(right(parent(node)),BLACK);
                    left_rotate(parent(node));
                    brother=right(parent(node));
                }
                if(color(brother)==BLACK)
                {
                    if(color(left(brother))==BLACK&&color(right(brother))==BLACK)
                    {
                        set_color(brother,RED);
                        node=parent(node);
                    }
                    else
                    {
                        if(color(right(brother))==BLACK)
                        {
                            set_color(brother,RED);
                            set_color(left(brother),BLACK);
                            right_rotate(brother);
                            brother=right(parent(node));
                        }
                        set_color(brother,color(parent(node)));
                        set_color(parent(node),BLACK);
                        set_color(right(brother),BLACK);
                        left_rotate(parent(node));
                    }
                }
            }
            else
            {
                Node *brother=left(parent(node));
                if(color(brother)==RED)
                {
                    set_color(parent(node),RED);
                    set_color(left(parent(node)),BLACK);
                    right_rotate(parent(node));
                    brother=left(parent(node));
                }
                if(color(brother)==BLACK)
                {
                    if(color(left(brother))==BLACK&&color(right(brother))==BLACK)
                    {
                        set_color(brother,RED);
                        node=parent(node);
                    }
                    else
                    {
                        if(color(left(brother))==BLACK)
                        {
                            set_color(brother,RED);
                            set_color(right(brother),BLACK);
                            left_rotate(brother);
                            brother=left(parent(node));
                        }
                        set_color(brother,color(parent(node)));
                        set_color(parent(node),BLACK);
                        set_color(left(brother),BLACK);
                        right_rotate(parent(node));
                    }
                }
            }
        }
        set_color(node,BLACK);
    }
    void adjust_rb_tree_delete(Node *node,Node *par)
    {
        if(node==nullptr&&par==nullptr)
        {
            return;
        }
        if(par==nullptr)
        {
            set_color(node,BLACK);
            return;
        }

        while(color(node)==BLACK)
        {
            if(par==nullptr)
            {
                break;
            }
            if(left(par)==node)
            {
                Node *brother=right(par);
                if(color(brother)==RED)
                {
                    set_color(par,RED);
                    set_color(right(par),BLACK);
                    left_rotate(par);
                    brother=right(par);
                }
                if(color(brother)==BLACK)
                {
                    if(color(left(brother))==BLACK&&color(right(brother))==BLACK)
                    {
                        set_color(brother,RED);
                        node=par;
                        par=parent(node);
                    }
                    else
                    {
                        if(color(right(brother))==BLACK)
                        {
                            set_color(brother,RED);
                            set_color(left(brother),BLACK);
                            right_rotate(brother);
                            brother=right(par);
                        }
                        set_color(brother,color(par));
                        set_color(par,BLACK);
                        set_color(right(brother),BLACK);
                        left_rotate(par);
                        break;
                    }
                }
            }
            else
            {
                Node *brother=left(par);
                if(color(brother)==RED)
                {
                    set_color(par,RED);
                    set_color(left(par),BLACK);
                    right_rotate(par);
                    brother=left(par);
                }
                if(color(brother)==BLACK)
                {
                    if(color(left(brother))==BLACK&&color(right(brother))==BLACK)
                    {
                        set_color(brother,RED);
                        node=par;
                        par = parent(node);
                    }
                    else
                    {
                        if(color(left(brother))==BLACK)
                        {
                            set_color(brother,RED);
                            set_color(right(brother),BLACK);
                            left_rotate(brother);
                            brother=left(par);
                        }
                        set_color(brother,color(par));
                        set_color(par,BLACK);
                        set_color(left(brother),BLACK);
                        right_rotate(par);
                        break;
                    }
                }
            }
        }
        set_color(node,BLACK);
    }
    void delete_(const T &val)
    {
        if(root==nullptr)
        {
            return ;
        }
        Node *cur=root;
        while(cur!=nullptr)
        {
            if(cur->data<val)
            {
                cur=cur->right;
            }
            else if(cur->data>val)
            {
                cur=cur->left;
            }
            else
            {
                break;
            }
        }
        if(cur==nullptr)
        {
            return;
        }
        if(cur->left!=nullptr&&cur->right!=nullptr)
        {
            Node *p=cur->left;
            while(p->right!=nullptr)
            {
                p=p->right;
            }
            cur->data=p->data;
            cur=p;
        }
        Node *child=cur->left;
        if(child==nullptr)
        {
            child=cur->right;
        }
        if(child!=nullptr)
        {
            Node *par=cur->parent;
            child->parent=cur->parent;
            if(cur->parent==nullptr)
            {
                root=child;
            }
            else
            {
                if(left(parent(cur))==cur)
                {
                    parent(cur)->left=child;
                }
                else
                {
                    parent(cur)->right=child;
                }
            }
            Color c=color(cur);
            delete cur;
            if(c==BLACK)
            {
                adjust_rb_tree_delete(child,par);
            }
        }
        else
        {
            Node *par=cur->parent;
            if(cur->parent==nullptr)
            {
                root=child;
            }
            else
            {
                if(left(parent(cur))==cur)
                {
                    parent(cur)->left=child;
                }
                else
                {
                    parent(cur)->right=child;
                }
            }
            Color c=color(cur);
            delete cur;
            if(c==BLACK)
            {
                adjust_rb_tree_delete(child,par);
            }
        }
    }
};

int main()
{
    return 0;
}