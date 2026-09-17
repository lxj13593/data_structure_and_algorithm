#include<iostream>
#include<vector>

using namespace std;

//给定N个数字，从中选出一部分，让这部分的和和剩下的和的差最小

int sum=0;
int remain=0;
vector<int> x;
vector<int> best_x;

void func(vector<int> v,int i,int length,int &min)
{
    if(i==length)
    {
        int diff=abs(sum-remain);
        if(diff<min)
        {
            min=diff;
            best_x=x;
        }
    }
    else
    {
        sum+=v[i];
        remain-=v[i];
        x.push_back(v[i]);
        func(v,i+1,length,min);
        sum-=v[i];
        remain+=v[i];
        x.pop_back();
        func(v,i+1,length,min);
    }
} 

int main()
{
    vector<int> v{1,2,3};
    int t=999999;
    for(int i=0;i<v.size();i++)
    {
        remain+=v[i];
    }
    func(v,0,v.size(),t);
    cout<<t<<endl;
    for(int i=0;i<best_x.size();i++)
    {
        cout<<best_x[i]<<" ";
    }
    cout<<endl;
    return 0;
}