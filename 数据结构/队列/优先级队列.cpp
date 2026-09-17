#include <iostream>
#include <functional>
#include<cstring>
#include<ctime>

using namespace std;

class PriorityQuque
{
public:

    using Compare = function<bool(int, int)>;

public:

    PriorityQuque(int cap = 20, Compare comp = greater<int>())
        : cap(cap)
        , size(0)
        , comp(comp)
    {
        queue = new int[cap];
    }

    ~PriorityQuque()
    {
        delete[] queue;
        queue=nullptr;
    }

    void push(int val)
    {
        if(size==cap)
        {
            expand(2*cap);
        }

        if(size==0)
        {
            queue[size]=val;
        }
        else
        {
            up_shift(size,val);
        }
        size++;
    }

    void pop()
    {
        if(size==0)
        {
            return;
        }
        size--;
        if(size!=0)
        {
            down_shift(0,queue[size]);
        }
    }

    int top()
    {
        if(size!=0)
        {
            return queue[0];
        }
        throw "empty";
    }

    bool empty()
    {
        return size==0;
    }

    int size_()
    {
        return size;
    }

private:
    
    void expand(int new_cap)
    {
        int *p=new int[new_cap];
        memcpy(p,queue,size*sizeof(int));
        delete[] queue;
        queue=p;
        cap=new_cap;
    }

    void up_shift(int i,int val)
    {
        while(i>0)
        {
            int par=(i-1)/2;
            if(comp(val,queue[par]))
            {
                queue[i]=queue[par];
                i=(i-1)/2;
            }
            else
            {
                break;
            }
        }
        queue[i]=val;
    }

    void down_shift(int i,int val)
    {
        while(2*i+1<size)
        {
            int child=2*i+1;
            int max=queue[child];
            int t=child;
            if(child+1<size&&comp(queue[child+1],queue[child]))
            {
                max=queue[child+1];
                t=child+1;
            }
            if(comp(max,val))
            {
                queue[i]=max;
                i=t;
            }
            else
            {
                break;
            }
        }
        queue[i]=val;
    }

private:

    int *queue;
    int cap;
    int size;
    Compare comp;
};

int main()
{
    PriorityQuque pq1(20,less<int>());
    int arr[10];
    srand(time(nullptr));
    for(int i=0;i<10;i++)
    {
        arr[i]=rand()%100+1;
    }
    for(int v:arr)
    {
        pq1.push(v);
    }
    while(!pq1.empty())
    {
        cout<<pq1.top()<<' ';
        pq1.pop();
    }
    return 0;
}