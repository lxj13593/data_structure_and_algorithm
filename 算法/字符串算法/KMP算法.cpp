#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

vector<int> next_array(string b)
{
    vector<int> next(b.size(),0);
    next[0]=-1;
    int i=0;
    int k=-1;
    while(i<(int)b.size()-1)
    {
        if(k==-1||b[k]==b[i])
        {
            i++;
            k++;  
            if(b[i]==b[k])
            {
                next[i]=next[k];
            }
            else
            {
                next[i]=k;
            }
        }
        else
        {
            k=next[k];
        }
    }
    return next;
}
 
int func(string a,string b)
{
    int i=0;
    int j=0;
    vector<int> next=next_array(b);
    while(i<a.size()&&j<(int)b.size())
    {
        if(j==-1||a[i]==b[j])
        {
            i++;
            j++;
        }
        else
        {
            j=next[j];
        }
    }
    if(j==b.size())
    {
        return i-j;
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