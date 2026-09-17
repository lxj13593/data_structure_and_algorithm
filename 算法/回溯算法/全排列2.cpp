#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

vector<int> v{1,2,3};
vector<int> v1;
vector<int> state(3,0);

void func(int i,int length)
{
    if(i==length)
    {
        for_each(v1.begin(),v1.end(),[](int val){cout<<val<<" ";});
        cout<<endl;
    }
    else
    {
        for(int j=0;j<length;j++)
        {
            if(state[j]==0)
            {
                state[j]=1;
                v1.push_back(v[j]);
                func(i+1,length);
                v1.pop_back();
                state[j]=0;
            }
        }
    }
}

int main()
{
    func(0,v.size());
    return 0;
}