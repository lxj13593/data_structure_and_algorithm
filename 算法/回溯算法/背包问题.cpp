#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

vector<int> w{2, 5, 7, 3, 6, 4, 9, 8};
vector<int> v{6, 10, 13, 7, 12, 8, 16, 15};
int vs = accumulate(v.begin(), v.end(), 0);

int n = 8;
int C = 20; // 背包容量
int w_ = 0;
int v_ = 0;
int max_ = 0;
vector<int> x;
vector<int> best_x;
int all_case = 0;

void func(int i)
{
    if (i == n)
    {
        all_case++;
        if (w_ <= C)
        {
            if (v_ > max_)
            {
                max_ = v_;
                best_x = x;
            }
        }
    }
    else
    {
        vs -= v[i];
        if (w_ + w[i] <= C)
        {
            w_ += w[i];
            v_ += v[i];
            x.push_back(i + 1);
            func(i + 1);
            v_ -= v[i];
            w_ -= w[i];
            x.pop_back();
        }
        if (vs + v_ >= max_)
        {
            func(i + 1);
        }
        vs += v[i];
    }
}

int main()
{
    func(0);
    for_each(best_x.begin(), best_x.end(), [](int val)
             { cout << val << " "; });
    cout << endl;
    cout << max_;
    cout << endl;
    cout << all_case << endl;
    return 0;
}