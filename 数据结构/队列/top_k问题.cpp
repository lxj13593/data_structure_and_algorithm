#include <iostream>      // 标准输入输出流
#include <vector>        // 动态数组 vector
#include <algorithm>     // 通用算法
#include <numeric>       // 数值计算工具
#include <queue>         // 优先级队列 priority_queue
#include <map>           // 有序映射 map
#include <set>           // 有序集合 set
#include <unordered_map> // 哈希映射，用于统计元素出现次数
#include <functional>    // greater 和 function 函数对象
using namespace std;

// 从数组中找出最小的 K 个元素。
// 使用大根堆保存当前最小的 K 个数，堆顶始终是这 K 个数中的最大值。
// 参数 v：待查找数组；参数 k：需要查找的元素个数。
// 返回值：保存最小 K 个元素的大根堆，依次出堆时按从大到小输出。
// 时间复杂度：O(n log k)；额外空间复杂度：O(k)。
priority_queue<int> top_k_min(const vector<int> &v, int k)
{
    // K 必须在数组有效元素个数范围内。
    if (k <= 0 || k > v.size())
    {
        throw invalid_argument("k错误");
    }

    // 先用前 K 个元素建立候选集合。
    priority_queue<int> p;
    for (int i = 0; i < k; i++)
    {
        p.push(v[i]);
    }

    // 只有当前元素小于堆顶时，它才可能属于最小的 K 个元素。
    // 此时删除候选集合中最大的元素，再加入当前元素。
    for (int j = k; j < v.size(); j++)
    {
        if (v[j] >= p.top())
        {
            // 当前元素不小于候选集合中的最大值，直接跳过。
            continue;
        }
        else
        {
            // 用更小的当前元素替换堆顶，候选集合大小始终保持为 K。
            p.pop();
            p.push(v[j]);
        }
    }

    // 返回时不破坏原数组，调用者可通过不断 pop 读取结果。
    return p;
}

// 从数组中找出最大的 K 个元素。
// 使用小根堆保存当前最大的 K 个数，堆顶始终是这 K 个数中的最小值。
// 参数 v：待查找数组；参数 k：需要查找的元素个数。
// 返回值：保存最大 K 个元素的小根堆，依次出堆时按从小到大输出。
// 时间复杂度：O(n log k)；额外空间复杂度：O(k)。
priority_queue<int, vector<int>, greater<int>> top_k_max(const vector<int> &v, int k)
{
    // K 必须在数组有效元素个数范围内。
    if (k <= 0 || k > v.size())
    {
        throw invalid_argument("k错误");
    }

    // greater<int> 将 priority_queue 设置为小根堆。
    priority_queue<int, vector<int>, greater<int>> q;

    // 先用前 K 个元素建立候选集合。
    for (int i = 0; i < k; i++)
    {
        q.push(v[i]);
    }

    // 只有当前元素大于堆顶时，它才可能属于最大的 K 个元素。
    // 此时删除候选集合中最小的元素，再加入当前元素。
    for (int j = k; j < v.size(); j++)
    {
        if (v[j] <= q.top())
        {
            // 当前元素不大于候选集合中的最小值，直接跳过。
            continue;
        }
        else
        {
            // 用更大的当前元素替换堆顶，候选集合大小始终保持为 K。
            q.pop();
            q.push(v[j]);
        }
    }

    // 返回时不破坏原数组，调用者可通过不断 pop 读取结果。
    return q;
}

// 输出出现次数最少的 K 种元素及其出现次数。
// 参数 v：待统计数组；参数 k：需要输出的不同元素个数。
// 前置条件：K 大于 0，并且不超过数组中不同元素的个数。
// 时间复杂度：O(n + m log k)，其中 m 是不同元素的个数；额外空间复杂度：O(m + k)。
void repeat_k_min(const vector<int> &v, int k)
{
    // 统计每个元素的出现次数：key 为元素，value 为出现次数。
    unordered_map<int, int> m;
    for (auto &val : v)
    {
        m[val]++;
    }

    // 堆中元素格式为 <元素值, 出现次数>。
    // 比较器让出现次数较大的元素位于堆顶，形成大根堆。
    using pair_type = pair<int, int>;
    using Comp = function<bool(pair_type &, pair_type &)>;
    priority_queue<pair_type, vector<pair_type>, Comp> p([](pair_type &val1, pair_type &val2)
                                                         { return val1.second < val2.second; });

    // 先放入 K 种元素，作为初始候选集合。
    auto it = m.begin();
    for (int i = 0; i < k; i++, it++)
    {
        p.push(*it);
    }

    // 堆顶是候选集合中出现次数最多的元素。
    // 若新元素出现得更少，就用它替换堆顶。
    for (; it != m.end(); it++)
    {
        if (it->second >= p.top().second)
        {
            // 当前元素的频次不低于堆顶，不属于频次最小的 K 个候选项。
            continue;
        }
        else
        {
            // 用频次更低的元素替换当前候选集合中频次最高的元素。
            p.pop();
            p.push(*it);
        }
    }

    // 依次输出候选结果；由于使用大根堆，输出频次为从大到小。
    // 出现次数相同时，元素之间的顺序不确定。
    while (!p.empty())
    {
        cout << p.top().first << " " << p.top().second << endl;
        p.pop();
    }
}

