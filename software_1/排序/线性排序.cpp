#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <stdio.h>
#define N 30000
using namespace std;

struct LIST
{
    int key;
};

struct Queue
{
    struct LIST t[N];
    int f=0;
    int l=0;
};

void Swap(struct LIST &a,struct LIST &b)
{
    struct LIST tem;
    tem=a;
    a=b;
    b=tem;
}

void bubble_sort(int n,struct LIST S[])
{
    int i,j;
    for(i=0;i<n-1;i++)
    {
        for(j=n-1;j>i;j--)
        {
            if(S[j].key<S[j-1].key)
            {
                Swap(S[j],S[j-1]);
            }
        }
    }
}

void counting_sort(int n,struct LIST S[])
{
    int i,tem[N],c[N];
    //struct LIST A[N+1];
    for(i=0;i<N;i++)
    {
        tem[i]=0;
    }
    for(i=0;i<N;i++)
    {
        tem[S[i].key]++;
    }
    for(i=1;i<n;i++)
    {
        tem[i]+=tem[i-1];
    }
    for(i=0;i<N;i++)
    {
        tem[S[i].key]--;
        c[tem[S[i].key]]=S[i].key;
        //tem[S[i].key]--;
    }
    /*cout<<"the result of the counting_sort"<<endl;
    for(j=0;j<N;j++)
        {
            //x[j].key=rand()%1000;
            printf("%d\t",c[j]);
            if((j+1)%5==0)
            {
                printf("\n");
            }
        }*/
}

int Radix(int k,int p)
{
    int power=1;
    for(int i=1;i<p;i++)
    {
        power=power*10;
    }
    return (( k%(power*10))/power) ;
}

void Radix_Sort(int n,struct LIST S[])
{
    struct Queue Q[10];
    //struct LIST tem;
    int r,i,j,k;
    for(j=1;j<=n;j++)
    {
        for(i=0;i<N;i++)
        {
            r=Radix(S[i].key,j);
            Q[r].t[Q[r].l]=S[i];
            Q[r].l++;
        }
        k=0;
        for(i=0;i<10;i++)
        {
            while(Q[i].f!=Q[i].l)
            {
                S[k]=Q[i].t[Q[i].f];
                k++;
                Q[i].f++;
            }
            Q[i].f=Q[i].l=0;
        }
    }
    /*cout<<"the result of the radix_sort"<<endl;
    for(j=0;j<N;j++)
        {
            //x[j].key=rand()%1000;
            printf("%d\t",S[j].key);
            if((j+1)%5==0)
            {
                printf("\n");
            }
        }*/
}

void bucket_sort(int n,struct LIST S[])
{
    int ls=20,i,k=0,tem;
    struct Queue bucket[ls];
    if(ls!=0)
    {
    for(i=0;i<N;i++)//对元素进行一遍扫描之后入桶
    {
        tem=S[i].key/(n/10);
        bucket[tem].t[bucket[tem].l]=S[i];
        bucket[tem].l++;
    }
    for(i=0;i<ls;i++)//桶内排序
    {
        bubble_sort(bucket[i].l,bucket[i].t);
    }
    for(i=0;i<ls;i++)//将元素从桶中拿出
    {
        while(bucket[i].f!=bucket[i].l)
        {
            S[k]=bucket[i].t[bucket[i].f];
            k++;
            bucket[i].f++;
        }
    }
    }
    if(ls==0)
    {
        bubble_sort(N,S);
    }
    /*cout<<"the result of the bucket_sort"<<endl;
    for(i=0;i<N;i++)
        {
            //x[j].key=rand()%1000;
            printf("%d\t",S[i].key);
            if((i+1)%5==0)
            {
                printf("\n");
            }
        }*/
}

int main()
{
    srand(time(0));
    int k=0,j,m,n=N/3;
    struct LIST x[N],y[N],z[N],c[N];
    clock_t start, end;
    double t;
    m=n;
    //printf("所得到的随机数为：\n");
    for(j=0;j<N;j++)
        {
            x[j].key=rand()%n;
            y[j].key=z[j].key=x[j].key;
            c[j].key=20;
            /*printf("%d\t",x[j].key);
            if((j+1)%5==0)
            {
                printf("\n");
            }*/
        }
    while(m!=1)
    {
        k++;
        m=m/10;
    }
    cout<<"the random data"<<endl;
    start = clock();
    bucket_sort(n,x);
    end = clock();
    t = (double)(end-start)/CLOCKS_PER_SEC;
    cout<<"bucket Time ("<<N<<"nums):"<<t<<"s"<<endl<<endl;
    start = clock();
    Radix_Sort(k+1,y);
    end = clock();
    t = (double)(end-start)/CLOCKS_PER_SEC;
    cout<<"radix Time ("<<N<<"nums):"<<t<<"s"<<endl<<endl;
    start = clock();
    counting_sort(n,z);
    end = clock();
    t = (double)(end-start)/CLOCKS_PER_SEC;
    cout<<"counting Time ("<<N<<"nums):"<<t<<"s"<<endl<<endl;
    cout<<"the asc data"<<endl;
    start = clock();
    bucket_sort(n,x);
    end = clock();
    t = (double)(end-start)/CLOCKS_PER_SEC;
    cout<<"bucket Time ("<<N<<"nums):"<<t<<"s"<<endl<<endl;
    start = clock();
    Radix_Sort(k+1,y);
    end = clock();
    t = (double)(end-start)/CLOCKS_PER_SEC;
    cout<<"radix Time ("<<N<<"nums):"<<t<<"s"<<endl<<endl;
    start = clock();
    counting_sort(n,z);
    end = clock();
    t = (double)(end-start)/CLOCKS_PER_SEC;
    cout<<"counting Time ("<<N<<"nums):"<<t<<"s"<<endl<<endl;
    cout<<"the repeating data"<<endl;
    start = clock();
    bucket_sort(n,c);
    end = clock();
    t = (double)(end-start)/CLOCKS_PER_SEC;
    cout<<"bucket Time ("<<N<<"nums):"<<t<<"s"<<endl<<endl;
    start = clock();
    Radix_Sort(k+1,c);
    end = clock();
    t = (double)(end-start)/CLOCKS_PER_SEC;
    cout<<"radix Time ("<<N<<"nums):"<<t<<"s"<<endl<<endl;
    start = clock();
    counting_sort(n,c);
    end = clock();
    t = (double)(end-start)/CLOCKS_PER_SEC;
    cout<<"counting Time ("<<N<<"nums):"<<t<<"s"<<endl<<endl;
    return 0;
}
