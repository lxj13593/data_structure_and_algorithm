#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

// 回朔
void func(vector<int> w,int i,int c1,int c2,vector<int> &a,vector<int> &b,int &num) 
{
    if(i==w.size())
    {
        int wa=accumulate(a.begin(),a.end(),0);
        int wb=accumulate(b.begin(),b.end(),0);
        if(wa<=c1&&wb<=c2)
        {
            num++;
            for(auto val:a)
            {
                cout<<val<<" ";
            }
            cout<<endl;
            for(auto val:b)
            {
                cout<<val<<" ";
            }
            cout<<endl;
            cout<<endl;
        }
        return;
    }
    a.push_back(w[i]);
    func(w,i+1,c1,c2,a,b,num);
    a.pop_back();
    b.push_back(w[i]);
    func(w,i+1,c1,c2,a,b,num);
    b.pop_back();
}

int main()
{
    vector<int> w{8, 5, 12, 7, 4, 9, 6, 10};
    vector<int> c1_case;
    vector<int> c2_case;
    int c1 = 32;
    int c2 = 30;
    int num=0;
    func(w,0,c1,c2,c1_case,c2_case,num);
    cout<<num<<endl;
    return 0;
}