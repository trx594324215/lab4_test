#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <stdio.h>
#define N 100000
using namespace std;
//quick sort 


struct LIST
{
    int key;
};

void Swap(struct LIST &a,struct LIST &b)
{
    struct LIST tem;
    tem=a;
    a=b;
    b=tem;
}

int Partition_asc(struct LIST S[],int p,int r)
{
    int x=S[r].key;
    int j,i=p-1,m=(p+r)/2;
    for(j=p;j<r;j++)
    {
        if(S[j].key<=x)
        {
            i=i+1;
            Swap(S[j],S[i]);
        }
    }
    Swap(S[i+1],S[r]);
    return i+1;
}

int Partition_asc_op(struct LIST S[],int p,int r)
{
    int x=S[r].key;
    int j,i=p-1,m=(p+r)/2;
    if(S[r].key<S[m].key)
    {
        Swap(S[r],S[m]);
    }
    if(S[p].key>S[r].key)
    {
        Swap(S[p],S[r]);
    }
    if(S[p].key>S[m].key)
    {
        Swap(S[p],S[m]);
    }
    x=S[m].key;
    for(j=p;j<r;j++)
    {
        if(S[j].key<=x)
        {
            i=i+1;
            Swap(S[j],S[i]);
        }
    }
    Swap(S[i+1],S[r]);
    return i+1;
}

int Partition_des(struct LIST S[],int p,int r)
{
    int x=S[r].key;
    int j,i=p-1;
    for(j=p;j<r;j++)
    {
        if(S[j].key>=x)
        {
            i=i+1;
            Swap(S[j],S[i]);
        }
    }
    Swap(S[i+1],S[r]);
    return i+1;
}

void quick_sort_asc(int p,int r,struct LIST S[])
{
    int q;
    if(p<r)
    {
        q=Partition_asc(S ,p, r);
        quick_sort_asc(p,q-1,S);
        quick_sort_asc(q+1,r,S);
    }
}

void quick_sort_asc_op(int p,int r,struct LIST S[])
{
    int q;
    if(p<r)
    {
        q=Partition_asc_op(S ,p, r);
        quick_sort_asc_op(p,q-1,S);
        quick_sort_asc_op(q+1,r,S);
    }
}

void quick_sort_asc_op2(int p,int r,struct LIST S[])
{
    if(p<r)
    {
        int x=S[r].key,tem[N+1],k=0,h;
    int j,i=p-1,m=(p+r)/2;
    if(S[r].key<S[m].key)
    {
        Swap(S[r],S[m]);
    }
    if(S[p].key>S[r].key)
    {
        Swap(S[p],S[r]);
    }
    if(S[p].key>S[m].key)
    {
        Swap(S[p],S[m]);
    }
    x=S[m].key;
    for(j=p;j<r;j++)
    {
        if(S[j].key<x)
        {
            i=i+1;
            Swap(S[j],S[i]);
        }
        if(S[j].key==x)
        {
            i=i+1;
            tem[k]=i;
            k++;
            Swap(S[j],S[i]);
        }
    }
    Swap(S[i+1],S[r]);
    h=i+1;
    for(;k>=0;k--)
    {
        Swap(S[i],S[k]);
        i--;
    }
        quick_sort_asc_op(p,i,S);
        quick_sort_asc_op(h,r,S);
    }
}

void quick_sort_des(int p,int r,struct LIST S[])
{
    int q;
    if(p<r)
    {
        q=Partition_des(S ,p, r);
        quick_sort_des(p,q-1,S);
        quick_sort_des(q+1,r,S);
    }
}

