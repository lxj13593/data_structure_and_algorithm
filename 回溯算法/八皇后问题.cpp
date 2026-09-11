#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

// 还可以用全排列解决

int row=8;
int col=8;
int all_case=0;
int x[8]={0};

bool check(int row_,int col_)
{
    for(int i=0;i<row_;i++)
    {
        if(x[i]==col_)
        {
            return false;
        }
        if(abs(i-row_)==abs(x[i]-col_))
        {
            return false;
        }
    }
    return true;
}

void func(int i)
{
    if(i==row)
    {
        all_case++;
        for(int k=0;k<row;k++)
        {
            cout<<x[k]+1<<" ";
        }
        cout<<endl;
        return;
    }
    else
    {
        for(int j=0;j<col;j++)
        {
            if(check(i,j))
            {
                x[i]=j;
                func(i+1);
            }
        }
    }
}

int main()
{
    func(0);
    cout<<all_case<<endl;
    return 0;
}