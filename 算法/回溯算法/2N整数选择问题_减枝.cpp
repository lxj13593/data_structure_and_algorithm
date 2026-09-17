#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

// 给定2N个数字，从中选出N个数字，让这N个数字的和与剩下数字的和的差最小

vector<int> v{12, 7, 25, 4, 18, 31, 9, 16, 22, 11};
vector<int> x;
vector<int> best_x;
int min_ = INT_MAX;
int sum = 0;
int remain = accumulate(v.begin(), v.end(), 0);
int all_case = 0;

void fun(int i)
{
    if (i == v.size())
    {
        all_case++;
        if (x.size() != v.size() / 2)
        {
            return;
        }
        int diff = abs(sum - remain);
        if (diff < min_)
        {
            min_ = diff;
            best_x = x;
        }
    }
    else
    {
        if (x.size() < v.size() / 2)
        {
            sum += v[i];
            remain -= v[i];
            x.push_back(v[i]);
            fun(i + 1);
            sum -= v[i];
            remain += v[i];
            x.pop_back();
        }
        if((v.size()/2-x.size())<=(v.size()-i-1))
        {
            fun(i + 1);
        }
    }
}

int main()
{
    fun(0);
    cout << min_ << endl;
    for (int i = 0; i < best_x.size(); i++)
    {
        cout << best_x[i] << " ";
    }
    cout << endl;
    cout << all_case << endl;
    return 0;
}