#include <iostream>
using namespace std;

void reverse(char c[],int len)
{
    char *p=c;
    char *q=c+len-1;
    while(p<q)
    {
        char t=*p;
        *p=*q;
        *q=t;
        p++;
        q--;
    }
}

int main()
{
    char c[]="hello";
    cout<<c<<endl;
    reverse(c,5);
    cout<<c;
    return 0;
}