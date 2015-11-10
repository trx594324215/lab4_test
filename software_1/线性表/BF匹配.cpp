#include <iostream>
#define max 100
using namespace std;
int main()
{
    char T[max],W[max];
    int i,j,k,m=0;
    cin>>T;
    cout<<"please input the match string"<<endl;
    cin>>W;
    while(W[m]!='\0')
    {
        m++;
    }
    for(i=0;i<max;i++)
    {
        j=0;
        k=i;
        while((W[j]==T[k])&&(j<m)&&(W[j]!='\0'))
        {
            k++;
            j++;
        }
        if((j==10)||(W[j]=='\0'))
        {
            cout<<i+1<<endl;
            break;
        }
    }
    if(i==max)
    {
        cout<<"none"<<endl;
    }
    return 0;
}
