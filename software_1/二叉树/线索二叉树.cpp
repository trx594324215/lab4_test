#include <iostream>
#define max 100
using namespace std;
//����������
typedef struct node
{
	struct node *leftChild;
	struct node *rightChild;
	char data;
	bool ltag;
	bool rtag;
}BiTreeNode, *BiTree;

typedef struct Stack
{
	BiTree Data[max];
	int top;
	int flag;
}STACK;

//BiTree pre = NULL;
BiTree test[max];
int i = 0;

BiTree pre;

void  createBiTree(BiTree &T)//�ݹ齨��������//
{
	char c;
	cin >> c;
	if ('#' == c)
		T = NULL;
	else
	{
		T = new BiTreeNode;
		T->data = c;
		createBiTree(T->leftChild);
		createBiTree(T->rightChild);
	}
}

void  PreOrder(BiTree BT)//�ݹ�ǰ�����//
{
	if (BT != NULL)
	{
		cout << BT->data;
		test[i] = BT;
		i++;
		if (BT->leftChild == NULL)
		{
			BT->ltag = false;
		}
		if (BT->rightChild == NULL)
		{
			BT->rtag = false;
		}
		PreOrder(BT->leftChild);
		PreOrder(BT->rightChild);
	}
}

void  InOrderTh(BiTree p) //�������� pǰ��������
{
	//cout << p->data;
	if (p)
	{ //p �ǿ�ʱ����ǰ���ʵĽ���� p
		p->ltag = (p->leftChild) ? true : false; //��(��)���� �ǿ�
		p->rtag = (p->rightChild) ? true : false; //ʱ,��־1,��: 0
		if (pre)
		{ //��*p ��ǰ��*pre ����
			if (pre->rtag == false) //  *p��ǰ���ұ�־Ϊ����
				pre->rightChild = p; // �� *pre ��������ָ��ǰ��� ��
			if (p->ltag == false) //   *p�����־Ϊ����
				p->leftChild = pre;         //�� *p��������ָ��ǰ�� ǰ��
		}
		pre = p;
		// ��pre ����һ�����ʵ�ǰ��ǰ��
		if (p->ltag == true)
		{
			InOrderTh(p->leftChild);
		} //������������
		if (p->rtag == true)
		{
			InOrderTh(p->rightChild);
		}
	}
}

BiTree  fNext(BiTree p)//ǰ��ĺ�һ��
{
	BiTree q;
	if (p->rtag == false)
	{
		q = p->rightChild;
		return q;
	}
	else
	{
		if (p->ltag == true)
		{
			q = p->leftChild;
		}
		else
			q = p->rightChild;
	}
	return q;
}

BiTree parent(BiTree t,char a)//�󸸽ڵ�
{
	if (t->ltag == true)
	{
		if (t->leftChild->data == a)
		{
			return t;
		}
	}
	if (t->rtag == true)
	{
		if (t->rightChild->data == a)
		{
			return t;
		}
			
	}
	t = fNext(t);
	parent(t,a);
}

BiTree  InNext(BiTree p,BiTree T)//�������һ��
{
	BiTree Q;
	if (p->rtag != false)
	{
		Q = p->rightChild;
		while (Q->ltag != false)
		{
			Q = Q->leftChild;
		}
	}
	else
	{
		Q = p->rightChild;
		if (Q != NULL)
		{
			Q = parent(T, Q->data);
		}
	}
	return (Q);
}

void midorder(BiTree T,BiTree t)
{
	BiTree Q;
	cout << T->data;
	Q=InNext(T,t);
	if (Q != NULL)
	{
		//cout << Q->data;
		midorder(Q,t);
	}
}

void preorder(BiTree T)
{
	if (T != NULL)
	{
		cout << T->data;
		T = fNext(T);
		preorder(T);
	}
}

int main()
{
	BiTree Q, T,t;
	createBiTree(T);
	InOrderTh(T);
	t = T;
	preorder(t);
	cout << endl;
	/*Q = InNext(T->rightChild,T);
	cout << Q->data << endl;*/
	while (T->ltag != false)
	{
		T = T->leftChild;
	}
	//Q = InNext(T,t);
	//cout << Q->data;
	midorder(T,t);
	return 0;
}
