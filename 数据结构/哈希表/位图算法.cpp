#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstdint>

using namespace std;

// 有1亿个整数，最大值不超过1亿，问都有哪些元素重复了？谁是第一个重复的？谁是第一个不重复的(1个位保存数据的状态，2个位保存数据的状态)？ 内存限制100M

void find_repeat_number(const vector<int> &v)
{
    vector<int> bitmap;
    bitmap.resize(100000000/32+1);
    for(auto &val:v)
    {
        int index=val/32;
        int offset=val%32;
        if((bitmap[index]&(1u<<offset))==0)
        {
            bitmap[index]|=(1u<<offset);
        }
        else
        {
            cout<<val<<" ";
            // break;
        }
    }
    cout<<endl;
}

void find_first_repeat_number(const vector<int> &v)
{
    vector<int> bitmap;
    bitmap.resize(100000000/32+1);
    for(auto &val:v)
    {
        int index=val/32;
        int offset=val%32;
        if((bitmap[index]&(1u<<offset))==0)
        {
            bitmap[index]|=(1u<<offset);
        }
        else
        {
            cout<<val<<" ";
            break;
        }
    }
    cout<<endl;
}

void find_repeat_number_and_print_one_time(const vector<int> &v)
{
    vector<uint32_t> bitmap;
    vector<uint32_t> bitmap_1;
    bitmap.resize(100000000/32+1);
    bitmap_1.resize(100000000/32+1);
    for(auto &val:v)
    {
        int index=val/32;
        int offset=val%32;
        if((bitmap[index]&(1u<<offset))==0&&(bitmap_1[index]&(1u<<offset))==0)
        {
            bitmap[index]|=(1u<<offset);
        }
        else if((bitmap[index]&(1u<<offset))!=0&&(bitmap_1[index]&(1u<<offset))==0)
        {
            bitmap_1[index]|=(1u<<offset);
            cout<<val<<" ";
        }
    }
    cout<<endl;
}

void find_first_no_repeat(const vector<int> &v)
{
    vector<uint32_t> bitmap;
    vector<uint32_t> bitmap_1;
    bitmap.resize(100000000/32+1);
    bitmap_1.resize(100000000/32+1);
    for(auto &val:v)
    {
        int index=val/32;
        int offset=val%32;
        if((bitmap[index]&(1u<<offset))==0&&(bitmap_1[index]&(1u<<offset))==0)
        {
            bitmap[index]|=(1u<<offset);
        }
        else if((bitmap[index]&(1u<<offset))!=0&&(bitmap_1[index]&(1u<<offset))==0)
        {
            bitmap_1[index]|=(1u<<offset);
        }
    }
    for(auto &val:v)
    {
        int index=val/32;
        int offset=val%32;
        if((bitmap[index]&(1u<<offset))!=0&&(bitmap_1[index]&(1u<<offset))==0)
        {
            cout<<val;
            break;
        }
    }
}

int main()
{
    return 0;
}