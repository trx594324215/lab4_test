#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#define N 100
using namespace std;

int cou ;
char visited[N];
typedef struct node        //边表结点
{
	int adjvex;
	int T = 1;            //邻接点域（下标）
	struct node *next;     //下一边链接指针
}EdgeNode;

typedef struct veretexnode             //顶点表结点
{
	char  vertex;          //顶点数据域
	EdgeNode * firstedge;
}VertexNode;              //边链表头指针

typedef struct             //顶点表结点
{
	VertexNode vexlist[N];
	int n;
	int e;                 //顶点个数与边数
} AdjGraph;

void MNvisited()//置空访问数组//
{
	int i;
	for (i = 0; i<N; i++)
	{
		visited[i] = 'F';
	}
}

void DFS1(AdjGraph* G, int i, int dnf[])      //以vi为出发点时对邻接表表示的图G进行先深搜索（递归方法）
{
	EdgeNode *p;
	//cout<<G->vexlist[i].vertex;     //访问顶点vi;
	visited[i] = 'T';                   //标记vi已访问
	dnf[i] = cou;//对vi进行编号
	cou++;
	p = G->vexlist[i].firstedge;       //取vi边表的头指针
	while (p != NULL)                      //依次搜索vi的邻接点vj, 这里j=p->adjvex
	{
		if (visited[p->adjvex] != 'T')   //若vj尚未访问
		{
			p->T = 0;
			DFS1(G, p->adjvex, dnf);
		}          //则以vj为出发点先深搜索
		p = p->next;
	}
}

void DFS2(AdjGraph* G, int i)      //以vi为出发点时对邻接表表示的图G进行先深搜索（递归方法）
{
	//int  dfn[max],cou=0;
	EdgeNode *p;
	//cout<<G->vexlist[i].vertex;     //访问顶点vi;
	visited[i] = 'T';                   //标记vi已访问
	//dnf[i] = cou++;                 //对vi进行编号
	p = G->vexlist[i].firstedge;       //取vi边表的头指针
	while (p != NULL)                      //依次搜索vi的邻接点vj, 这里j=p->adjvex
	{
		if (visited[p->adjvex] != 'T')   //若vj尚未访问
		{
			p->T = 0;
			EdgeNode *q;
			q = G->vexlist[p->adjvex].firstedge;
			while (q->adjvex != i)
			{
				q = q->next;
			}
			q->T = 0;
			DFS2(G, p->adjvex);
		}          //则以vj为出发点先深搜索
		p = p->next;
	}
}

void CreateGraph(AdjGraph &G)//邻接表建立图
{
	int i, tail, head;
	cout << "please input the number of the points and edges:" << endl;
	cin >> G.n >> G.e;                              //1.输入顶点个数和边数
	for (i = 0; i < G.n; i++)                      //2.建立顶点表
	{
		cout << "please input the information of the points:" << endl;
		cin >> G.vexlist[i].vertex;             //2.1输入顶点信息
		G.vexlist[i].firstedge = NULL;          //2.2边表置为空表
	}
	for (i = 0; i < G.e; i++)
	{
		cout << "please input the information of the edge:" << endl;//3.逐条边输入,建立边表
		cin >> tail >> head;                   //3.1输入
		EdgeNode * p = new EdgeNode;            //3.2建立边结点
		p->adjvex = head;			            //3.3设置边结点
		p->next = G.vexlist[tail].firstedge;     //3.4链入第tail 号链表的前端
		G.vexlist[tail].firstedge = p;
		p = new EdgeNode;
		p->adjvex = tail;
		p->next = G.vexlist[head].firstedge;     //3.5链入第head 号链表的前端
		G.vexlist[head].firstedge = p;
	}
}

void outputpic(AdjGraph G)//输出建立好的邻接表//
{
	EdgeNode *p;
	for (int j = 0; j<G.n; j++)
	{
		printf("%c", G.vexlist[j].vertex);
		p = G.vexlist[j].firstedge;
		while (p != NULL)
		{
			printf("->%d", p->adjvex);
			p = p->next;
		}
		printf("->^\n");
	}
}

