#include <iostream>
#define max 100
using namespace std;
//线索二叉树
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

void  createBiTree(BiTree &T)//递归建立二叉树//
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

void  PreOrder(BiTree BT)//递归前序遍历//
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

void  InOrderTh(BiTree p) //将二叉树 p前序线索化
{
	//cout << p->data;
	if (p)
	{ //p 非空时，当前访问的结点是 p
		p->ltag = (p->leftChild) ? true : false; //左(右)孩子 非空
		p->rtag = (p->rightChild) ? true : false; //时,标志1,否: 0
		if (pre)
		{ //若*p 的前驱*pre 存在
			if (pre->rtag == false) //  *p的前驱右标志为线索
				pre->rightChild = p; // 令 *pre 的右线索指向前序后 继
			if (p->ltag == false) //   *p的左标志为线索
				p->leftChild = pre;         //令 *p的左线索指向前序 前驱
		}
		pre = p;
		// 令pre 是下一个访问的前序前驱
		if (p->ltag == true)
		{
			InOrderTh(p->leftChild);
		} //左子树线索化
		if (p->rtag == true)
		{
			InOrderTh(p->rightChild);
		}
	}
}

BiTree  fNext(BiTree p)//前序的后一个
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

BiTree parent(BiTree t,char a)//求父节点
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

BiTree  InNext(BiTree p,BiTree T)//中序的下一个
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
