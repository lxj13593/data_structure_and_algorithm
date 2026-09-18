#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

double func(vector<pair<double, int>> p,double c,vector<int> w,vector<int> v)
{
    int index=0;
    double value=0;
    while(c>0)
    {
        if(w[p[index].second]<=c)
        {
            c-=w[p[index].second];
            value+=v[p[index].second];
            index++;
        }
        else
        {
            value+=c*p[index].first;
            c-=c;
        }
    }
    return value;
}

int main()
{
    vector<int> w{4, 6, 5, 8, 3, 7, 9, 2};
    vector<int> v{20, 30, 25, 32, 18, 35, 36, 12};
    double C = 25;
    vector<pair<double, int>> p;
    for(int i=0;i<w.size();i++)
    {
        p.push_back(pair<double, int>((v[i]*1.0)/(w[i]*1.0),i));
    }
    sort(p.begin(),p.end(),[](const pair<double, int> a,const pair<double, int> b){return a.first>b.first;});
    for(auto val:p)
    {
        cout<<val.first<<" "<<val.second<<endl;
    }
    cout<<func(p,C,w,v)<<endl;
    return 0;
}