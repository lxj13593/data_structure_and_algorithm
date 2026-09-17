#include<iostream>

using namespace std;


void Shell_sort(int *arr, int n)
{
    for (int gap = n / 2; gap >= 1; gap = gap / 2)
    {
        for (int i = gap; i < n; i++)
        {
            int t = arr[i];
            int x = i-gap;
            for (; x >= 0; x-=gap)
            {
                if (arr[x] <= t)
                {
                    break;
                }
                arr[x + gap] = arr[x];
            }
            arr[x + gap] = t;
        }
    }
}

void bubble_sort(int *arr,int n)
{
    for(int i=0;i<n-1;i++)
    {
        int flag=0;
        for(int j=0;j<n-i-1;j++)
        {
            if(arr[j]>arr[j+1])
            {
                int t=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=t;
                flag=1;
            }   
        }
        if(flag==0)
        {
            break;
        }
    }
}

void select_sort(int *arr,int n)
{
    for(int i=0;i<n-1;i++)
    {
        int min=arr[i];
        int t=i;
        for(int j=i+1;j<n;j++)
        {
            if(arr[j]<min)
            {
                min=arr[j];
                t=j;
            }
        }
        if(t!=i)
        {
            int x=arr[i];
            arr[i]=arr[t];
            arr[t]=x;
        }
    }
}

void insert_sort(int *arr,int n)
{
    for(int i=0;i<n-1;i++)
    {
        int t=arr[i+1];
        int x=i;
        for(;x>=0;x--)
        {
            if(arr[x]<=t)
            {
                break;
            }
            arr[x+1]=arr[x];
        }
        arr[x+1]=t;
    }
}


int main()
{
    int count=100000;
    int *a=new int[count];
    int *b=new int[count];
    int *c=new int[count];
    int *d=new int[count];

    srand(time(nullptr));

    for(int i=0;i<count;i++)
    {
        int val=rand()%100000+1;
        a[i]=val;
        b[i]=val;
        c[i]=val;
        d[i]=val;
    }

    clock_t c1,c2;
    c1=clock();
    bubble_sort(a,count);
    c2=clock();
    cout<<"time:"<<(c2-c1)*1.0/CLOCKS_PER_SEC<<endl;
    c1=clock();
    select_sort(b,count);
    c2=clock();
    cout<<"time:"<<(c2-c1)*1.0/CLOCKS_PER_SEC<<endl;
    c1=clock();
    insert_sort(c,count);
    c2=clock();
    cout<<"time:"<<(c2-c1)*1.0/CLOCKS_PER_SEC<<endl;
    c1=clock();
    Shell_sort(d,count);
    c2=clock();
    cout<<"time:"<<(c2-c1)*1.0/CLOCKS_PER_SEC<<endl;
    delete a;
    delete b;
    delete c;
    delete d;
    return 0;
}