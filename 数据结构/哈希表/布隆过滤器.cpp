#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
#include "stringhash.h"

using namespace std;

class BloomFilters
{
public:
    BloomFilters(int bit_size = 1471) : bit_size(bit_size), bit_vector(bit_size / 32 + 1)
    {
    }
    void insert(const char *s)
    {
        int id1 = BKDRHash(s) % bit_size;
        int id2 = PJWHash(s) % bit_size;
        int id3 = ELFHash(s) % bit_size;

        int index1 = id1 / 32;
        int offset1 = id1 % 32;
        bit_vector[index1] |= (1u << offset1);

        int index2 = id2 / 32;
        int offset2 = id2 % 32;
        bit_vector[index2] |= (1u << offset2);

        int index3 = id3 / 32;
        int offset3 = id3 % 32;
        bit_vector[index3] |= (1u << offset3);
    }

    bool query(const char *s)
    {
        int id1 = BKDRHash(s) % bit_size;
        int id2 = PJWHash(s) % bit_size;
        int id3 = ELFHash(s) % bit_size;

        int index1 = id1 / 32;
        int offset1 = id1 % 32;

        int index2 = id2 / 32;
        int offset2 = id2 % 32;

        int index3 = id3 / 32;
        int offset3 = id3 % 32;

        int flag1 = bit_vector[index1] & (1u << offset1);
        int flag2 = bit_vector[index2] & (1u << offset2);
        int flag3 = bit_vector[index3] & (1u << offset3);
        if (flag1 != 0 && flag2 != 0 && flag3 != 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

private:
    int bit_size;
    vector<int> bit_vector;
};

class MaliciousWebsite
{
public:
    void insert(const char *s)
    {
        bloom_filters.insert(s);
    }
    bool query(const char *s)
    {
        return bloom_filters.query(s);
    }

private:
    BloomFilters bloom_filters;
};

void test_1()
{
    MaliciousWebsite mw;
    const char *s[] = {
        "https://www.google.com",
        "https://www.bilibili.com",
        "https://www.github.com",
        "https://www.zhihu.com",
        "https://www.openai.com"};
    for(int i=0;i<sizeof(s)/sizeof(s[0]);i++)
    {
        mw.insert(s[i]);
    }
    cout<<mw.query(s[0])<<endl;
    cout<<mw.query(s[1])<<endl;
    cout<<mw.query(s[2])<<endl;
    cout<<mw.query(s[3])<<endl;
    cout<<mw.query(s[4])<<endl;
    cout<<mw.query("https://chatgpt.com/c/6a47a102-19e4-83ec-89aa-fda8c728afe8")<<endl;
}

int main()
{
    test_1();
    return 0;
}