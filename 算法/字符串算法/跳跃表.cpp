#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <map>

using namespace std;

class SkipList
{
private:
    struct Node
    {
        Node(int data = 0)
            : data(data), next(nullptr), down(nullptr)
        {
        }
        int data;
        Node *next;
        Node *down;
    };
    struct HeadNode : public Node
    {
        HeadNode(int level)
            : level(level)
        {
        }
        int level;
    };

private:
    HeadNode *head;

public:
    SkipList()
    {
        head = new HeadNode(1);
    }
    ~SkipList()
    {
        HeadNode *p = head;
        while (p != nullptr)
        {
            Node *q = p->next;
            while (q)
            {
                Node *s = q->next;
                delete q;
                q = s;
            }
            HeadNode *r = static_cast<HeadNode *>(p->down);
            delete p;
            p = r;
        }
    }
    bool find(int data)
    {
        Node *pre = head;
        Node *cur = pre->next;
        while (1)
        {
            if (cur != nullptr && cur->data < data)
            {
                pre = cur;
                cur = cur->next;
            }
            else if (cur != nullptr && cur->data == data)
            {
                return true;
            }
            else
            {
                if (pre->down == nullptr)
                {
                    return false;
                }
                pre = pre->down;
                cur = pre->next;
            }
        }
    }
    void init_test_data()
    {
        vector<vector<int>> values = {
            {7, 14, 21, 32, 37, 71, 85, 117},
            {7, 21, 37, 71},
            {21, 37}};

        // 记录下面一层的节点，方便连接 down 指针
        map<int, Node *> lower;

        for (int i = 0; i < values.size(); i++)
        {
            // 第一层的头节点已经在构造函数里创建了
            if (i > 0)
            {
                HeadNode *newHead = new HeadNode(i + 1);
                newHead->down = head;
                head = newHead;
            }

            Node *p = head;
            map<int, Node *> current;

            for (int data : values[i])
            {
                Node *node = new Node(data);

                // 连接同一层的 next 指针
                p->next = node;
                p = node;

                // 上层节点指向下一层的对应节点
                if (i > 0)
                {
                    node->down = lower[data];
                }

                current[data] = node;
            }

            lower = current;
        }
    }
    int get_level()
    {
        int level = 1;
        while (rand() % 2 == 1)
        {
            level++;
        }
        return level;
    }
    void add(int data)
    {
        if (find(data))
        {
            return;
        }

        int level = get_level();
        if (level > head->level)
        {
            level = head->level + 1;
            HeadNode *nnode = new HeadNode(level);
            nnode->down = head;
            head = nnode;
        }

        Node **node_list = new Node *[level];
        for (int i = 0; i < level; i++)
        {
            node_list[i] = new Node(data);
            if (i > 0)
            {
                node_list[i]->down = node_list[i - 1];
            }
        }

        HeadNode *p = head;
        for (int i = head->level; i > level; i--)
        {
            p = static_cast<HeadNode *>(p->down);
        }

        Node *pre = p;
        Node *cur = p->next;
        for (int i = p->level - 1; i >= 0; i--)
        {
            while (cur != nullptr && cur->data < data)
            {
                pre = cur;
                cur = cur->next;
            }
            node_list[i]->next = cur;
            pre->next = node_list[i];

            if (i > 0)
            {
                pre = pre->down;
                cur = pre->next;
            }
        }
        delete[] node_list;
    }
    void show()
    {
        HeadNode *p = head;
        while (p != nullptr)
        {
            Node *q = p->next;
            while (q)
            {
                cout << q->data << " ";
                q = q->next;
            }
            cout << endl;
            p = static_cast<HeadNode *>(p->down);
        }
    }
    void delete_(int data)
    {
        Node *pre = head;
        Node *cur = pre->next;
        while (1)
        {
            if (cur != nullptr && cur->data < data)
            {
                pre = cur;
                cur = cur->next;
            }
            else if (cur != nullptr && cur->data == data)
            {
                break;
            }
            else
            {
                if (pre->down == nullptr)
                {
                    return;
                }
                pre = pre->down;
                cur = pre->next;
            }
        }
        while (1)
        {
            pre->next = cur->next;
            Node *p = cur->down;
            delete cur;
            if(p==nullptr)
            {
                break;
            } 
            cur = p;
            pre = pre->down;
            while (pre->next != cur)
            {
                pre = pre->next;
            }
        }
        while(head->next==nullptr&&head->down!=nullptr)
        {
            Node *p=head->down;
            delete head;
            head=static_cast<HeadNode *>(p);
        }
    }
};

void test_find()
{
    SkipList list;
    list.init_test_data();
    cout << list.get_level() << endl;
    cout << list.find(7) << endl;
}

void test_add()
{
    SkipList list;
    for (int i = 0; i < 20; i++)
    {
        list.add(rand() % 100);
    }
    list.show();
}

void test_delete()
{
    SkipList list;
    for (int i = 0; i < 20; i++)
    {
        list.add(rand() % 100);
    }
    list.delete_(57);
    list.show();
}

int main()
{
    test_delete();
    return 0;
}