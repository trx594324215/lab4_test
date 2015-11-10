#include <iostream>
#define B 10000
#include <fstream>

using namespace std;

struct records
{
	long int key;
};

struct search_type
{
	records data;
	search_type *next;
};
typedef  search_type  *search_ptr; //开散列表类型，B为桶数 typedef cellptr  HASH[B]

typedef search_ptr  HASH[B];

int h_key(int k)
{
	int m,n,o;
	m = k % 10000;
	k = k / 10000;
	n = k % 10000;
	k = k / 10000;
	o = k % 10000;
	m = (m + n + o) % 10000;
	return m;
}

search_ptr Search(int k, HASH F)
{
	search_ptr bptr=NULL;
	int m;
	m = h_key(k);
	bptr = F[m];
	while (bptr != NULL)
	{
		if (bptr->data.key == k)
			return bptr;
		else
			bptr = bptr->next;
	}
	return bptr;// 没找到
}//Search

void Insert(records R, HASH  F)
{
	int bucket;
	search_ptr oldheader;
	if (Search(R.key, F) == NULL)
	{
		bucket = h_key(R.key);
		oldheader = F[bucket];
		F[bucket] = new search_type;
		F[bucket]->data = R;
		F[bucket]->next = oldheader;
	}
}//Insert

void Delete(int k, HASH F) 
{
	int bucket = h_key(k); 
	search_ptr bptr, p; 
	if (F[bucket] != NULL)//可能在表中 
		if(F[bucket]->data.key==k)
		{//首元素就是 
			bptr= F[bucket]; 
			F[bucket]=F[bucket]->next; 
			free(bptr); 
		}
		else
		{//可能在中间或不存在 
			bptr=F[bucket]; 
			while(bptr->next!=NULL) 
				if(bptr->next->data.key==k)
				{ 
					p=bptr->next; 
					bptr->next=p->next; 
					free(p); 
				}
				else 
					bptr=bptr->next; 
		} 
}// Delete 


int main()
{
	records R;
	int i,j,k=0;
	float a;
	HASH F;
	search_ptr p = NULL;
	for (i = 0; i < B; i++)
	{
		F[i] = NULL;
	}
	fstream f("f:\\book.txt", ios::in);
	//cin >> a >> b >> c >> d;
	f >> R.key;
	i = 0;
	while (R.key >= 0)
	{
		i++;
		Insert(R, F);
		f >> R.key;
	}
	f.close();
	for (i = 0; i < B; i++)
	{
		if (F[i] != NULL)
			k++;
	}
	a = 1.0*k / B;
	cout << a<<endl;
	cin >> j;
	p=Search(j,F);
	if (p != NULL)
	{
		cout << "find it" << endl;
	}
	else
	{
		cout << "none" << endl;
	}
	return 0;
}
