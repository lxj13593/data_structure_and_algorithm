#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

bool binary_search(vector<int> &v,int l,int h,int val)
{
    if(l>h)
    {
        return false;
    }
    else
    {
        int mid=(l+h)/2;
        if(v[mid]>val)
        {
            return binary_search(v,l,mid-1,val);
        }
        else if(v[mid]<val)
        {
            return binary_search(v,mid+1,h,val);
        }
        else
        {
            return true;
        }
    }
}

void test_1()
{
    vector<int> v{3, 7, 12, 18, 24, 31, 39, 46, 55, 68};
    cout<<binary_search(v,0,v.size()-1,46)<<endl;
}

int main()
{
    test_1();
    return 0;
}