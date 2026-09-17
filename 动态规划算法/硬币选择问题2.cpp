#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

void func(int n,int *dp,int v[])
{
    for(int i=1;i<n+1;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(i>=v[j])
            {
                if(1+dp[i-v[j]]<dp[i])
                {
                    dp[i]=1+dp[i-v[j]];
                }
            }
        }
    }
}

int main()
{
    int n = 11;
    int v[3]={1,3,5};
    int *dp = new int[n + 1];
    for (int i = 0; i < n + 1; i++)
    {
        dp[i] = i;
    }
    func(n,dp,v);
    cout<<dp[n]<<endl;
    delete[] dp;
    return 0;
}