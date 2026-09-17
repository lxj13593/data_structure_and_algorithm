#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

// 给定一组数字，从里面挑出一些数字，是使得他们的和为指定值，有的话打印，没有的话不打印

vector<int> v{8, 3, 11, 6, 14, 5, 9, 2};
vector<int> x;
int target = 20;
int all_case;
int sum=0;

void fun(int i)
{
    if (i == v.size())
    {
        all_case++;
        if (sum == target)
        {
            for_each(x.begin(), x.end(), [](int val)
                     { cout << val << " "; });
            cout << endl;
        }
    }
    else
    {
        vector<int> v1;
        vector<int> v2;
        for (int j = i; j < v.size(); j++)
        {
            if (v[j] > 0)
            {
                v1.push_back(v[j]);
            }
            if (v[j] < 0)
            {
                v2.push_back(v[j]);
            }
        }
        int sum1 = accumulate(v1.begin(), v1.end(), 0);
        int sum2 = accumulate(v2.begin(), v2.end(), 0);
        if (sum+sum2 <= target && target <= sum+sum1)
        {
            sum+=v[i];
            x.push_back(v[i]);
            fun(i + 1);
            x.pop_back();
            sum-=v[i];
            fun(i + 1);
        }
    }
}

int main()
{
    fun(0);
    cout<<all_case<<endl;
    return 0;
}