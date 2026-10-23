#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <map>
#include <stack>

using namespace std;

class TrieTree
{
private:
    struct TrieNode
    {
        TrieNode(char data, int freq) : data(data), freq(freq) {}
        char data;
        int freq;
        map<char, TrieNode *> node_map;
    };

private:
    TrieNode *root;

    void pre_order(TrieNode *node, string word, vector<string> &wordlist)
    {
        if (node != root)
        {
            word.push_back(node->data);
        }

        if (node->freq > 0)
        {
            wordlist.push_back(word);
        }
        for (const auto &val : node->node_map)
        {
            pre_order(val.second, word, wordlist);
        }
    }
    void clear(TrieNode *node)
    {
        for (auto val : node->node_map)
        {
            clear(val.second);
        }
        delete node;
    }

public:
    TrieTree()
    {
        root = new TrieNode('\0', 0);
    }
    ~TrieTree()
    {
        clear(root);
    }
    // 添加单词
    void add(const string &s)
    {
        TrieNode *p = root;
        int i = 0;
        while (!p->node_map.empty() && i < s.size())
        {
            auto it = p->node_map.find(s[i]);
            if (it != p->node_map.end())
            {
                p = it->second;
                i++;
            }
            else
            {
                break;
            }
        }
        if (i == s.size())
        {
            p->freq++;
        }
        else
        {
            for (int j = i; j < s.size(); j++)
            {
                TrieNode *node = new TrieNode(s[j], 0);
                p->node_map[s[j]] = node;
                p = node;
            }
            p->freq = 1;
        }
    }
    // 查询单词
    bool query(const string &s)
    {
        TrieNode *p = root;
        for (int i = 0; i < s.size(); i++)
        {
            auto it = p->node_map.find(s[i]);
            if (it != p->node_map.end())
            {
                p = it->second;
            }
            else
            {
                return 0;
            }
        }
        if (p->freq > 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    void pre_order(TrieNode *node = nullptr, string s = "")
    {
        if (node == nullptr)
        {
            node = root;
        }
        string word;
        word += s;
        vector<string> wordlist;
        pre_order(node, word, wordlist);
        for (auto val : wordlist)
        {
            cout << val << endl;
        }
    }
    void prefix_search(const string &s)
    {
        TrieNode *p = root;
        int i = 0;
        while (i < s.size())
        {
            auto it = p->node_map.find(s[i]);
            if (it != p->node_map.end())
            {
                p = it->second;
                i++;
            }
            else
            {
                break;
            }
        }
        if (i == s.size())
        {
            pre_order(p, s.substr(0, s.size() - 1));
        }
    }
    void delete_(const string &s)
    {
        TrieNode *p = root;
        int i = 0;
        stack<pair<char, TrieNode *>> v;
        v.push(pair<char, TrieNode *>('\0', p));
        while (i < s.size())
        {
            auto it = p->node_map.find(s[i]);
            if (it != p->node_map.end())
            {
                p = it->second;
                i++;
                v.push(pair<char, TrieNode *>(s[i - 1], p));
            }
            else
            {
                break;
            }
        }
        char erase_ch = '\0';
        if (i == s.size())
        {
            if (p->freq ==0)
            {
                return;
            }
            p->freq--;
            if (p->node_map.empty())
            {
                while (!v.empty())
                {
                    TrieNode *l = v.top().second;
                    if (l->freq > 0 || l->node_map.size() > 1 || l->data == '\0')
                    {
                        break;
                    }
                    else
                    {
                        erase_ch = v.top().first;
                        delete l;
                        v.pop();
                    }
                }
                if (erase_ch != '\0')
                {
                    TrieNode *k = v.top().second;
                    k->node_map.erase(erase_ch);
                }
            }
        }
    }
};

void test_1()
{
    TrieTree tree;
    vector<string> words = {
        "pool",
        "prize",
        "preview",
        "prepare",
        "produce",
        "progress",
        "pri",
    };

    for (const auto &word : words)
    {
        tree.add(word);
    }
    // tree.pre_order();
    // tree.prefix_search("pr");
    tree.delete_("pri");
    cout << tree.query("pri") << endl;
    tree.pre_order();
}

int main()
{
    test_1();
    return 0;
}