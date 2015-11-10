#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <stdio.h>
#define max 10
using namespace std;
#count sort

struct Struct
{
	int key;
	int node;
	Struct* next;
};

int main()
{
	srand(time(0));
	int r0, rm, X[max], j, i;
	for (j = 0; j<max; j++)
	{
		X[j] = rand() % 10;
		cout << X[j] << "   ";
		if ((j + 1) % 5 == 0)
		{
			cout << endl;
		}
	}
	cout << "please input the zone you want to sort:" << endl;
	//cin>>r0>>rm;
	struct Struct S[max];
	for (j = 0; j<max; j++)
	{
		S[j].key = 0;
		S[j].next = NULL;
	}
	for (i = 0; i<max; i++)
	{
		if (S[X[i]].key == 0)
		{
			S[X[i]].node = X[i];
			S[X[i]].key = 1;
		}
		else
		{
			Struct *Si = new Struct;
			Struct *p;
			p = S[X[i]].next;
			if (p != NULL)
			{
				while (p->next != NULL)
				{
					p = p->next;
				}
				Si->node = X[i];
				Si->next = NULL;
				p->next = Si;
				S[X[i]].key++;
			}
			else
			{
				Si->node = X[i];
				Si->next = NULL;
				S[X[i]].next = Si;
				S[X[i]].key++;
			}
		}
	}
	for (i = 0; i<max; i++)
	{
		if (S[i].key != 0)
		{
			cout << S[i].node << endl;
			Struct *Si;
			Si = S[i].next;
			while (Si != NULL)
			{
				cout << S[i].node << endl;
				Si = Si->next;
			}
		}
	}
	return 0;
}
