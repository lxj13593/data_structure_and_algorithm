#include<iostream>

using namespace std;

void insert_sort(int *arr,int n)
{
    for(int i=0;i<n-1;i++)
    {
        int t=arr[i+1];
        int x=i;
        while(x>=0&&t<arr[x])
        {
            x--;
        }
        for(int j=i;j>=x+1;j--)
        {
            arr[j+1]=arr[j];
        }
        arr[x+1]=t;
    }
}

void insert_sort_1(int *arr,int n)
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
    int arr[10];
    srand(time(nullptr));
    for(int i=0;i<10;i++)
    {
        arr[i]=rand()%100+1;
    }
    for(int v:arr)
    {
        cout<<v<<" ";
    }
    cout<<endl;
    insert_sort_1(arr,10);
    for(int v:arr)
    {
        cout<<v<<" ";
    }
    cout<<endl;
}