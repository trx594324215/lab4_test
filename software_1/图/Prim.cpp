#include <iostream>
#define N 100
using namespace std;

int n;

void  Prim(int  C[N][N])
{
	int  LOWCOST[N];
	int  CLOSEST[N];
	int i, j, k;
	int  Min;
	LOWCOST[0] = 0;
	CLOSEST[0] = 0;
	for (i = 1; i<n; i++)
	{
		LOWCOST[i] = C[0][i];
		CLOSEST[i] = 0;
	}
	for (i = 1; i < n; i++)
	{
		for (int p = 1; p < n; p++)
		{
			if (LOWCOST[p] != 0)
			{
				Min = LOWCOST[p];
				k = p;
				break;
			}
		}
		for (j = 1; j < n; j++)
		{
			if ((LOWCOST[j] < Min) && (LOWCOST[j]!=0))
			{
				Min = LOWCOST[j];
				k = j;
			}
		}
		char point;
		point = k + 65;
		cout << "(" << point << "," << CLOSEST[k] << ")" << endl;
		LOWCOST[k] = 0;
		for (j = 1; j < n; j++)
		if (C[k][j] <  LOWCOST[j] && LOWCOST[j] != 0)
		{
			LOWCOST[j] = C[k][j];
			CLOSEST[j] = k;
		}
	}
}

void create(int C[N][N])
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
		C[b][a]=C[a][b] = Weight;
		cin >> a >> b >> Weight;
	}
}

int main()
{
	cout << "please input the number of the points:" << endl;
	cin >> n;
	int C[N][N];
	create(C);
	Prim(C);
	return 0;
}
