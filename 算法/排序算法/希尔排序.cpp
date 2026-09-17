#include <iostream>

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
    Shell_sort(arr, 10);
    for (int v : arr)
    {
        cout << v << " ";
    }
    cout << endl;
}