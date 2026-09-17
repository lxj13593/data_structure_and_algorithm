#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int lcs(string s1, string s2, int i, int j, vector<vector<int>> &dp,vector<vector<int>> &path1)
{
    if (i == -1 || j == -1)
    {
        return 0;
    }

    if (dp[i][j] != -1)
    {
        return dp[i][j];
    }

    if (s1[i] == s2[j])
    {
        path1[i][j]=1;
        dp[i][j] = lcs(s1, s2, i - 1, j - 1, dp,path1) + 1;
    }
    else
    {
        int a = lcs(s1, s2, i - 1, j, dp,path1);
        int b = lcs(s1, s2, i, j - 1, dp,path1);

        dp[i][j] = max(a, b);
        if(dp[i][j]==a)
        {
            path1[i][j]=2;
        }
        else
        {
            path1[i][j]=3;
        }
    }

    return dp[i][j];
}

int lcs_1(string s1, string s2,
          int length1, int length2,
          vector<vector<int>> &dp)
{
    for (int i = 1; i <= length1; i++)
    {
        for (int j = 1; j <= length2; j++)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else
            {
                dp[i][j] = max(dp[i - 1][j],
                               dp[i][j - 1]);
            }
        }
    }

    return dp[length1][length2];
}

string get_path(vector<vector<int>> path,int length1,int length2,string s1)
{
    string s;
    int i=length1-1;
    int j=length2-1;
    while(i>=0&&j>=0)
    {
        if(path[i][j]==1)
        {
            s.push_back(s1[i]);
            i--;
            j--;
        }
        else if(path[i][j]==2)
        {
            i--;
        }
        else if(path[i][j]==3)
        {
            j--;
        }
    }
    reverse(s.begin(), s.end());
    return s;
}

int main()
{
    string X = "ABCBDAB";
    string Y = "BDCABA";
    
    // 递归 + 路径
    vector<vector<int>> path1(
        X.size(),
        vector<int>(Y.size(), 0));


    // 递归 + 记忆化使用
    vector<vector<int>> dp1(
        X.size(),
        vector<int>(Y.size(), -1));

    // 循环 DP 使用
    vector<vector<int>> dp2(
        X.size() + 1,
        vector<int>(Y.size() + 1, 0));

    cout << lcs(X, Y,
                X.size() - 1,
                Y.size() - 1,
                dp1,path1)
         << endl;

    // cout << lcs_1(X, Y,
    //               X.size(),
    //               Y.size(),
    //               dp2)
    //      << endl;
    for(auto val:path1)
    {
        for(auto val1:val)
        {
            cout<<val1<<" ";
        }
        cout<<endl;
    }
    string s=get_path(path1,X.size(),Y.size(),X);
    cout<<s<<endl;
    return 0;
}