#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int func(vector<int> w, vector<int> v, vector<vector<int>> &dp, int c)
{
    for (int i = 1; i <= w.size(); i++)
    {
        for (int j = 1; j <= c; j++)
        {
            if (w[i - 1] > j)
            {
                dp[i][j] = dp[i - 1][j];
            }
            else
            {
                int a = dp[i - 1][j];
                int b = dp[i - 1][j - w[i - 1]] + v[i - 1];
                dp[i][j] = max(a, b);
            }
        }
    }
    return dp[w.size()][c];
}

vector<int> select_item(vector<vector<int>> dp, int num, int c, vector<int> w)
{
    vector<int> v;
    int i = num;
    int j = c;
    while (i >= 1)
    {
        if (dp[i][j] > dp[i - 1][j])
        {
            v.push_back(i);
            j -= w[i-1];
            i--;
        }
        else
        {
            i--;
        }
    }
    return v;
}

int main()
{
    vector<int> w{2, 5, 4, 3};
    vector<int> v{6, 10, 8, 7};
    int C = 9;
    vector<vector<int>> dp(w.size() + 1, vector<int>(C + 1, 0));
    cout << func(w, v, dp, C) << endl;
    cout << "\t";
    for (int i = 0; i < C + 1; i++)
    {
        cout << i << "\t";
    }
    cout << endl;
    int i = 0;
    for (auto val : dp)
    {
        cout << i++ << "\t";
        for (auto val1 : val)
        {
            cout << val1 << "\t";
        }
        cout << endl;
    }
    vector<int> v1=select_item(dp,w.size(),C,w);
    for(int val:v1)
    {
        cout<<val<<" ";
    }
    cout<<endl;
    return 0;
}