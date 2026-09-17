#include<iostream>

using namespace std;

void shift_down(int *arr,int i,int size)
{
    int val=arr[i];
    while(i<size/2)
    {
        int child=2*i+1;
        if(child+1<size&&arr[child+1]>arr[child])
        {
            child=child+1;
        }
        if(arr[child]>val)
        {
            arr[i]=arr[child];
            i=child;
        }
        else
        {
            break;
        }
    }
    arr[i]=val;
}

void heap_sort(int *arr,int size)
{
    for(int i=(size-2)/2;i>=0;i--)
    {
        shift_down(arr,i,size);
    }
    for(int j=size-1;j>0;j--)
    {
        int t=arr[j];
        arr[j]=arr[0];
        arr[0]=t;
        shift_down(arr,0,j);
    }
}


void Shell_sort(int *arr, int n)
{
    for (int gap = n / 2; gap >= 1; gap = gap / 2)
    {
        for (int i = gap; i < n; i++)
        {
            int t = arr[i];
            int x = i-gap;
            for (; x >= 0; x-=gap)
            {
                if (arr[x] <= t)
                {
                    break;
                }
                arr[x + gap] = arr[x];
            }
            arr[x + gap] = t;
        }
    }
}

void merge(int *arr,int f,int mid,int l)
{
    int f1=f;
    int mid1=mid+1;
    int *arr1=new int[l-f+1];
    int k=0;
    while(f1<=mid&&mid1<=l)
    {
        if(arr[f1]>=arr[mid1])
        {
            arr1[k++]=arr[mid1++];
        }
        else
        {
            arr1[k++]=arr[f1++];
        }
    }
    while(f1<=mid)    
    {
        arr1[k++]=arr[f1++];
    }
    while(mid1<=l)
    {
        arr1[k++]=arr[mid1++];
    }
    for(int i=f,k1=0;i<=l;i++,k1++)
    {
        arr[i]=arr1[k1];
    }
    delete[] arr1;
}

void merge_sort(int *arr,int f,int l)
{
    if(f>=l)
    {
        return ;
    }
    int mid=(f+l)/2;
    merge_sort(arr,f,mid);
    merge_sort(arr,mid+1,l);
    merge(arr,f,mid,l);
}

void quick_sort(int *arr,int f,int l)
{
    if(f>=l)
    {
        return;
    } 
    int mark=arr[f];
    int f1=f;
    int l1=l;
    while(f1<l1)
    {
        while(f1<l1&&arr[l1]>=mark)
        {
            l1--;
        }
        arr[f1]=arr[l1];
        while(f1<l1&&arr[f1]<=mark)
        {
            f1++;
        }
        arr[l1]=arr[f1];
    }
    arr[f1]=mark;
    quick_sort(arr,f,f1-1);
    quick_sort(arr,f1+1,l);
}

int main()
{
    int count=10000000;
    int *a=new int[count];
    int *b=new int[count];
    int *c=new int[count];
    int *d=new int[count];

    srand(time(nullptr));

    for(int i=0;i<count;i++)
    {
        int val=rand()%10000+1;
        a[i]=val;
        b[i]=val;
        c[i]=val;
        d[i]=val;
    }

    clock_t c1,c2;
    c1=clock();
    quick_sort(a,0,count-1);
    c2=clock();
    cout<<"time:"<<(c2-c1)*1.0/CLOCKS_PER_SEC<<endl;
    c1=clock();
    merge_sort(b,0,count-1);
    c2=clock();
    cout<<"time:"<<(c2-c1)*1.0/CLOCKS_PER_SEC<<endl;
    c1=clock();
    Shell_sort(c,count);
    c2=clock();
    cout<<"time:"<<(c2-c1)*1.0/CLOCKS_PER_SEC<<endl;
    c1=clock();
    heap_sort(d,count);
    c2=clock();
    cout<<"time:"<<(c2-c1)*1.0/CLOCKS_PER_SEC<<endl;
    delete a;
    delete b;
    delete c;
    delete d;
    return 0;
}