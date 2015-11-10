#include <iostream>
#define N 128
#include <stdio.h>
#include <string.h>
#define cn 10
using namespace std;

typedef  struct
{ /* 结点型*/
	char letter;
	int  weight; /* 权值 */
	int    child[cn];  /* 孩子链*/
	int    parent; /* 双亲链 */
	int    flag;
}HuffmanT;

typedef struct
{
	char  ch;   //存储被编码的字符
	char  bits[N + 1];//字符编码位串
	int   coun;
	int   node;
}CodeNode;

void InitHT(HuffmanT T[])//初始化哈夫曼树//
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

void SelectMin(HuffmanT T[], int n, int c[], int K)//找出权值最小的数
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

void  CreartHT(HuffmanT T[], int coun, int K)//构造k叉huffam树
{
	int i;
	int c[N];
	for (i = 0; i < N; i++)//初始化最小值记录数组
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

void CharSetHuffmanEncoding(HuffmanT T[], CodeNode H[], int coun, int K)//k叉哈夫曼树的编码
{  /*根据Huffman树T 求Huffman编码表 H*/
	int c, p, i;           /* c 和p 分别指示T 中孩子和双亲的位置*/
	char cd[N+1];    /* 临时存放编码*/
	int start,s;            /* 指示编码在cd 中的位置 */
	cd[coun] = '\0';/* 编码结束符 */
	//CodeNode h = H;
	for (i = 0; i <coun; i++)
	{ /* 依次求叶子T[i]的编码 */
		H[i].ch = T[i].letter;  /* 读入叶子T[i]对应的字符*/
		start = coun;                   /* 编码起始位置的初值*/
		c = i;                         /* 从叶子T[i]开始上溯 */
		while ((p = T[c].parent) >= 0)
		{ /* 直到上溯到T[c]是树根位置 */
			//cd[--start]=(T[p].lchild==c)? '0':'1'; /* 若T[c]是T[p]的左孩子，则生成代码0，否则生成代码1*/
			for (int k = 0; i<K ; k++)
			{
				if (T[p].child[k] == c)
				{
					cd[--start] = k + 48;
					break;
				}
			}
			c = p;      /* 继续上溯*/
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
}  /*复制编码为串于编码表H*/

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
	fclose(fp);//给予各数值权值
	for (i = 0; i<N; i++)//消去没有出现的字符
	{
		if (T[i].weight != 0)
		{
			Ti[coun].letter = i;
			Ti[coun].weight = T[i].weight;
			coun++;
		}
	}//消去没有出现的字符
	CreartHT(Ti, coun, K);
	CharSetHuffmanEncoding(Ti, H, coun, K);
	for (i = 0; i<coun; i++)
	{
		printf("%d  ", i);
		printf("%c:", H[i].ch);
		cout << H[i].bits;
		printf("\n");
	}//输出
	return 0;
}
//问题1：总节点个数；问题2：Select函数的进一步检验；问题3：建立树的过程，包括可能补得0权重点；问题4：输出编码情况

/*void SelectMin(HuffmanT T[],int n,int*p1,int*p2)//找出权值最小的数
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

