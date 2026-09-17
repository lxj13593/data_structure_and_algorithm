#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int func(int n)
{
    if(n==1)
    {
        return 1;
    }
    if(n==0)
    {
        return 0;
    }
    return func(n-1)+func(n-2);
}

int func1(int n,int *dp)
{
    dp[0]=0;
    dp[1]=1;
    for(int i=2;i<=n;i++)
    {
        dp[i]=dp[i-1]+dp[i-2];
    }
    return dp[n];
}


int func2(int n,int *dp)
{
    if(dp[n]>=0)
    {
        return dp[n];
    }
    if(n==1)
    {
        dp[1]=1;
        return dp[1];
    }
    if(n==0)
    {
        dp[0]=0;
        return dp[0];
    }
    dp[n-1]=func2(n-1,dp);
    dp[n-2]=func2(n-2,dp);
    dp[n]=dp[n-1]+dp[n-2];
    return dp[n];
}

int main()
{
    int n=15;
    int *dp=new int[n+1];
    for(int i=0;i<n+1;i++)
    {
        dp[i]=-1;
    }
    cout<<func2(n,dp)<<endl;
    return 0;
}