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
{       /*�����:A���ⲿ����,��A[first]���Ƶ���ȫ��Ԫ�����ʵ�λ��*/
	int r = first; /* r�Ǳ����Ƶ����ʵ�λ�ã���ʼֵΪ��first*/
	while (r <= last / 2) /* A[r]����Ҷ�������Ƕ�*/
	if ((r == last / 2) && (last % 2 == 0))
	{/* r��һ��������2*r����Ϊ�����*/
		if (A[r].key>A[2 * r].key)
			swap(A[r], A[2 * r]);/*����*/
		r = last;  /*A[r].keyС�ڵ���A[2*r].key����"����"��������Ҷ��ѭ������*/
	}
	else if ((A[r].key>A[2 * r].key) && (A[2 * r].key <= A[2 * r + 1].key))
	{ /*����������ӣ��������С�ڻ�����Ҷ���*/
		swap(A[r], A[2 * r]);         /*������ӽ���*/
		r = 2 * r;                /*���Ƶ���λ��Ҳ���´ο��ǵĸ�*/
	}
	else if ((A[r].key>A[2 * r + 1].key) && (A[2 * r + 1].key<A[2 * r].key))
	{ /*�������Ҷ��ӣ����Ҷ���С�������*/
		swap(A[r], A[2 * r + 1]);      /*���Ҷ��ӽ���*/
		r = 2 * r + 1;            /*���Ƶ���λ��Ҳ���´ο��ǵĸ�*/
	}
	else /*A[r]���϶ѵĶ��壬��������ѭ������*/
		r = last;
}/*PushDown*/

void HeapSort(int n)
{
	int i;
	for (i = n / 2; i >= 1; i--)   /*��ʼ���ѣ����ҷ�Ҷ��㿪ʼ*/
		PushDown(i, n);/*����ѣ�����iΪ�������±��ҶΪn*/
	for (i = n; i >= 2; i--)
	{
		swap(A[1], A[i]); //�Ѷ��뵱ǰ���е��±���Ҷ��㽻��
		PushDown(1, i - 1); /*����Ѱ���1Ϊ������Ҷ�±�Ϊi-1����ȫ��Ԫ������ɶ�*/
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
