#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int max_sum(vector<int> &v,vector<int> &dp)
{
    dp[0]=v[0];
    int max_=dp[0];
    for(int i=1;i<dp.size();i++)
    {
        dp[i]=max(v[i],dp[i-1]+v[i]);
        if(dp[i]>max_)
        {
            max_=dp[i];
        }
    }
    return max_;
}

int main()
{
    vector<int> v{-2,11,-4,13,-5,-2};
    vector<int> dp(v.size(),0);
    cout<<max_sum(v,dp)<<endl;
    return 0;
}