int main()
{
    srand(time(0));
    int j,o;
    struct LIST x[N+1],x_des[N+1],x_asc[N+1],y[N+1],y_des[N+1],y_asc[N+1],z[N+1];
    clock_t start, end;
    double t;
    printf("所得到的随机数为：\n");
    for(j=1;j<N+1;j++)
        {
            x[j].key=rand()%100000+20;
            x_des[j].key=x_asc[j].key=x[j].key;
            y_des[j].key=y_asc[j].key=y[j].key=x[j].key;
            z[j].key=10;
        }
    quick_sort_des(1,N,x_des);
    quick_sort_des(1,N,y_des);
    quick_sort_asc(1,N,x_asc);
    quick_sort_asc(1,N,y_asc);
     /*for(j=1;j<N+1;j++)
        {
            //x[j].key=rand()%10000+20;
            //x_des[j].key=x_asc[j].key=x[j].key;
            printf("%d\t",x_asc[j].key);
            if((j)%5==0)
            {
                printf("\n");
            }
        }*/
    start = clock();
    quick_sort_asc(1,N,x);
    end = clock();
    t = (double)(end-start)/CLOCKS_PER_SEC;
    cout<<" random Time ("<<N<<"nums):"<<t<<"s"<<endl<<endl;
    start = clock();
    quick_sort_asc(1,N,x_asc);
    end = clock();
    t = (double)(end-start)/CLOCKS_PER_SEC;
    cout<<" des Time ("<<N<<"nums):"<<t<<"s"<<endl<<endl;
    start = clock();
    quick_sort_asc(1,N,x_des);
    end = clock();
    t = (double)(end-start)/CLOCKS_PER_SEC;
    cout<<" asc Time ("<<N<<"nums):"<<t<<"s"<<endl<<endl;
    cout<<"after the op"<<endl;
    start = clock();
    quick_sort_asc_op2(1,N,y);
    end = clock();
    t = (double)(end-start)/CLOCKS_PER_SEC;
    cout<<" random Time ("<<N<<"nums):"<<t<<"s"<<endl<<endl;
    start = clock();
    quick_sort_asc_op2(1,N,y_asc);
    end = clock();
    t = (double)(end-start)/CLOCKS_PER_SEC;
    cout<<" des Time ("<<N<<"nums):"<<t<<"s"<<endl<<endl;
    start = clock();
    quick_sort_asc_op2(1,N,y_des);
    end = clock();
    t = (double)(end-start)/CLOCKS_PER_SEC;
    cout<<" asc Time ("<<N<<"nums):"<<t<<"s"<<endl<<endl;
    cout<<"all the data are the same:"<<endl;
    start = clock();
    quick_sort_asc(1,N,z);
    end = clock();
    t = (double)(end-start)/CLOCKS_PER_SEC;
    cout<<" Time ("<<N<<"nums):"<<t<<"s"<<endl<<endl;
    cout<<"after the op"<<endl;
    start = clock();
    quick_sort_asc_op2(1,N,z);
    end = clock();
    t = (double)(end-start)/CLOCKS_PER_SEC;
    cout<<" Time ("<<N<<"nums):"<<t<<"s"<<endl<<endl;
    return 0;
}
/*printf("快速排序后的结果为：\n");
    for(j=1;j<N+1;j++)
    {
        printf("%d    ",x[j]);
        if((j+1)%5==0)
        {
            printf("\n");
        }
    }
void quick_sort_asc_op_2(int p,int r,struct LIST S[])
{
    if(p<r)
    {
        int x=S[r].key,tem[N+1],k=0,h;
    int j,i=p-1,m=(p+r)/2;
    if(S[r].key<S[m].key)
    {
        Swap(S[r],S[m]);
    }
    if(S[p].key>S[r].key)
    {
        Swap(S[p],S[r]);
    }
    if(S[p].key>S[m].key)
    {
        Swap(S[p],S[m]);
    }
    x=S[m].key;
    for(j=p;j<r;j++)
    {
        if(S[j].key<x)
        {
            i=i+1;
            Swap(S[j],S[i]);
        }
        if(S[j].key==x)
        {
            i=i+1;
            tem[k]=i;
            k++;
            Swap(S[j],S[i]);
        }
    }
    Swap(S[i+1],S[r]);
    h=i+1;
    for(;k>=0;k--)
    {
        Swap(S[i],S[k]);
        i--;
    }
        quick_sort_asc_op(p,i,S);
        quick_sort_asc_op(h,r,S);
    }
}*/
