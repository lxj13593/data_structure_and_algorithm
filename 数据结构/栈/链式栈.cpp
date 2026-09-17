#include<iostream>
using namespace std;

struct Node
{
    Node(int data=0):
        data(data)
        ,next(nullptr)
    {}
    int data;
    Node *next;
};

class Stack
{
public:
    Stack()
    {
        head=new Node();
        size=0;
    }
    ~Stack()
    {
        Node *p=head;
        while(p)
        {
            head=head->next;
            delete p;
            p=head;
        }
    }
    void push(int val)
    {
        Node *p=new Node(val);
        p->next=head->next;
        head->next=p;
        size++;
    }
    void pop()
    {
        if(head->next)
        {
            Node *p=head->next;
            head->next=p->next;
            delete p;
            size--;
        }
    }
    int top()
    {
        if(head->next) return head->next->data;
        else throw "stack is empty";
    }
    int s_size()
    {
        return size;
    }
    bool is_empty()
    {
        if(head->next==nullptr)
        {
            return true;
        }
        return false;
    }

private:
    Node *head;
    int size;
};

int main()
{
    Stack s1;
    int arr[]={10,20,62,21,52,30};
    for(int v:arr)
    {
        s1.push(v);
    }
    cout<<s1.s_size()<<endl;
    while(s1.is_empty()!=1)
    {
        cout<<s1.top()<<" ";
        s1.pop();
    }
    cout<<endl;
    cout<<s1.s_size()<<endl;
    return 0;
}
