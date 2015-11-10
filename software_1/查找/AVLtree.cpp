#include <iostream>

using namespace std;

typedef struct  celltype
{
	int data;//records=int
	struct celltype  *lchild, *rchild;
	int bf;
}BSTNode;
typedef   BSTNode  *BST;

void R_Rotate(BST &p)//��������
{
	BST q = NULL;
	//q=new node;
	q = p->lchild;
	p->lchild = q->rchild;
	q->rchild = p;
	p = q;
}

void L_Rotate(BST &p)//��������
{
	BST q;
	q = p->rchild;
	p->rchild = q->lchild;
	q->lchild = p;
	p = q;
}

void LeftBalance(BST &T)//��ƽ�⺯��
{
	BST lc;
	BST rd;
	lc = T->lchild;   //��T��������(B)��ֻ����LL��LR��
	switch (lc->bf)
	{
	case 1://����->������LL�ͣ�
		T->bf = lc->bf = 0;
		R_Rotate(T);
		break;
	case -1:  //LR�ͣ�������������
		rd = lc->rchild;   //rd��Ӧ���C���̣ö�Ӧ����
		switch (rd->bf)
		{
		case 1:
			T->bf = -1;
			lc->bf = 0;
			break;
		case 0:
			T->bf = lc->bf = 0;
			break;
		case -1:
			T->bf = 0;
			lc->bf = 1;
			break;
		}//switch(rd->bf)
		rd->bf = 0;
		L_Rotate(T->lchild);
		R_Rotate(T);
	}//switch(lc->bf)
}//LeftBalance

void RightBalance(BST &T)//��ƽ�⺯��
{
	BST rc;
	BST ld;
	rc = T->rchild;
	switch (rc->bf)
	{
	case -1:
		T->bf = rc->bf = 0;
		L_Rotate(T);
		break;
	case 1:
		ld = rc->lchild;
		switch (ld->bf)
		{
		case 0:
			ld->bf = T->bf = rc->bf = 0;
			break;
		case 1:
			rc->bf = -1;
			ld->bf = T->bf = 0;
			break;
		case -1:
			T->bf = 1;//֮ǰ��д����-1
			rc->bf = ld->bf = 0;
			break;
		}
		R_Rotate(T->rchild);
		L_Rotate(T);
	}
}

void AVLInsert(BST &T, int R, int &unbalanced)//records=int
{
	if (T == NULL)
	{  //������������򴴽�
		T = new BSTNode;
		T->data = R;
		T->lchild = T->rchild = NULL;
		T->bf = 0;
		unbalanced = 1;
	}
	else if (R<T->data)
	{//Ҫ��������������
		AVLInsert(T->lchild, R, unbalanced); //�ݹ����ֱ����ĳ����֦�ϲ���ڵ���ΪҶ�ӽڵ�
		if (unbalanced)  //��㷵�أ��ڷ��ع������ж��Ƿ�Ҫ��ת������ƽ�� //��������Ҳ��֤����תʧ���С����
			switch (T->bf)
		{    //���T��ƽ���
			case 1:
				LeftBalance(T);
				unbalanced = 0;
				break;
			case 0:
				T->bf = 1;
				break;
			case -1:
				T->bf = 0;
				unbalanced = 0;
				break;
		}
	}
	else if (R>T->data)
	{
		AVLInsert(T->rchild, R, unbalanced);
		if (unbalanced)
			switch (T->bf)
		{
			case 1://֮ǰд��-1
				T->bf = 0;
				unbalanced = 0;
				break;
			case  0:
				T->bf = -1;
				break;
			case  -1://֮ǰд��1
				RightBalance(T);
				unbalanced = 0;
				break; //��ƽ�⺯��û�и���
		}
	}
	//return 1;
}//AVLInsert

void AVLSearch(BST &T, int R)
{
	if (T != NULL)
	{
		if (T->data > R)
		{
			AVLSearch(T->lchild, R);
		}
		else if (T->data < R)
		{
			AVLSearch(T->rchild, R);
		}
		else
		{
			cout << "the number is in the tree" << endl;
		}
	}
	else
	{
		cout << "can not find the number" << endl;
	}
}

int Height(BST &T) {
	int lheight = 0; int rheight = 0; int result = 0;
	if (T != NULL) {
		if (T->lchild != NULL)
			lheight = Height(T->lchild);
		if (T->rchild != NULL)
			rheight = Height(T->rchild);
		if (lheight >= rheight)
			result = lheight + 1;
		else
			result = rheight + 1;
	}
	return result;
}

void preorder(BST &T)
{
	int l, r;
	if (T!=NULL)
	{
		l = Height(T->lchild);
		r = Height(T->rchild);
		T->bf = l - r;
		switch (T->bf)
		{
		case 2:
			LeftBalance(T);
			break;
		case -2:
			RightBalance(T);
			break;
		}
		preorder(T->lchild);
		preorder(T->rchild);
	}
}

void AVLDelete(BST &T, int R)
{
	BSTNode *root = NULL,*q=NULL;
	root = T;
	q = T;
		if (T->data == R) 
		{
			//balanced = 1;
			if (!T->rchild && !T->lchild) {
				T = NULL;
			}
			else if (T->rchild && !T->lchild) {
				T = T->rchild;
			}
			else if (T->lchild && !T->rchild) {
				T = T->lchild;
			}
			else if (T->lchild && T->rchild) {
				BSTNode *p = T;
				//BSTNode *o = T;
				p = p->rchild;
				//o = o->rchild;
				while (p->lchild) {
					p = p->lchild;
				}
				int tem;
				tem = p->data;
				p->data = T->data+1;
				T->data = tem;
				AVLDelete(T, p->data);
			}
			//preorder(q);
			//q = root;
		}
		else if (R > T->data) {
			if (!T->rchild) return;
			AVLDelete(T->rchild, R);
			preorder(q);
			T = q;
			q = root;
		}
		else if (R < T->data) {
			if (!T->lchild) return;
			AVLDelete(T->lchild, R);
			preorder(q);
			T = q;
			q = root;
		}
}

int main()
{
	BST T = NULL;
	int unbalance , *q;
	q = &unbalance;
	int R;
	cout << "please input the number:" << endl;
	cin >> R;
	while (R != 0)
	{
		AVLInsert(T, R, *q);
		cout << "please input the number:" << endl;
		cin >> R;
	}
	cin >> R;
	unbalance = 0;
	AVLDelete(T, R);
	return 0;
}