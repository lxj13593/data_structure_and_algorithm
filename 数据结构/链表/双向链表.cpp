#include<iostream>
using namespace std;

struct Node
{
    Node(int data=0):
        data(data)
        ,next(nullptr)
        ,pre(nullptr)
    {}
    int data;
    Node *next;
    Node *pre;  
};

class TwoLink
{
public:
    TwoLink()
    {
        head=new Node();
    }
    ~TwoLink()
    {
        Node *p=head;
        while(p)
        {
            head=head->next;
            delete p;
            p=head;
        }
    }
    void insert_start(int data)
    {
        Node *p=new Node(data);
        if(head->next!=nullptr)
        {
            head->next->pre=p;
        }
        p->next=head->next;
        p->pre=head;
        head->next=p;
    }
    void insert_end(int data)
    {
        Node *q=new Node(data);
        Node *p=head;
        while(p->next!=nullptr)
        {
            p=p->next;
        }
        p->next=q;
        q->pre=p;
    }
    void delete_data(int data)
    {
        Node *p=head->next;
        while(p!=nullptr)
        {
            if(p->data==data)
            {
                p->pre->next=p->next;
                if(p->next!=nullptr)
                {
                    p->next->pre=p->pre;
                }
                Node *s=p->next;
                delete p;
                p=s;
            }
            else
            {
                p=p->next;
            }
        }
    }
    void show()
    {
        Node *p=head->next;
        while(p!=nullptr)
        {
            cout<<p->data<<" ";
            p=p->next;
        }
        cout<<endl;
    }
    int find(int data)
    {
        Node *p=head->next;
        while(p!=nullptr)
        {
            if(p->data==data)
            {
                return data;
            }
            p=p->next;
        }
        return 0;
    }
private:
    Node *head;

};

int main()
{
    TwoLink tl1;
    TwoLink tl2;
    for(int i=1;i<=10;i++)
    {
        tl1.insert_end(i);
    }
    tl1.show();
    cout<<tl1.find(11)<<endl;
    for(int i=1;i<=10;i++)
    {
        tl2.insert_start(i);
    }
    tl2.show();
    tl2.delete_data(5);
    tl2.show();
    return 0;
}