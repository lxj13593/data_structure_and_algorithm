#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

// 用面值 1、3、5 的硬币组成金额 n，最少需要多少枚硬币。
const int n = 11;

int dp[n + 1] = {0};
int num = 0;

int func(int n)
{
    if (n < 0)
    {
        return INT_MAX / 2;
    }
    if (dp[n] > 0)
    {
        num++;
        return dp[n];
    }
    if (n == 0)
    {
        dp[n] = 0;
        return dp[n];
    }

    int n1 = func(n - 1) + 1;
    int n2 = func(n - 3) + 1;
    int n3 = func(n - 5) + 1;
    dp[n] = min(min(n1, n2), n3);
    return dp[n];
}

int main()
{
    cout << func(n) << endl;
    cout << num << endl;
    return 0;
}