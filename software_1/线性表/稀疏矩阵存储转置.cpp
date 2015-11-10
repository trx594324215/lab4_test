#include <iostream>

using namespace std;

struct element
{
	int row;
	int col;
	int item;
	element *next = NULL;
};

int main()
{
	struct element *LIST = NULL, *TLIST = NULL, *p = NULL, *q = NULL, *k = NULL;
	int i, j, r, c, tempr, tempc, tempi;
	cout << "Please input the array's row and col:" << endl;
	cin >> r >> c;
	cout << "Please input the element:" << endl;
	LIST = new element;
	p = LIST;
	do
	{
		cin >> tempr >> tempc >> tempi;
		if (tempi != 0)
		{
			p->row = tempr;
			p->col = tempc;
			p->item = tempi;
			q = new element;
			p->next = q;
			p = p->next;
		}
		else
		{
			p = NULL;
			break;
		}
	} while (p->item != 0);
	p = LIST;
	TLIST = new element;
	k = TLIST;
	while (p->next != NULL)
	{
		k->row = p->col;
		k->col = p->row;
		k->item = p->item;
		p = p->next;
		q = new element;
		k->next = q;
		k = k->next;
	}
	k = NULL;
	cout << "the array is:" << endl;
	for (i = 0; i<r; i++)
	{
		for (j = 0; j<c; j++)
		{
			p = LIST;
			while (p->next != NULL)
			{
				if ((i + 1 == p->row) && (j + 1 == p->col))
				{
					cout << p->item;
					break;
				}
				p = p->next;
			}
			if (p->next == NULL)
				cout << '0';
		}
		cout << endl;
	}
	cout << "the transport matrix: " << endl;
	for (i = 0; i<c; i++)
	{
		for (j = 0; j<r; j++)
		{
			p = TLIST;
			while (p->next != NULL)
			{
				if ((i + 1 == p->row) && (j + 1 == p->col))
				{
					cout << p->item;
					break;
				}
				p = p->next;
			}
			if (p->next == NULL)
				cout << '0';
		}
		cout << endl;
	}
	for (i = 0; i < c; i++)
	{
		for (j = 0; j < r; j++)
		{
			p = TLIST;
			while (p->next != NULL)
			{
				if ((i + 1 == p->row) && (j + 1 == p->col))
				{
					cout <<p->row<<p->col<< p->item << endl;
					break;
				}
				p = p->next;
			}
		}
	}
	return 0;
}
