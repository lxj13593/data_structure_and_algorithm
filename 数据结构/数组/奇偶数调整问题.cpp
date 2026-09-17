#include <iostream>
using namespace std;

void two_before_one(int a[],int len)
{
    int *p=a;
    int *q=a+len-1;
    while(p<q)
    {
        while(p<q&&*p%2==0)
        {
            p++;
        }
        while(p<q&&*q%2!=0)
        {
            q--;            
        }
        if(p<q)
        {
            int t=*p;
            *p=*q;
            *q=t;
            p++;
            q--;
        }
    }
}

int main()
{
    int a[10]={0};
    srand(time(nullptr));
    for(int i=0;i<10;i++)
    {
        a[i]=rand()%100;
    }
    for(int i=0;i<10;i++)
    {
        cout<<a[i]<<' ';
    }
    cout<<endl;
    two_before_one(a,10);
    for(int i=0;i<10;i++)
    {
        cout<<a[i]<<' ';
    }
    cout<<endl;
    return 0;
}