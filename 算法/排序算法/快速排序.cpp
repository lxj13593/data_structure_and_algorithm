#include <iostream>

using namespace std;

void quick_sort(int *arr,int f,int l)
{
    if(f>=l)
    {
        return;
    } 
    int mark=arr[f];
    int f1=f;
    int l1=l;
    while(f1<l1)
    {
        while(f1<l1&&arr[l1]>=mark)
        {
            l1--;
        }
        arr[f1]=arr[l1];
        while(f1<l1&&arr[f1]<=mark)
        {
            f1++;
        }
        arr[l1]=arr[f1];
    }
    arr[f1]=mark;
    quick_sort(arr,f,f1-1);
    quick_sort(arr,f1+1,l);
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
    quick_sort(arr, 0,9);
    for (int v : arr)
    {
        cout << v << " ";
    }
    cout << endl;
}