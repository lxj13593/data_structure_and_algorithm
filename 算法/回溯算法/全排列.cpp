#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

vector<int> v{1,2,3,4};

void func(int i)
{
    if(i==v.size()-1)
    {
        for_each(v.begin(),v.end(),[](int val){cout<<val<<" ";});
        cout<<endl;
    }
    else
    {
        for(int k=i;k<v.size();k++)
        {
            swap(v[i],v[k]);
            func(i+1);
            swap(v[i],v[k]);
        }
    }
}

int main()
{
    func(0);
    return 0;
}