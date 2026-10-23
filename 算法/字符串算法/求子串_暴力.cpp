#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int func(string a,string b)
{
    int i=0;
    while(i<=a.size()-b.size())
    {
        int j=0;
        int t=i;
        while(j<b.size()&&a[i]==b[j])
        {
            i++;
            j++;
        }
        if(j==b.size())
        {
            return i-b.size();
        }
        i=t+1;
    }
    return -1;
}

int main()
{
    string a="ABCDCABDEFG";
    string b="ABD";
    cout<<func(a,b)<<endl;
    return 0;
}