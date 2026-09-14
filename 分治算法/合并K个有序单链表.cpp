#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

struct Node
{
    int data;
    Node *next;
    Node(int data) : data(data), next(nullptr) {}
};

Node *init_link(initializer_list<int> list)
{
    Node *head = nullptr;
    Node *p = nullptr;
    for (int val : list)
    {
        if (head == nullptr)
        {
            p = new Node(val);
            head=p;
        }
        else
        {
            p->next= new Node(val);
            p=p->next;
        }
    }
    return head;
}

Node *merge_two_link(Node *p1,Node *p2)
{
    Node *head=new Node(0);
    Node *p=head;
    while(p1!=nullptr&&p2!=nullptr)
    {
        if(p1->data<p2->data)
        {
            p->next=p1;
            p=p->next;
            p1=p1->next;
        }
        else
        {
            p->next=p2;
            p2=p2->next;
            p=p->next;
        }
    }
    if(p1)
    {
        p->next=p1;
    }
    if(p2)
    {
        p->next=p2;
    }
    Node *s=head->next;
    delete head;
    head=nullptr;
    return s;
}

Node *merge_link_k(vector<Node*> &v,int l,int h)
{
    if(l>=h)
    {
        return v[l];
    }
    else
    {
        int mid=(l+h)/2;
        Node *left=merge_link_k(v,l,mid);
        Node *right=merge_link_k(v,mid+1,h);
        return merge_two_link (left,right);
    }
}

int main()
{
    Node *p1=init_link({1, 4, 7, 10, 15});
    Node *p2=init_link({2, 5, 8, 12, 18});
    Node *p3=init_link({3, 6, 9, 14, 20});
    Node *p4=init_link({0, 11, 13, 16, 22});
    vector<Node*> some_list;
    some_list.push_back(p1);
    some_list.push_back(p2);
    some_list.push_back(p3);
    some_list.push_back(p4);
    Node *p=merge_link_k(some_list,0,some_list.size()-1);
    for(Node *t=p;t!=nullptr;t=t->next)
    {
        cout<<t->data<<" ";
    }
    cout<<endl;
    return 0;
}