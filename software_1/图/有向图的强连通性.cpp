#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#define N 100
using namespace std;

int cou;
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

typedef struct stack
{
	VertexNode v[N];
	int top = N-1;
	int i[N];
} Stack;

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

void DFS1(AdjGraph* G, int i, Stack *s)      //������������ջ
{
	EdgeNode *p;
	cout<<G->vexlist[i].vertex;     //���ʶ���vi;
	visited[i] = 'T';//���vi�ѷ���
	s->v[s->top] = G->vexlist[i];
	s->i[s->top] = i;
	s->top--;
	//dnf[i] = cou;//��vi���б��
	//cou++;
	p = G->vexlist[i].firstedge;       //ȡvi�߱��ͷָ��
	while (p != NULL)                      //��������vi���ڽӵ�vj, ����j=p->adjvex
	{
		if (visited[p->adjvex] != 'T')   //��vj��δ����
		{
			p->T = 0;
			DFS1(G, p->adjvex, s);
		}          //����vjΪ��������������
		p = p->next;
	}
	for (int k = 0; k < G->n; k++)
	{
		if (visited[k] != 'T')
		{
			DFS1(G, k, s);
		}
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

void CreateGraph(AdjGraph &G,AdjGraph &fG)//�ڽӱ���ͼ
{
	int i, tail, head;
	cout << "please input the number of the points and edges:" << endl;
	cin >> G.n >> G.e;//1.���붥������ͱ���
	fG.e = G.e;
	fG.n = G.n;
	for (i = 0; i < G.n; i++)                      //2.���������
	{
		cout << "please input the information of the points:" << endl;
		cin >> G.vexlist[i].vertex;             //2.1���붥����Ϣ
		G.vexlist[i].firstedge = NULL;//2.2�߱���Ϊ�ձ�
		fG.vexlist[i].vertex = G.vexlist[i].vertex;
		fG.vexlist[i].firstedge = NULL;
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
		p->next = fG.vexlist[head].firstedge;     //3.5�����head �������ǰ��
		fG.vexlist[head].firstedge = p;
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

int main()
{
	AdjGraph G, T, fG,Gi, B;
	VertexNode w[N];
	Stack s;
	int dnf[N], low[N], coila[N],j=0;
	MNvisited();
	CreateGraph(G,fG);
	outputpic(G);
	Gi = G;
	DFS1(&G, 0,&s );
	MNvisited();
	for (int k = s.top+1; k < N ; k++)
	{
		dnf[s.i[k]] = j;
		j++;
	}
	return 0;
}
