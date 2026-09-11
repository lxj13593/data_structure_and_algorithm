#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

vector<int> v{8, 3, 11, 6, 14, 5, 9, 2};
vector<int> x;
int target = 20;
int sum = 0;

void func(int i)
{
    if (sum == target)
    {
        for_each(x.begin(), x.end(), [](int val)
                 { cout << val << " "; });
        cout << endl;
    }
    else
    {
        for (int k = i; k < v.size(); k++)
        {
            if (sum + v[k] <=target)
            {
                sum += v[k];
                x.push_back(v[k]);
                func(k + 1);
                x.pop_back();
                sum -= v[k];
            }
        }
    }
}

int main()
{
    func(0);
    return 0;
}