#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#define N 100
using namespace std;

int cou ;
char visited[N];
typedef struct node        //�߱���
{
	int adjvex;
	int T = 1;            //�ڽӵ����±꣩
	struct node *next;     //��һ������ָ��
}EdgeNode;

typedef struct veretexnode             //�������
{
	char  vertex;          //����������
	EdgeNode * firstedge;
}VertexNode;              //������ͷָ��

typedef struct             //�������
{
	VertexNode vexlist[N];
	int n;
	int e;                 //������������
} AdjGraph;

void MNvisited()//�ÿշ�������//
{
	int i;
	for (i = 0; i<N; i++)
	{
		visited[i] = 'F';
	}
}

void DFS1(AdjGraph* G, int i, int dnf[])      //��viΪ������ʱ���ڽӱ��ʾ��ͼG���������������ݹ鷽����
{
	EdgeNode *p;
	//cout<<G->vexlist[i].vertex;     //���ʶ���vi;
	visited[i] = 'T';                   //���vi�ѷ���
	dnf[i] = cou;//��vi���б��
	cou++;
	p = G->vexlist[i].firstedge;       //ȡvi�߱��ͷָ��
	while (p != NULL)                      //��������vi���ڽӵ�vj, ����j=p->adjvex
	{
		if (visited[p->adjvex] != 'T')   //��vj��δ����
		{
			p->T = 0;
			DFS1(G, p->adjvex, dnf);
		}          //����vjΪ��������������
		p = p->next;
	}
}

void DFS2(AdjGraph* G, int i)      //��viΪ������ʱ���ڽӱ��ʾ��ͼG���������������ݹ鷽����
{
	//int  dfn[max],cou=0;
	EdgeNode *p;
	//cout<<G->vexlist[i].vertex;     //���ʶ���vi;
	visited[i] = 'T';                   //���vi�ѷ���
	//dnf[i] = cou++;                 //��vi���б��
	p = G->vexlist[i].firstedge;       //ȡvi�߱��ͷָ��
	while (p != NULL)                      //��������vi���ڽӵ�vj, ����j=p->adjvex
	{
		if (visited[p->adjvex] != 'T')   //��vj��δ����
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
		}          //����vjΪ��������������
		p = p->next;
	}
}

void CreateGraph(AdjGraph &G)//�ڽӱ���ͼ
{
	int i, tail, head;
	cout << "please input the number of the points and edges:" << endl;
	cin >> G.n >> G.e;                              //1.���붥������ͱ���
	for (i = 0; i < G.n; i++)                      //2.���������
	{
		cout << "please input the information of the points:" << endl;
		cin >> G.vexlist[i].vertex;             //2.1���붥����Ϣ
		G.vexlist[i].firstedge = NULL;          //2.2�߱���Ϊ�ձ�
	}
	for (i = 0; i < G.e; i++)
	{
		cout << "please input the information of the edge:" << endl;//3.����������,�����߱�
		cin >> tail >> head;                   //3.1����
		EdgeNode * p = new EdgeNode;            //3.2�����߽��
		p->adjvex = head;			            //3.3���ñ߽��
		p->next = G.vexlist[tail].firstedge;     //3.4�����tail �������ǰ��
		G.vexlist[tail].firstedge = p;
		p = new EdgeNode;
		p->adjvex = tail;
		p->next = G.vexlist[head].firstedge;     //3.5�����head �������ǰ��
		G.vexlist[head].firstedge = p;
	}
}

void outputpic(AdjGraph G)//��������õ��ڽӱ�//
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

AdjGraph BuildTree(AdjGraph G)//����������//
{
	EdgeNode *p;
	AdjGraph T;
	T.n = G.n;
	for (int i = 0; i < T.n; i++)                      //2.���������
	{
		//cout << "please input the information of the points:"<< endl;
		T.vexlist[i].vertex = G.vexlist[i].vertex;             //2.1���붥����Ϣ
		T.vexlist[i].firstedge = NULL;          //2.2�߱���Ϊ�ձ�
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

AdjGraph BuildBTree(AdjGraph G)//����������//
{
	EdgeNode *p;
	AdjGraph T;
	T.n = G.n;
	for (int i = 0; i < T.n; i++)                      //2.���������
	{
		//cout << "please input the information of the points:"<< endl;
		T.vexlist[i].vertex = G.vexlist[i].vertex;             //2.1���붥����Ϣ
		T.vexlist[i].firstedge = NULL;          //2.2�߱���Ϊ�ձ�
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
	for (i = 0; i < T.n; i++)//�ȸ�low������и�ֵ�ͳ�ʼ��
	{
		low[i] = dnf[i];
	}
	for (i = T.n-1; i > -1; i--)
	{
		EdgeNode *q;
		q = B.vexlist[i].firstedge;
		while (q != NULL)
		{
			if (dnf[q->adjvex]<dnf[i])//q->adjvex��i�����Ƚڵ�
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
	for (i = T.n-1; i > -1; i--)//����ӽڵ��Lowֵ��Ƚ�
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
