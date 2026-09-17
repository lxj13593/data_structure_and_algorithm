#include<iostream>

using namespace std;

void shift_down(int *arr,int i,int size)
{
    int val=arr[i];
    while(i<size/2)
    {
        int child=2*i+1;
        if(child+1<size&&arr[child+1]>arr[child])
        {
            child=child+1;
        }
        if(arr[child]>val)
        {
            arr[i]=arr[child];
            i=child;
        }
        else
        {
            break;
        }
    }
    arr[i]=val;
}

void heap_sort(int *arr,int size)
{
    for(int i=(size-2)/2;i>=0;i--)
    {
        shift_down(arr,i,size);
    }
    for(int j=size-1;j>0;j--)
    {
        int t=arr[j];
        arr[j]=arr[0];
        arr[0]=t;
        shift_down(arr,0,j);
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
    for(int i=0;i<10;i++)
    {
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    heap_sort(arr,10);
    for(int i=0;i<10;i++)
    {
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    return 0;
}