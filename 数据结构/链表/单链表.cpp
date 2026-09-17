#include <iostream>
#include <cstdlib>
using namespace std;

struct Node
{
    Node(int data = 0) : data(data), next_(nullptr) {}
    int data;
    Node *next_;
};

class Link
{
public:
    Link()
    {
        head = new Node();
    }
    // ~Link()
    // {
    //     Node *p = head;
    //     while (p)
    //     {
    //         Node *next = p->next_;
    //         delete p; 
    //         p = next;
    //     }
    // }
    // 拷贝构造函数（防止浅拷贝）
    Link(const Link &other)
    {
        head = new Node();
        Node *curr = other.head->next_;
        Node *tail = head;
        while (curr)
        {
            tail->next_ = new Node(curr->data);
            tail = tail->next_;
            curr = curr->next_;
        }
    }

    // 拷贝赋值运算符
    Link &operator=(const Link &other)
    {
        if (this != &other)
        {
            // 释放现有内存
            Node *p = head;
            while (p)
            {
                Node *next = p->next_;
                delete p;
                p = next;
            }

            // 深拷贝
            head = new Node();
            Node *curr = other.head->next_;
            Node *tail = head;
            while (curr)
            {
                tail->next_ = new Node(curr->data);
                tail = tail->next_;
                curr = curr->next_;
            }
        }
        return *this;
    }

    void insert_back(int val)
    {
        Node *p = new Node(val);
        Node *q = head;
        while (q->next_ != nullptr)
        {
            q = q->next_;
        }
        q->next_ = p;
    }
    void show()
    {
        Node *p = head->next_;
        while (p)
        {
            cout << p->data << " ";
            p = p->next_;
        }
        cout << endl;
    }
    void insert_begin(int val)
    {
        Node *p = new Node(val);
        p->next_ = head->next_;
        head->next_ = p;
    }
    void delete_node(int val)
    {
        Node *p = head;
        Node *q = head->next_;
        while (q)
        {
            if (q->data == val)
            {
                Node *s = q->next_;
                p->next_ = q->next_;
                q = s;
                continue;
            }
            p = p->next_;
            q = q->next_;
        }
    }
    void delete_pos(int pos)
    {
        Node *p = head;
        Node *q = head->next_;
        int i = 0;
        while (pos <= 0)
        {
            return;
        }
        while (i != pos - 1 && q)
        {
            q = q->next_;
            p = p->next_;
            i++;
        }
        if (q)
        {
            p->next_ = q->next_;
        }
    }
    void reverse_()
    {
        Node *p = head->next_;
        head->next_ = nullptr;
        Node *q = nullptr;
        while (p)
        {
            q = p->next_;
            p->next_ = head->next_;
            head->next_ = p;
            p = q;
        }
    }
    int find(int datas)
    {
        Node *p = head;
        while (p)
        {
            if (p->data == datas)
            {
                return 1;
            }
            p = p->next_;
        }
        return 0;
    }
    Node *find_k_end(int k)
    {
        Node *p = head->next_;
        Node *q = head->next_;
        while (k > 0)
        {
            p = p->next_;
            k--;
        }
        while (p != nullptr)
        {
            p = p->next_;
            q = q->next_;
        }
        return q;
    }

    Node *get_head()
    {
        return head;
    }
    bool circle_judge(Node *&see, Node *&start)
    {
        Node *slow = head;
        Node *fast = head;
        bool flag = 0;
        if(!head||!head->next_)
        {
            see = nullptr;
            start = nullptr;
            return 0;
        }
        slow = slow->next_;
        fast = fast->next_->next_;
        while ( fast && fast->next_)
        {
            if(slow!=fast)
            {
                fast = fast->next_->next_;
                slow = slow->next_;
            }
            else
            {
                flag=1;
                break;
            }
        }
        if (flag == 1)
        {
            see=fast;
            Node *s = fast;
            Node *r = head;
            while (r != s)
            {
                r = r->next_;
                s = s->next_;
            }
            start=r;
        }
        return flag;
    }
private:
    Node *head;
};

Link merge_two_sorted_link(Node *head1, Node *head2)
{
    Node *p = head1->next_;
    Node *q = head2->next_;
    Link links;
    while (p != nullptr && q != nullptr)
    {
        if (p->data > q->data)
        {
            links.insert_back(q->data);
            q = q->next_;
        }
        else
        {
            links.insert_back(p->data);
            p = p->next_;
        }
    }
    while (p != nullptr)
    {
        links.insert_back(p->data);
        p = p->next_;
    }
    while (q != nullptr)
    {
        links.insert_back(q->data);
        q = q->next_;
    }
    return links;
}

Node *cross_judge(Link &l1,Link &l2)
{
    Node *p=l1.get_head()->next_;
    Node *q=l2.get_head()->next_;
    int a=0,b=0;
    while(p)
    {
        a++;
        p=p->next_;
    }
    while(q)
    {
        b++;
        q=q->next_;
    }
    p=l1.get_head()->next_;
    q=l2.get_head()->next_;
    int c=std::abs(a-b);

    cout<<a<<" "<<b<<" "<<c<<endl;

    if(a>b)
    {
        while(c>0)
        {
            c--;
            p=p->next_;
        }
    }
    else
    {
        while(c>0)
        {
            c--;
            q=q->next_;
        }
    }
    cout<<p->data<<endl;
    cout<<q->data<<endl;
    while(p)
    {
        if(p!=q)
        {
            p=p->next_;
            q=q->next_;
        }
        else
        {
            // cout<<q->data<<endl;
            return q;
        }
    }
    return nullptr;
}

int main()
{
    Link link;
    Link link2;
    srand(time(nullptr));
    for (int i = 0; i < 10; i++)
    {
        if (i % 2 == 0&&i!=8)
        {
            link.insert_back(i);
        }
        // else
        // {
        //     link2.insert_back(i);
        // }
        // cout<<a<<' ';
    }
    link2.insert_back(0);
    cout << endl;
    // cout<<"delete before:"<<endl;
    link.show();
    link2.show();

    Node *p1 = link.get_head();
    while (p1->next_ ->next_!= nullptr)
    {
        p1 = p1->next_;
    }
    Node *q1=link2.get_head()->next_;
    q1->next_=p1;

    link.show();
    link2.show();

    Node *s=cross_judge(link,link2);
    if(s)
    {
        cout<<s->data<<endl;
    }
    // Node *p = link.get_head()->next_;
    // while (p->next_ != nullptr)
    // {
    //     p = p->next_;
    // }
    // p->next_ = link.get_head()->next_;
    // link.show();
    // link2.show();
    /*     int a=2;
        link.delete_node(a);
        cout<<"delete elem"<<a<<endl;
        cout<<"delete end:"<<endl; */
    // link.delete_pos(10);
    /*     link.reverse_(); */
    // int a=link.find(6);
    // cout<<a;
    // link.show();
    // Node *q=link.find_k_end(1);
    // cout<<q->data;
    // Link link3 = merge_two_sorted_link(link.get_head(), link2.get_head());
    // Node *see=nullptr;
    // Node *start=nullptr;
    // bool a = link.circle_judge(see,start);
    // cout << a<<endl;
    // if(a==1)
    // {
    //     cout<<see->data<<endl;
    //     cout<<start->data<<endl; 
    // }
    // link3.show();
    return 0;
}
