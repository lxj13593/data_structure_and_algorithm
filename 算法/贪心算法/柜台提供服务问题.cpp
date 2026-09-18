#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

struct Counter
{
    int id;
    int time;
    int number;
    Counter(int id,int time,int number):id(id),time(time),number(number){};
    bool operator<(const Counter &other)
    {
        return time<other.time;
    }
};

int min_time(vector<Counter> v,int n)
{
    int min_time;
    int min_index;
    for(int i=0;i<n;i++)
    {
        min_time=v[0].time*(v[0].number+1);
        min_index=0;
        for(int j=1;j<v.size();j++)
        {
            int t=v[j].time*(v[j].number+1);
            if(t<min_time)
            {
                min_time=t;
                min_index=j;
            }
        }
        v[min_index].number++;
    }
    return min_time;
}

int main()
{
    vector<int> t{5, 4, 2, 7}; // 4个柜台，每服务1个人所需时间
    int n = 12;
    vector<Counter> counters;
    for (int i = 0; i < 4; i++)
    {
        counters.emplace_back(i + 1, t[i],0);
    }
    sort(counters.begin(),counters.end());
    cout<<min_time(counters,n)<<endl;
    return 0;
}