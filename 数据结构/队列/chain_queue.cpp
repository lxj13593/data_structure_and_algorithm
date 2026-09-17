#include<iostream>

using namespace std;

struct Node
{
    Node(int data=0):data(data),pre_(nullptr),next_(nullptr){}
    int data;
    Node *next_;
    Node *pre_;
};

class ChainQueue
{
public:
    ChainQueue()
    {
        head=new Node();
        head->next_=head;
        head->pre_=head;
        length=0;
    }
    ~ChainQueue()
    {
        Node *p=head->next_;
        while(p!=head)
        {
            head->next_=p->next_;
            p->next_->pre_=head;
            delete p;
            p=head->next_;
        }
        delete head;
        head=nullptr;
    }
public:
    void push(int val)
    {
        Node *node=new Node(val);
        node->pre_=head->pre_;
        node->next_=head;
        head->pre_->next_=node;
        head->pre_=node;
        length++;
    }
    void pop()
    {
        Node *p=head->next_;
        if(p!=head)
        {
            head->next_=p->next_;
            p->next_->pre_=head;
            delete p;
            length--;
        }
    }
    int front()
    {
        if(head->next_!=head)
        {
            return head->next_->data;
        }
        throw "empty";
    }
    int back()
    {
        if(head->next_!=head)
        {
            return head->pre_->data;
        }
        throw "empty";
    }
    int size()
    {
        return length;
    }
    bool empty()
    {
        return head->next_==head;
    }
    void show()
    {
        Node *p=head->next_;
        while(p!=head)
        {
            cout<<p->data<<" ";
            p=p->next_;
        }
        cout<<endl;
    }
private:
    Node *head;
    int length;
};

int main()
{
    ChainQueue cq1;
    int arr[]={10,25,61,85,32,45,16,45};
    for(int v:arr)
    {
        cq1.push(v);
    }
    cq1.show();
    cq1.push(1);
    cq1.push(2);
    cq1.push(3);
    cq1.show();

    cq1.pop();
    cq1.pop();
    cq1.pop();
    cq1.show();

    cout<<cq1.size()<<endl;

    while(!cq1.empty())
    {
        cout<<cq1.front()<<" "<<cq1.back()<<endl;
        cq1.pop();
    }
    return 0;
}