// 对闭区间 [low, high] 执行一次快速排序式分区。
// 选择区间首元素作为基准值，将小于等于基准值的元素放到左侧，
// 将大于等于基准值的元素放到右侧。
// 返回值：基准值完成分区后的最终下标。
int partition(vector<int> &v, int low, int high)
{
    // 暂存基准值；它原来的位置成为一个可以被其他元素填入的“空位”。
    int t = v[low];
    int l = low;
    int h = high;

    // 左右指针相遇时，本轮分区结束。
    while (l < h)
    {
        // 从右向左寻找第一个小于基准值的元素。
        while (l < h && v[h] >= t)
        {
            h--;
        }
        if (l < h)
        {
            // 将较小元素填入左侧空位，右侧位置变成新的空位。
            v[l] = v[h];
            l++;
        }

        // 从左向右寻找第一个大于基准值的元素。
        while (l < h && v[l] <= t)
        {
            l++;
        }
        if (l < h)
        {
            // 将较大元素填入右侧空位，左侧位置再次成为空位。
            v[h] = v[l];
            h--;
        }
    }

    // 左右指针的相遇位置就是基准值的最终位置。
    v[l] = t;
    return l;
}

// 使用快速选择思想，把数组中最小的 K 个元素移动到前 K 个位置。
// low 和 high 表示当前处理的闭区间，k 表示目标元素个数。
// 注意：该函数只保证前 K 个位置存放最小的 K 个元素，并不保证它们内部有序。
void top_k_min(vector<int> &v, int low, int high, int k)
{
    // 区间只剩一个或没有元素时，无须继续分区。
    if (low >= high)
    {
        return;
    }

    // t 是基准值分区后的最终下标。
    // 分区后，[0, t - 1] 中的元素不大于 v[t]。
    int t = partition(v, low, high);

    // 下标从 0 开始，因此 t + 1 表示从数组开头到基准值共有多少个元素。
    if (t + 1 == k)
    {
        // 基准值正好位于第 K 个位置，前 K 个元素已经是所求结果。
        return;
    }
    else if (t + 1 > k)
    {
        // 基准位置在第 K 个位置右侧，继续在左半部分查找。
        top_k_min(v, low, t, k);
    }
    else if (t + 1 < k)
    {
        // 基准位置在第 K 个位置左侧，继续在右半部分查找。
        top_k_min(v, t + 1, high, k);
    }
}

// 快速选择法求最小的 K 个元素并输出。
// 前置条件：数组非空，并且 1 <= k <= v.size()。
// 平均时间复杂度：O(n)；最坏时间复杂度：O(n^2)；递归栈平均为 O(log n)。
// 该方法会改变原数组中元素的排列顺序，输出结果不保证有序。
void quick_sort_top_k_min(vector<int> &v, int k)
{
    // 在整个数组范围内执行快速选择，使最小的 K 个元素位于数组前部。
    top_k_min(v, 0, v.size() - 1, k);

    // 输出数组前 K 个位置中的元素。
    for (int i = 0; i < k; i++)
    {
        cout << v[i] << " ";
    }
    cout << endl;
}

// 测试：求最大的 3 个元素。
void test_1()
{
    vector<int> nums = {64, 45, 52, 80, 66, 68, 0, 2, 18, 75};
    priority_queue<int, vector<int>, greater<int>> q = top_k_max(nums, 3);

    // 小根堆依次出堆，因此三个最大值按从小到大的顺序输出。
    while (!q.empty())
    {
        cout << q.top() << " ";
        q.pop();
    }
    cout << endl;
}

// 测试：求最小的 3 个元素。
void test_2()
{
    vector<int> nums = {64, 45, 52, 80, 66, 68, 0, 2, 18, 75};
    priority_queue<int> p = top_k_min(nums, 3);

    // 大根堆依次出堆，因此三个最小值按从大到小的顺序输出。
    while (!p.empty())
    {
        cout << p.top() << " ";
        p.pop();
    }
    cout << endl;
}

// 测试：输出出现次数最少的 3 种元素。
void test_3()
{
    vector<int> nums = {
        5, 5, 5,
        2, 2,
        8, 8, 8, 8,
        1,
        3, 3, 3,
        7, 7,
        10};
    repeat_k_min(nums, 3);
}

// 测试：使用快速选择法输出最小的 3 个元素。
void test_4()
{
    vector<int> nums = {
        64, 12, 89, 3, 45,
        27, 91, 8, 56, 33,
        72, 19, 100, 6, 38};

    // 结果包含 3、6、8，但三者的输出顺序不一定有序。
    quick_sort_top_k_min(nums, 3);
}

int main()
{
    // 根据需要取消对应测试函数前的注释。
    // test_1();
    // test_2();
    // test_3();
    test_4();
    return 0;
}
