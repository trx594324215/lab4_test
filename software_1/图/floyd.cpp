#include <iostream>
#define N 100
using namespace std;

int n;

void create(int C[N][N])
{
	//int C[n][n];
	for (int i = 0; i<n; i++)
	{
		for (int j = i; j<n; j++)
		{
			if (j == i)
			{
				C[i][j] = 0;
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

void   Floyd(int A[N][N], int C[N][N], int P[N][N])
{
	int i, j, k;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j< n; j++)
		{
			A[i][j] = C[i][j];
			P[i][j] = -1;
		}
	}
	for (k = 0; k < n; k++)
	{
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				if (A[i][k] + A[k][j] < A[i][j])
				{
					A[i][j] = A[i][k] + A[k][j];
					P[i][j] = k;
				}
			}
		}
	}
} /* Ê±¼ä¸´ÔÓ¶È£ºO(n3) */

int main()
{
	cout << "please input the number of the points:" << endl;
	cin >> n;
	int C[N][N],A[N][N],P[N][N];
	create(C);
	Floyd(A, C, P);
	return 0;
}
