#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

// 递归
int func(vector<vector<int>> &v, int i, int j)
{
    if (i >= v.size())
    {
        return 0;
    }
    return v[i][j] + min(func(v, i + 1, j), func(v, i + 1, j + 1));
}

// 动态规划
int func_1(vector<vector<int>> &v, vector<vector<int>> &dp, int i, int j)
{
    if (i >= v.size())
    {
        return 0;
    }
    if (dp[i][j] != 0)
    {
        return dp[i][j];
    }
    dp[i][j] = v[i][j] + min(func_1(v,dp, i + 1, j), func_1(v, dp,i + 1, j + 1));
    return dp[i][j];
}

//求具体路径
vector<int> func_2(vector<vector<int>> &dp,vector<vector<int>> &v)
{
    vector<int> v1;
    v1.push_back(v[0][0]);
    int j=0;
    for(int i=0;i<dp.size()-1;i++)
    {
        int val=dp[i][j]-v[i][j];
        if(dp[i+1][j]==val)
        {
            v1.push_back(v[i+1][j]);
        }
        else
        {
            v1.push_back(v[i+1][j+1]);
            j++;
        }
    }
    return v1;
}

int main()
{
    vector<vector<int>> v{
        {2},
        {3, 4},
        {6, 5, 7},
        {4, 1, 8, 3}};
    vector<vector<int>> dp(v.size());
    for (int i = 0; i < v.size(); i++)
    {
        dp[i] = vector<int>(v[i].size(), 0);
    }
    // cout<<func(v,0,0)<<endl;
    cout << func_1(v, dp, 0, 0) << endl;
    for(auto val:dp)
    {
        for(auto val1:val)
        {
            cout<<val1<<" ";
        }
        cout<<endl;
    }
    vector<int> v1=func_2(dp,v);
    for(int val:v1)
    {
        cout<<val<<" ";
    }
    cout<<endl;
    return 0;
}