#include<iostream>

using namespace std;

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
    select_sort(arr,10);
    for(int v:arr)
    {
        cout<<v<<" ";
    }
    cout<<endl;
}