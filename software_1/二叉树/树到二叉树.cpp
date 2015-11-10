#include <iostream>
#define MaxSize 100
//树到二叉树
using namespace std;

struct  CTNode
{
	int    child;
	CTNode  *next;
	bool left_right=true;
};

struct CTbox
{
	char    data;
	CTNode  *firstchild;
};

struct CTree
{
	CTbox ct[MaxSize];
	int   n, r;
};

typedef struct node
{
	struct node *leftChild=NULL;
	struct node *rightChild=NULL;
	char data;
}BiTreeNode, *BiTree;

int judge[MaxSize];
int j = 0;

void CreateTree(CTree &G)//邻接表建立二叉树
{
	int i, tail, head;
	CTNode* temp;
	CTNode *q[MaxSize];
	for (i = 0; i < G.n; i++)                      //2.建立顶点表
	{
		cout << "please input the information of the points:" << endl;
		cin >> G.ct[i].data;             //2.1输入顶点信息
		G.ct[i].firstchild = NULL;
		q[i] = G.ct[i].firstchild;        //2.2边表置为空表
	}
	for (i = 0; i < G.r; i++)
	{
		//CTNode *q=G.ct[]
		cout << "please input the information of the parent and the child:" << endl;//3.逐条边输入,建立边表
		cin >> tail >> head;
		judge[j] = head;
		j++;
		//CTNode *q=G.ct[tail].firstchild;                 //3.1输入
		CTNode *p = new CTNode;            //3.2建立边结点
		p->child = head;
		p->next = NULL;
		if (q[tail] == NULL)
		{
			G.ct[tail].firstchild = p;
			q[tail] = G.ct[tail].firstchild;
		}
		else
		{
			G.ct[tail].firstchild->next = p;
			G.ct[tail].firstchild = G.ct[tail].firstchild->next;
		}
	}
	for (i = 0; i<G.n; i++)
	{
		G.ct[i].firstchild = q[i];
	}
}

void outputpic(CTree G)//输出建立好的邻接表//
{
	CTNode *p;
	for (int j = 0; j<G.n; j++)
	{
		cout << G.ct[j].data;
		p = G.ct[j].firstchild;
		while (p != NULL)
		{
			cout << "->" << p->child;
			p = p->next;
		}
		cout << "->^" << endl;
	}
}

void tree_to_binarytree(CTree &t)//树转化成为二叉树
{
	int i, k, root[MaxSize], o = 0;
	CTNode *a[MaxSize];
	CTNode* temp;
	for (i = 0; i < MaxSize; i++)
	{
		root[i] = -1;
	}
	for (i = 0; i<t.n; i++)
	{
		a[i] = t.ct[i].firstchild;
	}
	for (i = t.n - 1; i >= 0; i--)
	{
		if (t.ct[i].firstchild == NULL)
		{
			continue;
		}
		else
		{
			t.ct[i].firstchild->left_right = false;
			CTNode *q = t.ct[i].firstchild;
			CTNode *o = t.ct[i].firstchild;
			q = q->next;
			while (q != NULL)
			{
				CTNode *p = new CTNode;
				p->child = q->child;
				p->next = NULL;
				int tail = o->child;//
				if (a[tail] == NULL)
				{
					t.ct[tail].firstchild = p;
					a[tail] = t.ct[tail].firstchild;
				}
				else
				{
					t.ct[tail].firstchild->next = p;
					t.ct[tail].firstchild = t.ct[tail].firstchild->next;
				}
				//p->next = t.ct[tail].firstchild;     //
				//t.ct[tail].firstchild = p;
				o = q;
				q = q->next;
				t.ct[i].firstchild->next = q;
			}
		}
	}
	for (i = 0; i<t.n; i++)
	{
		t.ct[i].firstchild = a[i];
	}
	for (i = 0; i < t.n; i++)//收集所有的根节点
	{
		for (k = 0; k < j; k++)
		{
			if (i == judge[k])
				break;
		}
		if (k == j)
		{
			root[o] = i;
			o++;
		}
	}
	for (i = 0; i < o; i++)
	{
		if (i == 0)
		{
			temp = t.ct[root[i]].firstchild;
		}
		else
		{
			if (temp != NULL)
			{
				temp->next = new CTNode;
				temp->next->child = root[i];
				temp->next->next = NULL;
				temp = t.ct[root[i]].firstchild;
			}
			else
			{
				temp = new CTNode;
				temp->child = root[i];
				temp->next = NULL;
				temp = t.ct[root[i]].firstchild;
			}
		}
	}
}

