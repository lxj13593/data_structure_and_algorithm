#include <iostream>
using namespace std;

class MyArray
{
public:
    MyArray(int size = 10);
    ~MyArray();
    int getMycap();
    int getMycur();
    void push_back(int elem);
    void pop_back();
    void delete_(int pos);
    void add(int elem, int pos);
    int find(int elem);
    void show();
    void change_elem(int elem1,int elem2);
private:
    void expand(int size);
    int *p;
    int mycur;
    int mycap;
};

MyArray::MyArray(int size) : mycap(size), mycur(0)
{
    this->p = new int[size]();
}

MyArray::~MyArray()
{
    delete[] p;
    p = nullptr;
}

void MyArray::push_back(int elem)
{
    if (mycur == mycap)
    {
        expand(mycap * 2);
    }
    p[mycur] = elem;
    mycur++;

}

void MyArray::pop_back()
{
    if (mycur > 0)
    {
        mycur--;
    }
}

void MyArray::delete_(int pos)
{
    if (pos < 0 || pos >= mycur)
    {
        return;
    }
    else
    {
        for (int i = pos + 1; i < mycur; i++)
        {
            p[i - 1] = p[i];
        }
    }
    mycur--;
}

void MyArray::add(int elem, int pos)
{
    if (pos < 0 || pos > mycur)
    {
        return;
    }
    if (mycur == mycap)
    {
        expand(2 * mycap);
    }

    for(int i=mycur-1;i>=pos;i--)
    {
        p[i+1]=p[i];
    }
    p[pos]=elem;
    mycur++;
}

int MyArray::find(int elem)
{
    for(int i=0;i<mycur;i++)
    {
        if(p[i]==elem)
        {
            return i;
        }
    }
    return -1;
}

void MyArray::expand(int size)
{
    int *p1=new int[size]();
    memcpy(p1,p,sizeof(int)*mycap);
    delete []p;
    p=p1;
    mycap=size;
}

void MyArray::show()
{
    for(int i=0;i<mycur;i++)
    {
        cout<<p[i]<<" ";
    }
    cout<<endl;
}

int MyArray::getMycap()
{
    return mycap;
}

int MyArray::getMycur()
{
    return mycur;
}

void MyArray::change_elem(int elem1,int elem2)
{
    int t=find(elem1);
    if(t!=-1)
    {
        p[t]=elem2;
    }
    else
    {
        return;
    }
}

int main()
{
    MyArray a;
    for(int i=0;i<=20;i++)
    {
        a.push_back(i);
    }

    a.show();
    cout<<a.getMycap()<<endl;
    cout<<a.getMycur()<<endl;
    a.change_elem(2,3);
    a.show();
    return 0;
}