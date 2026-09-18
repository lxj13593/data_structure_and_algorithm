#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int func(vector<int> v,int target)
{
    int num=0;
    for(int i=0;i<v.size();)
    {
        if(target>=v[i])
        {
            num++;
            target-=v[i];
        }
        else
        {
            i++;
        }
    }
    return target==0?num:-1;
}

int main()
{
    vector<int> v{1,3,5};
    sort(v.begin(),v.end(), greater<int>());
    int target=11;
    cout<<func(v,target)<<endl;
    return 0;
}