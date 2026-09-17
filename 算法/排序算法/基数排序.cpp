
#include <iostream>
#include<vector>

using namespace std;

int max_(int *arr,int size)
{
    int max=arr[0];
    for(int i=0;i<size;i++)
    {
        if(abs(arr[i])>max)
        {
            max=abs(arr[i]);
        }
    }
    return max;
}

void radix_sort(int *arr,int size)
{
    int max=max_(arr,size);
    vector<vector<int>> v1(20);
    int i=0;
    while(max>0)
    {
        max=max/10;
        i++;
    }
    int a=10;
    int b=1;
    for(int j=i;j>0;j--,a=a*10,b=b*10)
    {
        for(int k=0; k<20; k++) v1[k].clear(); 

        for(int k=0;k<size;k++)
        {
            int val=(arr[k]%a)/b+10;
            v1[val].push_back(arr[k]);
        }
        
        int k1=0;
        for(int i=0;i<v1.size();i++)
        {
            for(int j=0;j<v1[i].size();j++)
            {
                arr[k1]=v1[i][j];
                k1++;
            } 
        }
    }
}

int main()
{
    int arr[10];
    srand(time(nullptr));
    for (int i = 0; i < 10; i++)
    {
        arr[i] = rand() % 100 + 1-30;
    }
    for (int v : arr)
    {
        cout << v << " ";
    }
    cout << endl;
    radix_sort(arr, 10);
    for (int v : arr)
    {
        cout << v << " ";
    }
    cout << endl;
}