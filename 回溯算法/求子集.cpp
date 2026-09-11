#include<iostream>
#include<vector>

using namespace std;

void func(vector<int> v,int i,int length,int x[])
{
    if(i==length)
    {
        for(int j=0;j<length;j++)
        {
            if(x[j]==1)
            {
                cout<<v[j];
            }
        }
        cout<<endl;
    }
    else
    {
        x[i]=1;
        func(v,i+1,length,x);
        x[i]=0;
        func(v,i+1,length,x);
    }
} 

int main()
{
    vector<int> v{1,2,3};
    int x[]={0,0,0};
    func(v,0,v.size(),x);
    return 0;
}