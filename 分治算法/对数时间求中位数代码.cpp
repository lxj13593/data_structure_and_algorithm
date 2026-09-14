#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

double log_mid_number(vector<int> &v1, vector<int> &v2,
                      int l, int h, int half)
{
    if (l > h)
    {
        return -1;
    }

    int x = (l + h) / 2;   // v1 左边取 x 个元素
    int y = half - x;      // v2 左边取 y 个元素

    int left1;
    int right1;
    int left2;
    int right2;

    // v1 左边
    if (x == 0)
        left1 = INT_MIN;
    else
        left1 = v1[x - 1];

    // v1 右边
    if (x == v1.size())
        right1 = INT_MAX;
    else
        right1 = v1[x];

    // v2 左边
    if (y == 0)
        left2 = INT_MIN;
    else
        left2 = v2[y - 1];

    // v2 右边
    if (y == v2.size())
        right2 = INT_MAX;
    else
        right2 = v2[y];

    // 找到正确分割位置
    if (left1 <= right2 && left2 <= right1)
    {
        if ((v1.size() + v2.size()) % 2 == 0)
        {
            return (max(left1, left2)
                  + min(right1, right2)) / 2.0;
        }
        else
        {
            return max(left1, left2);
        }
    }

    // v1 左边太大，分割位置往左
    if (left1 > right2)
    {
        return log_mid_number(v1, v2, l, x - 1, half);
    }

    // v1 左边太小，分割位置往右
    return log_mid_number(v1, v2, x + 1, h, half);
}

double find_mid_number(vector<int> &v1, vector<int> &v2)
{
    // 保证在较短数组上二分
    if (v1.size() > v2.size())
    {
        return find_mid_number(v2, v1);
    }

    int half = (v1.size() + v2.size() + 1) / 2;

    return log_mid_number(v1, v2,
                          0,
                          v1.size(),
                          half);
}

int main()
{
    vector<int> v1{2, 5, 9, 14, 20};
    vector<int> v2{1, 4, 7, 11, 16};

    cout << find_mid_number(v1, v2) << endl;

    return 0;
}