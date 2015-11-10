#include <iostream>
#define max 20

using namespace std;

struct skiplist
{
	int val;
	skiplist *next = NULL;
	skiplist *down = NULL;
};

int height(skiplist *top)
{
	int n = 0;
	skiplist *p = NULL;
	p = top;
	while (p->down != NULL)
	{
		n++;
		p = p->down;
	}
	return n;
}

void Insert(skiplist *top, int x, int k)
{
	int i, j;
	j = height(top);
	skiplist *p[max];
	skiplist *q = top->down;
	for (i = 0; i < max; i++)
	{
		p[i] = NULL;
	}
	while (q != NULL)
	{
		while (q->next->val<x)
		{
			q = q->next;
		}
		if (j <= k)
		{
			p[j - 1] = q;
			q = q->down;
			j--;
		}
		else
		{
			q = q->down;
			j--;
		}
	}
	for (i = 0; i<k; i++)
	{
		if (p[i] == NULL)
		{
			skiplist *head, *last, *mid;
			head = new skiplist;
			mid = new skiplist;
			//top = new skiplist;
			last = new skiplist;
			//top->down = head;
			head->val = -1;
			head->next = mid;
			head->down = top->down;
			mid->val = x;
			mid->next = last;
			mid->down = p[i - 1]->next;
			last->val = 10000;
			top->down = head;
			p[i] = head;
		}
		else
		{
			skiplist *o = NULL;
			o = new skiplist;
			o->val = x;
			o->next = p[i]->next;
			if (i != 0)
			{
				o->down = p[i - 1]->next;
			}
			else
				o->down = NULL;
			p[i]->next = o;
		}
	}
}

skiplist* Find(skiplist *top, int x)
{
	skiplist *p = top->down;
	while (p->down != NULL)
	{
		if (p->next->val<x)
			p = p->next;
		else
			p = p->down;
	}
	while (p->next->val<x)
	{
		p = p->next;
	}
	if (p->next->val == x)
		return p->next;
	else
	{
		p = NULL;
		return p;
	}
}

void Delete(skiplist *top, int x)
{
	int i, j;
	j = height(top);
	skiplist *test = NULL;
	skiplist *p = top->down;
	skiplist *d = NULL;
	test = Find(top, x);
	if (test == NULL)
	{
		cout << "the element is not exist!" << endl;
	}
	else
	{
		while (p != NULL)
		{
			if (p->next->val<x)
				p = p->next;
			else if (p->next->val == x)
			{
				d = p;
				d->next = d->next->next;
				if ((d->val == -1) && (d->next->val == 10000))
				{
					top->down = top->down->down;
				}
				p = p->down;
			}
			else
				p = p->down;
		}
	}
}

int main()
{
	int level, data,k;
	skiplist *top = NULL, *head = NULL, *last = NULL;
	head = new skiplist;
	top = new skiplist;
	last = new skiplist;
	top->down = head;
	head->val = -1;
	head->next = last;
	last->val = 10000;
	cout<<"input the level and the data to establish the jump check:(when the data is -1,it is over)"<<endl;
	do
	{
		cin >> level >> data;
		if (data != -1)
		{
			Insert(top, data, level);
		}
	} while (data != -1);
	int i = height(top);
	cout << i << endl;
	skiplist *test[max], *t,*p=NULL;
	t = top;
	for (k = 0; k<i; k++)
	{
		test[k] = t->down;
		while (test[k] != NULL)
		{
			cout << test[k]->val << "->";
			test[k] = test[k]->next;
		}
		cout << endl;
		t = t->down;
	}
	cout<<"please input the data you want to research:"<<endl;
	cin >> k;
	p = Find(top, k);
	if (p == NULL)
	{
		cout << "none" << endl;
	}
	else
	{
		cout << p->val << endl;
	}
	cout << "input the number you want to delete:" << endl;
	cin >> k;
	Delete(top,k);
	t = top;
	for (k = 0; k<i; k++)
	{
		test[k] = t->down;
		while (test[k] != NULL)
		{
			cout << test[k]->val << "->";
			test[k] = test[k]->next;
		}
		cout << endl;
		t = t->down;
	}
	return 0;
}
