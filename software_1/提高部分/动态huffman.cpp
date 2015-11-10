#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

#define SWAP(a,b) t = a; a = b; b = t;
#define MAX 52
int Pos[30] = {0},N = 1; //Pos表示字母的位置  N: 0是终极根  1是NYT

struct Node{
    int value,x;//权值及序号及代表字母
    int dad,lson,rson;//父亲及左右儿子的序号
    Node(){x = -1;lson = rson = 0;}
};

class Huffman{
private:
    Node node[MAX];//node的下标表示序号
    int Size,NYT;//大小以及 NYT的编号
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
    if (!node[n].lson){//已到叶子且不为空
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
    node[NOW].x = x;      //当前字母
    NYT = MAX-(++N);      //NYT改变后的序号
    node[NYT].dad = node[NOW].dad = DAD;  //以原来NYT生成 左是NYT 右是当前点 左边小 右边大
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

void Huffman::Change(int n){//得到的是序号
    if (n==MAX) return;
    int N = Find(n,Size,node[n].value);//找到该去换的位置
    if (N == Size) {node[N].value++;return;}
    Swap(n,N);
    node[N].value++;
    Change(node[N].dad);
}

void Huffman::Input(int x){//得到的是字母
    int i,N = Pos[x];
    if (!N) N = Create(x);//不存在则由NYT创建一个树
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
