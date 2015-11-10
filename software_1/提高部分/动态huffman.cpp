#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

#define SWAP(a,b) t = a; a = b; b = t;
#define MAX 52
int Pos[30] = {0},N = 1; //Pos��ʾ��ĸ��λ��  N: 0���ռ���  1��NYT

struct Node{
    int value,x;//Ȩֵ����ż�������ĸ
    int dad,lson,rson;//���׼����Ҷ��ӵ����
    Node(){x = -1;lson = rson = 0;}
};

class Huffman{
private:
    Node node[MAX];//node���±��ʾ���
    int Size,NYT;//��С�Լ� NYT�ı��
public:
    Huffman() {
        NYT = MAX-N;
        node[NYT].value = 0;
        node[NYT].dad = MAX;
        Size = MAX-1;
    }
    void Input(int n);
    int Create(int n);
    void Show(int n,string s);
    void Change(int n);
    void Swap(int a,int b);
    int Find(int l,int r,int n);
}Tree;

void Huffman::Show(int n,string s){
    if (!node[n].lson){//�ѵ�Ҷ���Ҳ�Ϊ��
        if (n-NYT) {printf("%c:",node[n].x+'a');cout<<n<<":"<<node[n].value<<":"<<s<<endl;}
        Pos[node[n].x] = n;
        return ;
    }
    Show(node[n].lson,s+'0');
    Show(node[n].rson,s+'1');
}

int Huffman::Create(int x){
    int DAD = NYT,NOW = MAX-(++N);
    node[NOW].value = 1;
    node[NOW].x = x;      //��ǰ��ĸ
    NYT = MAX-(++N);      //NYT�ı������
    node[NYT].dad = node[NOW].dad = DAD;  //��ԭ��NYT���� ����NYT ���ǵ�ǰ�� ���С �ұߴ�
    node[DAD].lson = NYT;
    node[DAD].rson = NOW;
    Pos[x] = NOW;
    return DAD;
}

int Huffman::Find(int l,int r,int n){
    int i;
    for(i=l;i<r;i++)
        if (node[i+1].value>=n+1) break;
    return i;
}

void Huffman::Swap(int a,int b){
    if (a==b) return;
    int t;
    SWAP(node[a].value,node[b].value);
    SWAP(node[a].lson,node[b].lson);
    SWAP(node[a].rson,node[b].rson);
    if (node[a].lson) node[node[a].rson].dad = node[node[a].lson].dad = a;
    if (node[b].lson) node[node[b].rson].dad = node[node[b].lson].dad = b;
    SWAP(node[a].x,node[b].x);
}

void Huffman::Change(int n){//�õ��������
    if (n==MAX) return;
    int N = Find(n,Size,node[n].value);//�ҵ���ȥ����λ��
    if (N == Size) {node[N].value++;return;}
    Swap(n,N);
    node[N].value++;
    Change(node[N].dad);
}

void Huffman::Input(int x){//�õ�������ĸ
    int i,N = Pos[x];
    if (!N) N = Create(x);//����������NYT����һ����
    Change(N);
    Show(Size,"");cout<<endl;
}


int main()
{
    char x;
    while (cin>>x,x!='\n')
        Tree.Input(x-'a');
    return 0;
}
