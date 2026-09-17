#include<iostream>

using namespace std;

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
    bubble_sort(arr,10);
    for(int v:arr)
    {
        cout<<v<<" ";
    }
    cout<<endl;
    return 0;
}