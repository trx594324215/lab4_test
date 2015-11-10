#include <iostream>
#define N 100
using namespace std;

int n;

typedef struct edge
{
	int bgn, End, wet;
}Egde;

int Find(int father[], int v)
{
	int f = v;
	while (father[f] >0)
		f = father[f];
	return (f);
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
		C[a][b] = Weight;
		cin >> a >> b >> Weight;
	}
}

void Kruskal(Egde edges[], int e)
{
	int father[N], bnf, edf, i;
	for (i = 1; i <= e; i++)
		father[i] = 0;
	for (i = 1; i <= e; i++)
	{
		bnf = Find(father, edges[i].bgn);
		edf = Find(father, edges[i].End);
		if (bnf != edf)
			father[bnf] = edf;
	}
}

void Sort(Egde edges[N], int e)
{
	int i, j, temp, k;
	Egde Temp;
	for (i = 1; i<e ; i++)
	{
		temp = edges[i].wet;
		k = i;
		for (j = i + 1; j<=e; j++)
		{
			if (edges[j].wet<temp)
			{
				k = j;
				temp = edges[j].wet;
			}
		}
		Temp = edges[k];
		edges[k] = edges[i];
		edges[i] = Temp;
	}
}

int main()
{
	cout << "please input the number of the points:" << endl;
	cin >> n;
	Egde edges[N];
	int C[N][N], i, j, k = 1;
	create(C);
	for (i = 0; i<n; i++)
	{
		for (j = 0; j<n; j++)
		{
			if (C[i][j] != 10000)
			{
				edges[k].bgn = i;
				edges[k].End = j;
				edges[k].wet = C[i][j];
				k++;
			}
		}
	}
	Sort(edges, k-1);
	Kruskal(edges, k-1);
	return 0;
}
