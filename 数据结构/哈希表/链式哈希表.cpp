#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

// 使用“数组 + 链表”的方式实现哈希表。
// 每个数组元素是一个桶，同一哈希地址上的元素保存在对应链表中。
class ChainHash
{
public:
    // 将初始容量调整为素数表中第一个不小于 size 的值。
    ChainHash(int size = prime_table[0]) : bucket(0), prime_index(0), load_factor(0.75)
    {
        for (; prime_index < prime_table_size; prime_index++)
        {
            if (size <= prime_table[prime_index])
            {
                table.resize(prime_table[prime_index]);
                break;
            }
        }
        if (prime_index == prime_table_size)
        {
            prime_index--;
            cout << "exceed,now size is " << prime_table[prime_index] << endl;
            table.resize(prime_table[prime_index]);
        }
    }

public:
    // 插入整数。插入成功返回 true，元素已存在时返回 false。
    bool add_(int val)
    {
        // 此处用“非空桶数量 / 桶总数”作为装载因子。
        double factor = bucket * 1.0 / table.size();
        if (factor > load_factor)
        {
            expand();
        }
        // 除留余数法确定元素所属的桶。
        int index = val % table.size();
        if (table[index].empty())
        {
            // 只有从空桶变为非空桶时，非空桶计数才增加。
            bucket++;
            table[index].push_back(val);
            return true;
        }
        else
        {
            // 在桶内的链表中检查元素是否已经存在。
            auto it = find(table[index].begin(), table[index].end(), val);
            if (it == table[index].end())
            {
                table[index].push_back(val);
                return true;
            }
            else
            {
                cout << "duplicate numbers" << endl;
                return false;
            }
        }
    }

    // 删除指定元素。删除成功返回 true，元素不存在时返回 false。
    bool delete_(int val)
    {
        int index = val % table.size();
        auto it = find(table[index].begin(), table[index].end(), val);
        if (it != table[index].end())
        {
            table[index].erase(it);
            if (table[index].empty())
            {
                // 删除后桶变空，需要同步减少非空桶计数。
                bucket--;
            }
            return true;
        }
        else
        {
            cout << "no numbers,can not delete" << endl;
            return false;
        }
    }

    // 查询指定元素是否存在。
    bool query_(int val)
    {
        int index = val % table.size();
        auto it = find(table[index].begin(), table[index].end(), val);
        if (it != table[index].end())
        {
            return true;
        }
        else
        {
            cout << "no numbers" << endl;
            return false;
        }
    }

    // 逐桶显示哈希表，每行先输出桶下标，再输出该桶中的所有元素。
    void show()
    {
        int i = 0;
        for (const auto& lst : table)
        {
            cout << i++ << " ";
            if (lst.empty())
            {
                cout << endl;
            }
            else
            {
                for (int v : lst)
                {
                    cout << v << " ";
                }
                cout << endl;
            }
        }
    }

private:
    // 扩展到素数表中的下一个容量，并将所有旧元素重新哈希。
    bool expand()
    {
        ++prime_index;
        if (prime_index == prime_table_size)
        {
            cout << "can not expand,size is max" << endl;
            return false;
        }
        else
        {
            // 通过 swap 暂存旧表，再按新容量创建空表。
            vector<list<int>> new_table;
            table.swap(new_table);
            table.resize(prime_table[prime_index]);
            bucket = 0;
            // 表长改变后，所有元素的哈希地址都必须重新计算。
            for (const auto& lst : new_table)
            {
                for (int v : lst)
                {
                    int index = v % table.size();
                    if (table[index].empty())
                    {
                        bucket++;
                    }
                    table[index].push_back(v);
                }
            }
            return true;
        }
    }

private:
    vector<list<int>> table; // 桶数组，每个桶使用链表存放冲突元素
    int bucket;              // 当前非空桶的数量
    double load_factor;      // 触发扩容的装载因子阈值
    static const int prime_table_size = 10;
    static int prime_table[prime_table_size];
    int prime_index;         // 当前容量在素数表中的下标
};

// 哈希表可选容量，扩容时依次使用更大的素数。
int ChainHash::prime_table[ChainHash::prime_table_size] = {3, 7, 23, 47, 97, 251, 443, 911, 1471, 42773};

int main()
{
    // 简单测试：验证重复插入、删除、查询以及逐桶输出。
    ChainHash ch1;
    ch1.add_(12);
    ch1.add_(12);
    ch1.add_(13);
    ch1.add_(14);
    ch1.add_(16);
    ch1.delete_(14);
    cout<<ch1.query_(15)<<endl<<endl;
    ch1.show();
    return 0;
}