AdjGraph BuildTree(AdjGraph G)//先深生成树//
{
	EdgeNode *p;
	AdjGraph T;
	T.n = G.n;
	for (int i = 0; i < T.n; i++)                      //2.建立顶点表
	{
		//cout << "please input the information of the points:"<< endl;
		T.vexlist[i].vertex = G.vexlist[i].vertex;             //2.1输入顶点信息
		T.vexlist[i].firstedge = NULL;          //2.2边表置为空表
	}
	for (int j = 0; j<T.n; j++)
	{
		//printf("%c",G.vexlist[j].vertex);
		p = G.vexlist[j].firstedge;
		while (p != NULL)
		{
			if (p->T == 0)
			{
				EdgeNode *o=new EdgeNode;
				//o = p->next;
				//p->next
				o->adjvex = p->adjvex;
				o->T = p->T;
				o->next = T.vexlist[j].firstedge;
				T.vexlist[j].firstedge = o;
				//T.vexlist[j].firstedge->next = o;
				//p->next = o;
				/*EdgeNode *q = new EdgeNode;
				q->adjvex = j;
				q->next = T.vexlist[p->adjvex].firstedge;
				T.vexlist[p->adjvex].firstedge = q;*/
			}
			p = p->next;
		}
	}
	return T;
}

AdjGraph BuildBTree(AdjGraph G)//先深生成树//
{
	EdgeNode *p;
	AdjGraph T;
	T.n = G.n;
	for (int i = 0; i < T.n; i++)                      //2.建立顶点表
	{
		//cout << "please input the information of the points:"<< endl;
		T.vexlist[i].vertex = G.vexlist[i].vertex;             //2.1输入顶点信息
		T.vexlist[i].firstedge = NULL;          //2.2边表置为空表
	}
	for (int j = 0; j<T.n; j++)
	{
		//printf("%c",G.vexlist[j].vertex);
		p = G.vexlist[j].firstedge;
		while (p != NULL)
		{
			if (p->T == 1)
			{
				EdgeNode *o = new EdgeNode;
				//o = p->next;
				//p->next
				o->adjvex = p->adjvex;
				o->T = p->T;
				o->next = T.vexlist[j].firstedge;
				T.vexlist[j].firstedge = o;
				//T.vexlist[j].firstedge->next = o;
				//p->next = o;
				/*EdgeNode *q = new EdgeNode;
				q->adjvex = j;
				q->next = T.vexlist[p->adjvex].firstedge;
				T.vexlist[p->adjvex].firstedge = q;*/
			}
			p = p->next;
		}
	}
	return T;
}

void Iscoila(AdjGraph T, int dnf[],int low[],int coila[])
{
	int coun = 0;
	if (T.vexlist[dnf[0]].firstedge->next != NULL)
	{
		coila[0] = dnf[coun];
		coun++;
	}
	for (int i = 1; i < T.n; i++)
	{
		EdgeNode *p;
		p = T.vexlist[i].firstedge;
		while (p != NULL)
		{
			if (dnf[p->adjvex] > dnf[i])
			{
				if (low[p->adjvex] >= dnf[i])
				{
					coila[coun]=i;
					break;
				}
			}
			p = p->next;
		}
	}
}

void inlow(int low[], AdjGraph T, int dnf[],AdjGraph B)
{
	int i, j;
	for (i = 0; i < T.n; i++)//先给low数组进行赋值和初始化
	{
		low[i] = dnf[i];
	}
	for (i = T.n-1; i > -1; i--)
	{
		EdgeNode *q;
		q = B.vexlist[i].firstedge;
		while (q != NULL)
		{
			if (dnf[q->adjvex]<dnf[i])//q->adjvex是i的祖先节点
			{
				if (low[i] > low[q->adjvex])
				{
					low[i]= low[q->adjvex];
				}
			}
			q = q->next;
		}
	}
	EdgeNode *p;
	for (i = T.n-1; i > -1; i--)//与儿子节点的Low值相比较
	{
		p = T.vexlist[i].firstedge;
		while (p != NULL)
		{
			if (dnf[p->adjvex] > dnf[i])
			{
				if (low[p->adjvex] < low[i])
				{
					low[i] = low[p->adjvex];
				}
			}
			p = p->next;
		}
	}
}

int main()
{
	AdjGraph G, T,Gi,B;
	VertexNode w[N];
	int dnf[N], low[N], coila[N];
	cou = 0;
	MNvisited();
	CreateGraph(G);
	outputpic(G);
	Gi = G;
	DFS1(&G, 0, dnf);
	MNvisited();
	DFS2(&Gi, 0);
	T = BuildTree(G);
	B = BuildBTree(Gi);
	outputpic(T);
	outputpic(B);
	inlow(low, T, dnf, B);
	Iscoila(T, dnf, low, coila);
	return 0;
}
