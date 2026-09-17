#include <iostream>

using namespace std;

class CircleQueue
{
public:
    CircleQueue(int size = 10)
        : front(0)
        , rear(0)
        , size(size)
        , length(0)
        , expand_size(0)
    {
        queue = new int[size];
    }
    ~CircleQueue()
    {
        delete[] queue;
        queue = nullptr;
    }
public:
    void push(int val)
    {
        if ((rear + 1) % size == front)
        {
            expand(size*2);
        }
        queue[rear] = val;
        rear = (rear + 1) % size;
        length++;
    }
    void pop()
    {
        if(front!=rear)
        {
            front=(front+1)%size;
            length--;
        }
    }
    
    bool is_empty()
    {
        return front==rear;
    }

    int front_()
    {
        if(!is_empty())
        {
            return queue[front];
        }
        throw "empty";
    }
    int back_()
    {
        if(!is_empty())
        {
            return queue[(rear-1+size)%size];
        }
        throw "empty";
    }
    int length_()
    {
        return length;
    }
    void show()
    {
        for(int i=front;i!=rear;i=(i+1)%size)
        {
            cout<<queue[i]<<" ";
        }
        cout<<endl;
    }
    int expand_size_()
    {
        return expand_size;
    }
private:
    void expand(int new_size)
    {
        int *p=new int[new_size];
        int i=0;
        int j=front;
        for(;j!=rear;i++,j=(j+1)%size)
        {
            p[i]=queue[j];
        }
        delete[] queue;
        front=0;
        rear=i;
        queue=p;
        size=new_size;
        expand_size++;
    }
private:
    int front;
    int rear;
    int size;
    int length;
    int expand_size;
    int *queue;
};

int main()
{
    CircleQueue cq1;
    int arr[]={10,25,61,85,32,45,16,45};
    for(int v:arr)
    {
        cq1.push(v);
    }
    cq1.show();
    cq1.push(1);
    cout<<cq1.expand_size_()<<endl;
    cq1.push(2);
    cout<<cq1.expand_size_()<<endl;
    cq1.push(3);
    cout<<cq1.expand_size_()<<endl;
    cq1.show();

    cq1.pop();
    cq1.pop();
    cq1.pop();
    cq1.show();

    cout<<cq1.length_()<<endl;

    while(!cq1.is_empty())
    {
        cout<<cq1.front_()<<" "<<cq1.back_()<<endl;
        cq1.pop();
    }

    return 0;
}