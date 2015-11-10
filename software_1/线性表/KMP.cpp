#include <iostream>
#include <string>
#define max 100

using namespace std;

void nextfuction(char *S, int l, int next[])
{
	int k = 0, i = 0;
	//int next[l];
	next[0] = -1;
	int j = -1;
	char T[max];
	while (k<l)
	{
		T[k] = *S;
		S++;
		k++;
	}
	while (i < l)
	{
		if (j == -1 || T[i] == T[j])
		{
			++i;
			++j;
			next[i] = j;
		}
		else
		{
			//j= next[j];
			j--;
		}
	}
}

int KMP(char s[], char t[], int ls, int lt, int next[])
{
	int i = 0;
	int j = 0;
	while ((i<ls) && (j<lt))
	{
		if (s[i] == t[j])
		{
			++j;
		}
		else
		{
			j = next[j] + 1;
		}
		i++;
	}
	if (j >= lt)
		return i - lt + 1;
	else
		return -1;
}

int main()
{
	char M[max], T[max], *S = NULL;
	int l = 0, ml = 0, r;
	int next[max];
	cout << "please input the main string:" << endl;
	cin >> M;
	cout << "please input the target string:" << endl;
	cin >> T;
	while (T[l] != '\0')
	{
		l++;
	}
	while (M[ml] != '\0')
	{
		ml++;
	}
	S = T;
	nextfuction(S, l, next);
	r = KMP(M, T, ml, l, next);
	cout << r << endl;
	return 0;
}
/*int i = 1;
int next[9];
next[1] = 0;
int j = 0;
char T[9];
cin>>T;
//cout<<T<<endl;
while (i < 9) //T[0]中存放数组长度
{
if( j==0||T[i]==T[j])
{
++i;
++j;
next[i]=j;
}
else
{
//j= next[j];
j--;
}
}
for(int k=1;k<9;k++)
{
cout<<next[k];
}*/
