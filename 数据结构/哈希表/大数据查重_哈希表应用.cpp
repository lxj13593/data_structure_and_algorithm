#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

// 按照元素在数组中的出现顺序，查找第一个重复出现的数字。
// unordered_set 用来记录已经扫描过的数字，平均时间复杂度为 O(n)。
void check_first_repeat_number(const vector<int> &v)
{
    // s 中只保存当前元素之前已经出现过的数字。
    unordered_set<int> s;
    for (const auto &val : v)
    {
        auto it = s.find(val);
        if (it == s.end())
        {
            s.emplace(val);
        }
        else
        {
            // 当前数字已经存在于集合中，因此它是第一个被再次遇到的数字。
            cout << "第一次重复出现数字：" << val << endl;
            break;
        }
    }
}

// 查找所有重复出现的数字，每个重复数字只输出一次。
void check_all_repeat_number(const vector<int> &v)
{
    // s 记录已经出现过的数字，s1 记录已经输出过的重复数字。
    unordered_set<int> s;
    unordered_set<int> s1;
    cout << "重复出现数字：" << endl;
    for (const auto &val : v)
    {
        auto it = s.find(val);
        auto it1 = s1.find(val);
        if (it == s.end())
        {
            s.emplace(val);
        }
        else if (it1 == s1.end())
        {
            // val 在 s 中但不在 s1 中，说明它第一次被判定为重复。
            s1.emplace(val);
            cout << val << ' ';
        }
    }
    cout << endl;
}

// 统计每个数字的出现次数，并输出出现两次及以上的数字。
void check_all_repeat_number_and_quantity(const vector<int> &v)
{
    // 键为数字，值为该数字已经出现的次数。
    unordered_map<int, int> m;
    for (const auto &val : v)
    {
        auto it = m.find(val);
        if (it == m.end())
        {
            m.emplace(val,1);
        }
        else
        {
            it->second++;
        }
    }
    cout << "重复出现数字：" << endl;
    for(const auto &val:m)
    {
        if(val.second>1)
        {
            cout<<val.first<<" 次数："<<val.second<<endl;
        }
    }
}

// 使用哈希集合去除数组中的重复数字。
// 注意：unordered_set 不保证遍历顺序，因此去重后可能不再保持原顺序。
void deduplication(vector<int> &v)
{
    unordered_set<int> s;
    for(const auto &val:v)
    {
        s.emplace(val);
    }
    v.assign(s.begin(),s.end());
}


// 查找字符串中第一个只出现一次的字符。
void  first_no_repeat_char()
{
    string s = "abcaadeffghijjk";
    // 第一次遍历统计字符频次。
    unordered_map<char, int> m;
    for (const auto &val : s)
    {
        auto it = m.find(val);
        if (it == m.end())
        {
            m.emplace(val,1);
        }
        else
        {
            it->second++;
        }
    }
    // 第二次按原字符串顺序查找，保证得到的是“第一个”不重复字符。
    for(const auto &val:s)
    {
        if(m[val]==1)
        {
            cout<<val<<endl;
            break;
        }
    }
}

int main()
{
    // 生成 10 个 [0, 9] 范围内的随机数，作为各示例函数的测试数据。
    vector<int> v;
    srand(time(nullptr));
    for (int i = 0; i < 10; i++)
    {
        v.push_back(rand() % 10);
    }
    // 根据需要取消下面某一行的注释，观察对应功能的运行结果。
    // check_first_repeat_number(v);
    // check_all_repeat_number(v);
    // check_all_repeat_number_and_quantity(v);
    // deduplication(v);
    // for_each(v.begin(),v.end(),[](int val){cout<<val<<" ";});
    // cout<<endl;
    // first_no_repeat_char();
    return 0;
}
