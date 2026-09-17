#include<iostream>
using namespace std;

struct Node
{
    Node(int data,Node *next):data(data),next(next){}
    int data;
    Node *next;  
};

class CircleLink
{
public:
    CircleLink()
    {
        head=new Node(0,nullptr);
        tail=head;
        head->next=head;
    }
    ~CircleLink()
    {
        Node *p=head->next;
        while(p!=head)
        {
            Node *s=p;
            p=p->next;
            delete s;
        }
        delete head;
    }
    void insert_start(int data)
    {
        Node *p=new Node(data,nullptr);
        p->next=head->next;
        head->next=p;
        if(p->next==head)
        {
            tail=p;
        }
    }
    void insert_end(int data)
    {
        Node *p=new Node(data,nullptr);
        p->next=tail->next;
        tail->next=p;
        tail=p;
    }
    void delete_(int data)
    {
        Node *q=head;
        Node *p=head->next;
        while(p!=head)
        {
            if(p->data==data)
            {
                q->next=p->next;
                delete p;
                if(q->next==head)
                {
                    tail=q;
                }
                p=q->next;
            }
            else
            {
                p=p->next;
                q=q->next;
            }
        }
    }
    bool find(int data)
    {
        Node *p=head->next;
        while(p!=head)
        {
            if(p->data==data)
            {
                return true;
            }
            else
            {
                p=p->next;
            }
        }
        return false;
    }
    void show()
    {
        if(!head)
        {
            return;
        }
        Node *p=head->next;
        while(p!=head)
        {
            cout<<p->data<<" ";
            p=p->next;
        }
        cout<<endl;
    }
private:
    Node *head;
    Node *tail;
};

int main()
{
    CircleLink cl1;
    CircleLink cl2;
    for(int i=0;i<10;i++)
    {
        cl1.insert_end(i);
        cl2.insert_start(i);
    }
    cl1.show();
    cl2.show();
    bool a=cl1.find(2);
    for(int i=0;i<12;i++)
    {
        bool a=cl1.find(i);
        cout<<a<<" ";
    }
    cout<<endl;
    cl1.delete_(5);
    cl1.show();
    
    return 0;
}