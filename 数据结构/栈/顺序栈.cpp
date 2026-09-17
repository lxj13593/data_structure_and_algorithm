#include<iostream>
using namespace std;

class Stack
{
public:
    Stack(int size=10):
        size(size)
        ,top(0)
    {
        myStack=new int[size];
    }

    ~Stack()
    {
        delete[] myStack;
        myStack=nullptr;
    }

    void push(int val)
    {
        if(top==size)
        {
            expand(size*2);
        }
        myStack[top++]=val;
    }

    void pop()
    {
        if(top==0)
        {
            return;
        }
        top--;
    }

    int get_top() const
    {
        if(top==0)
        {
            throw "stack is empty"; 
        }
        return myStack[top-1];
    }

    int get_length() const
    {
        return top;
    }

    bool is_empty()
    {
        return top==0;
    }

private:
    int *myStack;
    int top;
    int size;
    
    void expand(int new_size)
    {
        int *p=new int[new_size];
        memcpy(p,myStack,sizeof(int)*size);
        delete[] myStack;
        size=new_size; 
        myStack=p;
    }
};

int main()
{
    Stack s1;
    int arr[]={10,52,63,87,95,63};
    for(int v:arr)
    {
        s1.push(v);
    }
    while(s1.is_empty()!=1)
    {
        cout<<s1.get_top()<<" ";
        s1.pop();
    }
    cout<<s1.get_length();
    return 0;
}
