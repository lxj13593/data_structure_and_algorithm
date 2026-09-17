#include <iostream>

using namespace std;

void merge(int *arr,int f,int mid,int l)
{
    int f1=f;
    int mid1=mid+1;
    int *arr1=new int[l-f+1];
    int k=0;
    while(f1<=mid&&mid1<=l)
    {
        if(arr[f1]>=arr[mid1])
        {
            arr1[k++]=arr[mid1++];
        }
        else
        {
            arr1[k++]=arr[f1++];
        }
    }
    while(f1<=mid)    
    {
        arr1[k++]=arr[f1++];
    }
    while(mid1<=l)
    {
        arr1[k++]=arr[mid1++];
    }
    for(int i=f,k1=0;i<=l;i++,k1++)
    {
        arr[i]=arr1[k1];
    }
    delete[] arr1;
}

void merge_sort(int *arr,int f,int l)
{
    if(f>=l)
    {
        return ;
    }
    int mid=(f+l)/2;
    merge_sort(arr,f,mid);
    merge_sort(arr,mid+1,l);
    merge(arr,f,mid,l);
}

int main()
{
    int arr[10];
    srand(time(nullptr));
    for (int i = 0; i < 10; i++)
    {
        arr[i] = rand() % 100 + 1;
    }
    for (int v : arr)
    {
        cout << v << " ";
    }
    cout << endl;
    merge_sort(arr, 0,9);
    for (int v : arr)
    {
        cout << v << " ";
    }
    cout << endl;
}