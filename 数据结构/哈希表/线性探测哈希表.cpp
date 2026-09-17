#include <iostream>

using namespace std;

// 哈希槽位的三种状态。
// 删除元素时不能直接改为 NoUse，否则会截断发生冲突的元素的查找路径。
enum State
{
    Using, // 槽位当前保存着有效元素
    NoUse, // 槽位从未被使用过
    Delete // 槽位中的元素已被逻辑删除，可供后续插入复用
};

// 哈希表中的单个槽位，同时保存数值和槽位状态。
struct Node
{
    Node(int val = 0, State state = NoUse) : val(val), state(state) {}
    int val;
    State state;
};

class HashTable
{
public:
    // 将用户指定的容量向上调整为素数表中第一个足够大的值，
    // 使用素数作为表长可以减少取模哈希产生的聚集现象。
    HashTable(int size_ = 3) : use_size(0), load_factor(0.8),prime_index(0) 
    {
        if (size_ >= 42773)
        {
            size = 42773;
            prime_index = prime_table_size - 1;
            cout << "Exceeding the maximum length,length is 42773 now" << endl;
        }
        else
        {
            for (int i = 0; i < prime_table_size; i++)
            {
                if (size_ <=prime_table[i])
                {
                    size = prime_table[i];
                    prime_index = i;
                    break;
                }
            }
        }
        node = new Node[size];
    }

    // 释放构造函数中动态申请的槽位数组。
    ~HashTable()
    {
        delete[] node;
        node = nullptr;
    }

public:
    // 插入一个整数。发生哈希冲突时，向后逐槽进行线性探测。
    void add_(int val)
    {
        // 装载因子 = 当前有效元素数量 / 哈希表容量。
        double factor = use_size * 1.0 / size;

        cout<<factor<<endl;

        if (factor > load_factor)
        {
            // 装载因子超过阈值时先扩容，降低后续冲突概率。
            expand();
        }

        int index = hash(val);
        // 从哈希位置开始循环探测，最多检查 size 个槽位。
        for (int i = index, j = 0; j < size; j++, i = (i + 1) % size)
        {
            // NoUse 和 Delete 槽位都可以用于保存新元素。
            if (node[i].state != Using)
            {
                node[i].val = val;
                node[i].state = Using;
                use_size++;
                break;
            }
        }
    }

    // 逻辑删除指定元素，不破坏线性探测形成的查找链。
    void delete_(int val)
    {
        int index = hash(val);
        for (int i = index, j = 0; j < size; j++, i = (i + 1) % size)
        {
            if (node[i].state == Using)
            {
                if (node[i].val == val)
                {
                    // 使用 Delete 标记墓碑，后面的冲突元素仍然可以被查询到。
                    node[i].state = Delete;
                    use_size--;
                }
            }
            else if (node[i].state == NoUse)
            {
                // 遇到从未使用的槽位，说明目标值不可能出现在后续位置。
                return;
            }
        }
    }

    // 查询指定元素，找到时返回槽位下标，否则返回 -1。
    int query(int val)
    {
        int index = hash(val);
        for (int i = index, j = 0; j < size; j++, i = (i + 1) % size)
        {
            if (node[i].state == Using)
            {
                if (node[i].val == val)
                {
                    return i;
                }
            }
            else if (node[i].state == NoUse)
            {
                // NoUse 表示线性探测链已经结束，可以提前停止查找。
                return -1;
            }
            else
            {
                // Delete 槽位只跳过，不能终止查找。
                continue;
            }
        }
        return -1;
    }

    // 按槽位顺序显示哈希表；空闲或已删除的槽位统一显示为 *。
    void show()
    {
        for (int i = 0; i < size; i++)
        {
            if (node[i].state == Using)
            {
                cout << node[i].val << ' ';
            }
            else
            {
                cout << "*" << ' ';
            }
        }
        cout << endl;
    }

private:
    // 除留余数法：把整数映射到 [0, size - 1] 的槽位。
    int hash(int val)
    {
        return val % size;
    }

    // 扩展到素数表中的下一个容量，并重新计算所有有效元素的位置。
    void expand()
    {
        ++prime_index;
        if (prime_index == prime_table_size)
        {
            throw "can not expand,exceed";
        }
        Node *new_node = new Node[prime_table[prime_index]];
        int k = 0;
        for (int i = 0; i < size; i++)
        {
            // 仅迁移有效元素，已删除的墓碑不会进入新表。
            if (node[i].state == Using)
            {
                int index = node[i].val % prime_table[prime_index];
                // 新表中仍使用线性探测解决冲突。
                for (int k = index, j = 0; j < prime_table[prime_index]; j++, k = (k + 1) % prime_table[prime_index])
                {
                    if (new_node[k].state != Using)
                    {
                        new_node[k].val = node[i].val;
                        new_node[k].state = Using;
                        break;
                    }
                }
            }
        }
        delete[] node;
        node = new_node;
        size = prime_table[prime_index];
    }

private:
    Node *node;        // 动态槽位数组
    int size;          // 当前哈希表容量
    int use_size;      // 当前有效元素数量
    double load_factor;// 触发扩容的装载因子阈值
    static const int prime_table_size = 10;
    static int prime_table[prime_table_size];
    int prime_index;   // 当前容量在素数表中的下标
};

// 预设的扩容容量序列，每次扩容选择下一个素数。
int HashTable::prime_table[HashTable::prime_table_size] = {3, 7, 23, 47, 97, 251, 443, 911, 1471, 42773};

int main()
{
    // 第一组测试代码可用于连续插入、查询、删除和显示哈希表。
    // HashTable ht1;
    // for (int i = 0; i < 20; i++)
    // {
    //     ht1.add_(20 - i);
    // }
    // ht1.show();
    // cout << ht1.query(5) << endl;
    // ht1.delete_(14);
    // ht1.show();
    // cout << ht1.query(1) << endl;

    // 第二组测试代码用于观察重复值、冲突和删除操作。
    HashTable ht2;
    ht2.add_(21);
    ht2.add_(21);
    ht2.add_(32);
    ht2.add_(14);
    ht2.add_(15);
    ht2.add_(16);

    cout<<ht2.query(21)<<endl;
    ht2.delete_(21);
    cout<<ht2.query(21)<<endl;
    return 0;
}
