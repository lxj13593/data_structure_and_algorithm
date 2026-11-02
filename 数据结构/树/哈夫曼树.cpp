#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <queue>
#include <map>
#include <unordered_map>

using namespace std;

struct TreeNode
{
    TreeNode(string s, int freqs)
        : freqs(freqs), s(s), left(nullptr), right(nullptr)
    {
    }

    int freqs;
    string s;
    TreeNode *left;
    TreeNode *right;
};

struct Compare
{
    bool operator()(const TreeNode *a, const TreeNode *b) const
    {
        return a->freqs > b->freqs;
    }
};

class HuffmanTree
{
private:
    TreeNode *head;
    unordered_map<string, string> s_code;
    priority_queue<TreeNode *, vector<TreeNode *>, Compare> q;

    void init_small_queue(string s)
    {
        map<string,int> m;
        for(char ch:s)
        {
            string sh(1,ch);
            m[sh]++;
        }
        for (const auto &val : m)
        {
            TreeNode *tnode = new TreeNode(val.first, val.second);
            q.push(tnode);
        }
    }

    void destroy(TreeNode *root)
    {
        if (root == nullptr)
            return;

        destroy(root->left);
        destroy(root->right);
        delete root;
    }

    void save_number(TreeNode *h, string code)
    {
        if (h == nullptr)
        {
            return;
        }
        if (h->left == nullptr && h->right == nullptr)
        {
            s_code[h->s] = code;
        }
        save_number(h->left, code + "0");
        save_number(h->right, code + "1");
    }

public:
    HuffmanTree()
        : head(nullptr)
    {
    }

    ~HuffmanTree()
    {
        destroy(head);
    }

    void build(string s)
    {
        init_small_queue(s);
        while (!q.empty())
        {
            TreeNode *node1 = q.top();
            q.pop();
            if (!q.empty())
            {
                TreeNode *node2 = q.top();
                q.pop();
                int freqs = node1->freqs + node2->freqs;
                TreeNode *f_node = new TreeNode("", freqs);
                f_node->left = node1;
                f_node->right = node2;
                q.push(f_node);
            }
            else
            {
                head = node1;
            }
        }
        save_number(head, "");
    }

    void show_number()
    {
        for (const auto &val : s_code)
        {
            cout << val.first << " " << val.second << endl;
        }
    }

    string encode(string s)
    {
        string result;
        for(char ch:s)
        {
            string sh(1,ch);
            result+=s_code[sh];
        }
        return result;
    }

    string decode(string s)
    {
        TreeNode *p=head;
        string result;
        for(char ch:s)
        {
            if(ch=='0')
            {
                p=p->left;
            }
            else
            {
                p=p->right;
            }
            if(p->left==nullptr&&p->right==nullptr)
            {
                result+=p->s;
                p=head;
            }
        }
        return result;
    }
};

void test_1()
{
    HuffmanTree h_tree;
    string str = "abacabadabacabaeffffeedc";
    h_tree.build(str);
    h_tree.show_number();
    string s=h_tree.encode(str);
    cout<<s<<endl;
    cout<<h_tree.decode(s)<<endl;
}

int main()
{
    test_1();
    return 0;
}
