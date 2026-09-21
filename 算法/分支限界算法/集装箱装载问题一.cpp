#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <queue>

using namespace std;

// 状态空间树中的节点
struct Node
{
    Node(int weight, int level, Node *parent, bool isleft)
        : weight(weight), level(level), parent(parent), isleft(isleft) {}

    int level;  // 当前处理到第几个物品，下一步要处理 w[level]
    int weight; // 当前节点已经装入船中的总重量

    Node *parent; // 父节点，用于最后回溯选择路径

    bool isleft; // true：当前节点由“选择该物品”得到
                 // false：当前节点由“不选择该物品”得到
};

int bound(int level, vector<int> w)
{
    int s = 0;
    for (int i = level + 1; i < w.size(); i++)
    {
        s += w[i];
    }
    return s;
}

int func(vector<int> w, int c, Node *best)
{
    // 保存所有 new 出来的节点
    // 因为节点之间有 parent 指针，不能中途随便 delete
    // 最后路径回溯完成后统一释放
    vector<Node *> all_node;

    // 使用队列进行广度优先搜索 BFS
    queue<Node *> q;

    int i = 0;  // 当前节点所在层，也就是当前准备处理的物品下标
    int cw = 0; // 当前节点已经装入的重量

    int best_w = 0; // 当前找到的最大装载重量

    // 创建根节点：
    // 当前重量为0
    // level=0，表示下一步处理第0个物品
    // 没有父节点
    Node *root = new Node(0, 0, nullptr, false);

    // 根节点进入队列
    q.push(root);

    // 如果一个物品都装不进去，best至少还能指向根节点
    best = root;

    // 保存根节点，最后统一释放
    all_node.push_back(root);

    // 只要队列里还有没有处理的节点，就继续搜索
    while (!q.empty())
    {
        // 取出队首节点
        Node *front = q.front();
        q.pop();

        // 当前节点的信息
        cw = front->weight;
        i = front->level;

        // 如果 i == w.size()
        // 说明所有物品都已经处理完了
        // 当前节点是叶子节点，不需要再生成左右孩子
        if (i == w.size())
        {
            continue;
        }

        // =========================
        // 左孩子：选择第 i 个物品
        // =========================

        // 如果选择当前物品，新的重量
        int wt = cw + w[i];

        // 只有不超过船的容量，左孩子才合法
        if (wt <= c)
        {
            // 创建左孩子
            // level + 1 表示当前物品已经处理完，
            // 下一层继续处理下一个物品
            Node *p1 = new Node(
                cw + w[i],
                i + 1,
                front,
                true);

            // 保存节点，最后统一释放
            all_node.push_back(p1);

            // 如果当前重量比之前找到的最大重量更大
            // 更新最优重量和最优节点
            if (wt > best_w)
            {
                best_w = wt;
                best = p1;
            }

            // 左孩子入队，等待后续处理
            q.push(p1);
        }

        // =========================
        // 右孩子：不选择第 i 个物品
        // =========================
        int r = bound(i, w);
        if (cw + r >= best_w)
        {
            // 不选当前物品，所以重量不变
            Node *p2 = new Node(
                cw,
                i + 1,
                front,
                false);

            // 保存节点，最后统一释放
            all_node.push_back(p2);

            // 右孩子入队
            q.push(p2);
        }
    }

    // =========================
    // 根据 best 节点回溯选择路径
    // =========================

    // 从最优节点一直沿 parent 往根节点走
    while (best->parent != nullptr)
    {
        // isleft == true
        // 说明从父节点到当前节点时选择了这个物品
        if (best->isleft == 1)
        {
            // level 是从1开始对应物品编号的
            cout << best->level << " ";
        }

        // 回到父节点
        best = best->parent;
    }

    cout << endl;

    // =========================
    // 统一释放所有动态申请的节点
    // =========================
    for (auto val : all_node)
    {
        delete val;
    }

    // 返回最大装载重量
    return best_w;
}

int main()
{
    // 三个物品的重量
    vector<int> w = {12, 8, 15};

    // 船的最大容量
    int c = 27;

    // 保存最优节点
    Node *best = nullptr;

    // 输出：
    // 先输出选择的物品编号
    // 再输出最大装载重量
    cout << func(w, c, best) << endl;

    return 0;
}