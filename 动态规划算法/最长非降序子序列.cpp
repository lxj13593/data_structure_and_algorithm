#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

vector<int> func(vector<int> &v,vector<vector<int>> &dp)
{
    dp[0].push_back(v[0]);
    int max_=dp[0].size();
    int t=0;
    for(int i=1;i<dp.size();i++)
    {
        int max_before=0;
        int index=-1;
        for(int j=0;j<i;j++)
        {
            if(v[j]<v[i])
            {
                if(dp[j].size()>max_before)
                {
                    max_before=dp[j].size();
                    index=j;
                }
            }
        }
        if(index!=-1)
        {
            dp[i]=dp[index];
        }
        dp[i].push_back(v[i]);
        if(dp[i].size()>max_)
        {
            max_=dp[i].size();
            t=i;
        }
    }
    return dp[t];
}

int main()
{
    vector<int> v{10, 9, 2, 5, 3, 7, 101, 18};
    vector<vector<int>> dp(v.size()); 
    vector<int> max_=func(v,dp);
    for_each(max_.begin(),max_.end(),[](int val){cout<<val<<" ";});
    cout<<endl;
    return 0;
}