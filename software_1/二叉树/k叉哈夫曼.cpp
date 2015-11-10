#include <iostream>
#define N 128
#include <stdio.h>
#include <string.h>
#define cn 10
using namespace std;

typedef  struct
{ /* �����*/
	char letter;
	int  weight; /* Ȩֵ */
	int    child[cn];  /* ������*/
	int    parent; /* ˫���� */
	int    flag;
}HuffmanT;

typedef struct
{
	char  ch;   //�洢��������ַ�
	char  bits[N + 1];//�ַ�����λ��
	int   coun;
	int   node;
}CodeNode;

void InitHT(HuffmanT T[])//��ʼ����������//
{
	int i, j;
	for (i = 0; i<10 * N - 1; i++)
	{
		for (j = 0; j<cn; j++)
		{
			T[i].child[j] = -1;
		}
		T[i].parent = -1;
		T[i].weight = 0;
	}
}

void SelectMin(HuffmanT T[], int n, int c[], int K)//�ҳ�Ȩֵ��С����
{
	int i = 0, tem, q;
	for (int j = 0; j<K; j++)
	{
		i = 0;
		while (T[i].flag != 0)
		{
			i++;
		}
		tem = T[i].weight;
		for (i = 0; i<n; i++)
		{
			if (T[i].flag == 0) //&& (q == K))
			{
				if ((T[i].weight) <= tem)
				{
					c[j] = i;
					tem = T[i].weight;
				}
			}
		}
		int p = c[j];
		T[p].flag = 1;
	}
}

void  CreartHT(HuffmanT T[], int coun, int K)//����k��huffam��
{
	int i;
	int c[N];
	for (i = 0; i < N; i++)//��ʼ����Сֵ��¼����
	{
		c[i] = -1;
	}
	while ((coun+1)%(K-1) != 1)
	{
		T[coun].weight = 0;
		coun++;
	}
	int p = (K*(coun+1) - 1) / (K - 1);
	for (i = coun+1; i < p; i++)
	{              
		SelectMin(T, i, c, K); 
		for (int j = 0; j<K; j++)
		{
			T[c[j]].parent = i;
			T[i].child[j] = c[j];
			T[i].weight += T[c[j]].weight;
		}
	}
}

void CharSetHuffmanEncoding(HuffmanT T[], CodeNode H[], int coun, int K)//k����������ı���
{  /*����Huffman��T ��Huffman����� H*/
	int c, p, i;           /* c ��p �ֱ�ָʾT �к��Ӻ�˫�׵�λ��*/
	char cd[N+1];    /* ��ʱ��ű���*/
	int start,s;            /* ָʾ������cd �е�λ�� */
	cd[coun] = '\0';/* ��������� */
	//CodeNode h = H;
	for (i = 0; i <coun; i++)
	{ /* ������Ҷ��T[i]�ı��� */
		H[i].ch = T[i].letter;  /* ����Ҷ��T[i]��Ӧ���ַ�*/
		start = coun;                   /* ������ʼλ�õĳ�ֵ*/
		c = i;                         /* ��Ҷ��T[i]��ʼ���� */
		while ((p = T[c].parent) >= 0)
		{ /* ֱ�����ݵ�T[c]������λ�� */
			//cd[--start]=(T[p].lchild==c)? '0':'1'; /* ��T[c]��T[p]�����ӣ������ɴ���0���������ɴ���1*/
			for (int k = 0; i<K ; k++)
			{
				if (T[p].child[k] == c)
				{
					cd[--start] = k + 48;
					break;
				}
			}
			c = p;      /* ��������*/
		}
		for (int a = 0; a < N + 1; a++)
		{
			if ((cd[a] <'10')&&(cd[a]>='0' ))
			{
				s = a;
				break;
			}
		}
		strcpy(H[i].bits, &cd[s]);
		//h=h+1;
		/*int a = start;
		int b = 0;
		while (cd[a] != '\0')
		{
			H[i].bits[b] = cd[a];
			a++;
			b++;
		}
		H[i].bits[b + 1] = '\0';*/
		//strcpy(H[i].bits,&cd[start]);
	}
}  /*���Ʊ���Ϊ���ڱ����H*/

int main()
{
	HuffmanT  T[cn * N - 1], Ti[cn * N - 1];
	CodeNode  H[N];
	for (int a = 0; a < N; a++)
	{
		H[a].coun = 0;
	}
	for (int a = 0; a < cn * N - 1; a++)
	{
		T[a].flag = 0;
		T[a].weight = 0;
		Ti[a].flag = 0;
		Ti[a].weight = 0;
	}
	int i, j, coun = 0, k = 0, p = 2, K = 0;
	char c;
	cout << "please input the k:" << endl;
	cin >> K;
	FILE *fp;
	InitHT(Ti);
	fp = fopen("test1.txt", "r");
	c = fgetc(fp);
	while (c != EOF)
	{
		j = (int)c;
		T[j].weight++;
		c = fgetc(fp);
	}
	fclose(fp);//�������ֵȨֵ
	for (i = 0; i<N; i++)//��ȥû�г��ֵ��ַ�
	{
		if (T[i].weight != 0)
		{
			Ti[coun].letter = i;
			Ti[coun].weight = T[i].weight;
			coun++;
		}
	}//��ȥû�г��ֵ��ַ�
	CreartHT(Ti, coun, K);
	CharSetHuffmanEncoding(Ti, H, coun, K);
	for (i = 0; i<coun; i++)
	{
		printf("%d  ", i);
		printf("%c:", H[i].ch);
		cout << H[i].bits;
		printf("\n");
	}//���
	return 0;
}
//����1���ܽڵ����������2��Select�����Ľ�һ�����飻����3���������Ĺ��̣��������ܲ���0Ȩ�ص㣻����4������������

/*void SelectMin(HuffmanT T[],int n,int*p1,int*p2)//�ҳ�Ȩֵ��С����
{
int i=0,tem;
while(T[i].flag!=0)
{
i++;
}
tem=T[i].weight;
for(i=0;i<n;i++)
{
if(T[i].flag==0)
{
if((T[i].weight)<=tem)
{
*p1=i;
tem=T[i].weight;
}
}
}
T[*p1].flag=1;
i=0;
while(T[i].flag!=0)
{
i++;
}
tem=T[i].weight;
for(i=0;i<n;i++)
{
if(T[i].flag==0)
{
if(((T[i].weight)<=tem)&&(i!=*p1))
{
*p2=i;
tem=T[i].weight;
}
}
}
T[*p2].flag=1;
}*/

