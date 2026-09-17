#include<iostream>

using namespace std;

int binary_search(int *arr,int size,int val)
{
    int first=0;
    int last=size-1;
    while(first<=last)
    {
        int mid=(first+last)/2;
        if(arr[mid]==val)
        {
            return mid+1;
        }
        if(arr[mid]>val)
        {
            last=mid-1;
        }
        if(arr[mid]<val)
        {
            first=mid+1;
        }
    }
    throw "no aim";
}

int binary_search_d(int *arr,int f,int l,int val)
{
    if(f>l)
    {
        return -1;
    }
    int mid=(f+l)/2;
    if(arr[mid]==val)
    {
        return mid+1;
    }
    else if(arr[mid]>val)
    {
        return binary_search_d(arr,f,mid-1,val);
    }
    else
    {
        return binary_search_d(arr,mid+1,l,val);
    }

}

int main()
{
    int arr[]={10,20,30,40,50,60,70,80,90};
    cout<<binary_search(arr,9,30);
    cout<<binary_search_d(arr,0,8,80);
    return 0;
}

