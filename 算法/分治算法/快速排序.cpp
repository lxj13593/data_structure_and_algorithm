#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int process_(vector<int> &v,int l,int h)
{
    int x=v[l];
    int l1=l;
    int h1=h;
    while(l1<h1)
    {
        while(l1<h1&&v[h1]>=x)
        {
            h1--;
        }
        if(l1<h1)
        {
            v[l1]=v[h1];
        }
        while(l1<h1&&v[l1]<=x)
        {
            l1++;
        }
        if(l1<h1)
        {
            v[h1]=v[l1];
        }
    }
    v[l1]=x;
    return l1;
}

void quick_sort(vector<int> &v,int l,int h)
{
    if(l>=h)
    {
        return;
    }
    else
    {
        int t=process_(v,l,h);
        quick_sort(v,l,t-1);
        quick_sort(v,t+1,h);
    }
}

void test_1()
{
    vector<int> v{42, 17, 8, 63, 29, 51, 14, 76, 35, 22};
    quick_sort(v,0,v.size()-1);
    for_each(v.begin(),v.end(),[](int val){cout<<val<<" ";});
    cout<<endl;
}

int main()
{
    test_1();
    return 0;
}