void  PreOrder(BiTree BT)//递归前序遍历//
{
	if (BT != NULL)
	{
		cout << BT->data;
		PreOrder(BT->leftChild);
		PreOrder(BT->rightChild);
	}
}

void adj_to_tree(BiTree &T, CTree G, int i)//二叉树邻接表转链表
{
	T = new BiTreeNode;
	T->data = G.ct[i].data;
	if (G.ct[i].firstchild != NULL)
	{
		if (G.ct[i].firstchild->left_right == false)//有左子树
		{
			adj_to_tree(T->leftChild, G, G.ct[i].firstchild->child);
			if (G.ct[i].firstchild->next != NULL)
			{
				adj_to_tree(T->rightChild, G, G.ct[i].firstchild->next->child);
			}
		}
		else
		{
			adj_to_tree(T->rightChild, G, G.ct[i].firstchild->child);
		}
	}
}

void binarytree_to_tree(CTree &t)//二叉树转化成森林
{
	int i;
	int temp,tempor;
	for (i = 0; i < t.n; i++)//考虑各个根节点
	{
		if (i == 0)
		{
			if (t.ct[i].firstchild->next != NULL)
			{
				CTNode* p = t.ct[i].firstchild->next;
				int j;
				j = p->child;
				p = t.ct[p->child].firstchild->next;
				t.ct[i].firstchild->next = NULL;
				while (p != NULL)
				{
					t.ct[j].firstchild->next = NULL;
					j = p->child;
					p = t.ct[j].firstchild->next;
				}
			}
		}
		CTNode* q=t.ct[i].firstchild;
		if ((t.ct[i].firstchild == NULL) || (t.ct[i].firstchild->left_right == true))
		{
			continue;
		}
		else
		{
			while (q->next != NULL)
			{
				q = q->next;
			}
			temp = t.ct[i].firstchild->child;
			CTNode* Temp=t.ct[temp].firstchild;
			while (Temp != NULL)
			{
				if (Temp->left_right == true)//只有右子树
				{
					q->next = Temp;//i邻接表后面
					q = q->next;
					t.ct[temp].firstchild = NULL;
					temp = Temp->child;
					Temp = t.ct[temp].firstchild;
				}
				else
				{
					if (Temp->next != NULL)//两子树均存在
					{
						q->next= Temp->next;
						q = q->next;
						tempor = Temp->next->child;
						t.ct[temp].firstchild->next = NULL;
						temp = tempor;
						Temp = t.ct[temp].firstchild;
					}
					else
					{
						Temp = NULL;
					}
				}
			}
		}
	}
}

int main()
{
	CTree t;
	BiTree T;
	int i;
	cout << "please input the point of the tree and the number of the forest:" << endl;
	cin >> t.n>>i;
	t.r = t.n - i;
	CreateTree(t);
	outputpic(t);
	tree_to_binarytree(t);
	outputpic(t);
	binarytree_to_tree(t);
	outputpic(t);
	adj_to_tree(T, t, 0);
	PreOrder(T);
	return 0;
}


/*void CreateTree (CTree &G)//邻接表建立二叉树
{
int i,tail,head;
for ( i = 0; i < G.n; i++)                      //2.建立顶点表
{
cout << "please input the information of the points:"<< endl;
cin >> G.ct[i].data;             //2.1输入顶点信息
G.ct[i].firstchild = NULL;          //2.2边表置为空表
}
for (i = 0; i < G.r; i++)
{
//CTNode *q=G.ct[]
cout <<"please input the information of the child:"<< endl;//3.逐条边输入,建立边表
cin >> tail >> head ;
//CTNode *q=G.ct[tail].firstchild;                 //3.1输入
CTNode *p = new CTNode;            //3.2建立边结点
p->child = head;
p->next = G.ct[tail].firstchild;     //3.4链入第tail 号链表的前端
G.ct[tail].firstchild = p;
}
}*/
