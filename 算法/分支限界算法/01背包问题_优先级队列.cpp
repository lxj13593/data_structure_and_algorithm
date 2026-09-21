#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <queue>
#include <functional>

using namespace std;

struct Node
{
    Node(int value, int weight, int level, Node *parent, bool is_left, int bound) : value(value), weight(weight), level(level), parent(parent), is_left(is_left), bound(bound)
    {
    }

    int value;
    int weight;
    int level;
    Node *parent;
    bool is_left;
    int bound;
};

int bound(int level, vector<int> v, int cv)
{
    int s = cv;
    for (int i = level; i < v.size(); i++)
    {
        s += v[i];
    }
    return s;
}

int func(vector<int> w, vector<int> v, int c)
{
    int i = 0;
    int cw = 0;
    int cv = 0;

    int best_v = 0;

    priority_queue<Node *, vector<Node *>, function<bool(Node *, Node *)>> q([](Node *n1, Node *n2) -> bool
                                                                               { return n1->bound < n2->bound; });
    int b = bound(0, v, 0);
    Node *root = new Node(0, 0, 0, nullptr, false, b);
    Node *best = root;
    q.push(root);

    while (!q.empty())
    {
        Node *front = q.top();
        q.pop();
        cw = front->weight;
        cv = front->value;
        i = front->level;
        b = front->bound;

        if (i == w.size())
        {
            continue;
        }

        // 处理左边
        if (cw + w[i] <= c)
        {
            Node *p1 = new Node(cv + v[i], cw + w[i], i + 1, front, true, b);
            if (cv + v[i] > best_v)
            {
                best_v = cv + v[i];
                best = p1;
            }
            q.push(p1);
        }

        b = bound(i + 1, v, cv);
        if (b >= best_v)
        {
            // 处理右边
            Node *p2 = new Node(cv, cw, i + 1, front, false, b);
            q.push(p2);
        }
    }

    while (best->parent != nullptr)
    {
        if (best->is_left == 1)
        {
            cout << best->level << endl;
        }
        best = best->parent;
    }

    return best_v;
}

int main()
{
    vector<int> w = {16, 15, 15};
    vector<int> v = {45, 25, 25};
    int c = 30;
    cout << func(w, v, c) << endl;
    return 0;
}