#include<iostream>
using namespace std;

struct Node
{
    Node(int data,Node *next):data(data),next(next){}
    int data;
    Node *next;  
};

void ysf_circle(Node *head,int k,int m)
{
    Node *p=head;
    Node *q=head;
    while(q->next!=head)
    {
        q=q->next;
    }
    for(int i=1;i<k;i++)
    {
        q=p;
        p=p->next;
    }
    for(;;)
    {
        for(int i=1;i<m;i++)
        {
            q=p;
            p=p->next;
        }
        cout<<p->data<<endl;
        if(q==p)
        {
            delete p;
            break;
        }
        q->next=p->next;
        delete p;
        p=q->next;
    }
}

int main()
{
    Node *head=new Node(1,nullptr);
    Node *n2=new Node(2,nullptr);
    Node *n3=new Node(3,nullptr);
    Node *n4=new Node(4,nullptr);
    Node *n5=new Node(5,nullptr);
    Node *n6=new Node(6,nullptr);
    Node *n7=new Node(7,nullptr);
    Node *n8=new Node(8,nullptr);

    head->next=n2;
    n2->next=n3;
    n3->next=n4;
    n4->next=n5;
    n5->next=n6;
    n6->next=n7;
    n7->next=n8;
    n8->next=head;

    ysf_circle(head,1,1);

}