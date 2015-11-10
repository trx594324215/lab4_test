#include <iostream>
#define max 20
using namespace std;

struct LIST
{
	int key;
	//char name[10];
};
LIST A[max];

void PushDown(int first, int last)
{       /*整理堆:A是外部数组,把A[first]下推到完全二元树的适当位置*/
	int r = first; /* r是被下推到的适当位置，初始值为根first*/
	while (r <= last / 2) /* A[r]不是叶，否则是堆*/
	if ((r == last / 2) && (last % 2 == 0))
	{/* r有一个儿子在2*r上且为左儿子*/
		if (A[r].key>A[2 * r].key)
			swap(A[r], A[2 * r]);/*下推*/
		r = last;  /*A[r].key小于等于A[2*r].key或者"大于"，交换后到叶，循环结束*/
	}
	else if ((A[r].key>A[2 * r].key) && (A[2 * r].key <= A[2 * r + 1].key))
	{ /*根大于左儿子，且左儿子小于或等于右儿子*/
		swap(A[r], A[2 * r]);         /*与左儿子交换*/
		r = 2 * r;                /*下推到的位置也是下次考虑的根*/
	}
	else if ((A[r].key>A[2 * r + 1].key) && (A[2 * r + 1].key<A[2 * r].key))
	{ /*根大于右儿子，且右儿子小于左儿子*/
		swap(A[r], A[2 * r + 1]);      /*与右儿子交换*/
		r = 2 * r + 1;            /*下推到的位置也是下次考虑的根*/
	}
	else /*A[r]符合堆的定义，不必整理，循环结束*/
		r = last;
}/*PushDown*/

void HeapSort(int n)
{
	int i;
	for (i = n / 2; i >= 1; i--)   /*初始建堆，从右非叶结点开始*/
		PushDown(i, n);/*整理堆，把以i为根，大下标的叶为n*/
	for (i = n; i >= 2; i--)
	{
		swap(A[1], A[i]); //堆顶与当前堆中的下标大的叶结点交换
		PushDown(1, i - 1); /*整理堆把以1为根，大叶下标为i-1的完全二元树整理成堆*/
	}
}

int length()
{
	int i = 1;
	while (A[i].key != 0)
	{
		i++;
	}
	return i;
}

void Insert(int k)
{
	int x;
	cout << "please input the new user's money to insert:" << endl;
	cin >> x;
	A[k + 1].key = x;
	HeapSort(k + 1);
}

void push(int m)
{
	swap(A[1], A[m - 1]);
	A[m - 1].key = 0;
	int k = length();
	HeapSort(k);
}

int main()
{
	int i;
	for (i = 0; i<max; i++)
	{
		A[i].key = 0;
	}
	int k, m;
	cout << "please input the number:" << endl;
	cin >> m;
	cout << "please input the data:" << endl;
	for (i = 1; i<m+1; i++)
	{
		cin >> A[i].key;
		//Insert(k);
	}
	k = length();
	HeapSort(k);
	for (i = 1; i<m+1; i++)
	{
		cout << A[i].key << endl;
		//Insert(k);
	}
	Insert(k);
	//cout << ""
	m = length();
	push(m);
	for (i = 1; i<m-1; i++)
	{
		cout << A[i].key << endl;
		//Insert(k);
	}
	return 0;
}
