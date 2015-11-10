#include <iostream>
#define N 100
using namespace std;

int n;

void create(int C[N][N])//邻接矩阵建立图
{
	//int C[n][n];
	for (int i = 0; i<n; i++)
	{
		for (int j = i; j<n; j++)
		{
			if (j == i)
			{
				C[i][j] = 10000;
			}
			else
			{
				C[i][j] = C[j][i] = 10000;
			}
		}
	}
	cout << "please input the weight of the points:" << endl;
	int a, b;
	int Weight;
	cin >> a >> b >> Weight;
	while (Weight != 10000)
	{
		C[a][b] = Weight;
		cin >> a >> b >> Weight;
	}
}

int MinCost(int D[N], bool S[N])
{
	int temp = 10000;
	int w = 1,i;
	for (i = 1; i < n; i++)
	{
		if (!S[i] && D[i] < temp)
		{
			temp = D[i];
			w = i;
		}
	}
	return  w;
}

void  Dijkstra(int  C[N][N])
{
	int D[N], P[N];
	bool S[N];
	int sum,v,w,i;
	for (i = 1; i < n; i++)
	{
		D[i] = C[0][i];
		S[i] = false; 
		P[i] = 0;
	}
	S[0] = true;
	int m = n;
	for (i = 0; i < m - 1; i++)
	{
		w = MinCost(D, S);
		S[w] = true;
		for (v = 1; v < m; v++)
		{
			if (S[v] != true)
			{
				sum = D[w] + C[w][v];
				if (sum < D[v])
				{
					D[v] = sum;
					P[v] = w;
				}
			}
		}
	}
}//   时间复杂度：O（n2）

int main()
{
	cout << "please input the number of the points:" << endl;
	cin >> n;
	int C[N][N],D[N],P[N];
	bool S[N];
	create(C);
	Dijkstra(C);
	return 0;
}
