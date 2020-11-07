#include<iostream>
using namespace std;

#define maxsize 10
#define maxterms 10
int A[][maxsize];//普通矩阵的数据结构

//稀疏矩阵数据结构
typedef struct trimat
{
    int i, j;//行和列号
    int data;//数值
}trimat;

//普通矩阵方法
void trsmat(int A[][maxsize], int B[][maxsize], int m, int n);//矩阵转置
void addmat(int C[][maxsize], int A[][maxsize], int B[][maxsize], int m, int n);//矩阵相加
void mutmat(int C[][maxsize], int A[][maxsize], int B[][maxsize], int m, int n);//矩阵相乘

/*也可以直接使用数组表示稀疏矩阵的数据结构
trimat_struct[0][0]表示非零个数
trimat_struct[0][1]表示行数
trimat_struct[0][2]表示列数
K>0时
trimat_struct[k][0]第k个的值
trimat_struct[k][1]第k个的行号值
trimat_struct[k][2]第k个的列号值
*/
int trimat_struct[maxterms + 1][3];//三元组数据结构

//三元组方法
void creatTrimat(float A[][maxsize], int m, int n, float B[][3]);//建立三元组
void printTrimat(float B[][3]);//通过三元组打印矩阵

//伪地址表示法之十字链表
typedef struct OLNode//普通节点结构
{
    int i, j;
    struct OLNode *right = NULL;
    struct OLNode *down = NULL;
    float data;
}OLNode;
//十字链表方法
int CreateCrossListMat(float A[][maxsize], int m, int n, int k, CrossList &M);//创建十字链表

typedef struct CrossList//头节点结构
{
    OLNode *rhead = NULL,*chead=NULL;
    int m, n, k;//行号、列号、个数
}CrossList;

int main()
{

}

/*
矩阵的转置：
*/
void trsmat(int A[][maxsize],int B[][maxsize],int m,int n)
{
    for (int i = 0; i < m;++i)
        for (int j = 0; j < n;++j)
        {
            B[i][j] = A[j] [i];
        }
}


/*
矩阵相加
*/
void addmat(int C[][maxsize],int A[][maxsize],int B[][maxsize],int m,int n)
{
    for (int i = 0; i < m;++i)
        for (int j = 0; j < n; ++j)
        {
            C[i][j] = A[i][j] + B[i][j];
        }
}

/*
矩阵相乘
*/
void mutmat(int C[][maxsize],int A[][maxsize],int B[][maxsize],int m,int n)
{
    for (int i = 0; i < m;++i)
        for (int j = 0; j < n;++j)
        {
            C[i][j] = 0;
            for (int h = 0; h < n;++h)
                C[i][j] += A[i][h] * B[h][j];
        }
}

/*
建立三元组
*/
void creatTrimat(float A[][maxsize],int m,int n,float B[][3])
{
    int k = 1;
    for (int i = 0; i < m;++i)
        for (int j = 0; j < n;++j)
        {
            if(A[i][j]!=0)
            {
                B[k][0] = A[i][j];
                B[k][1] = i;
                B[k][2] = j;
                ++k;
            }
        }
    B[0][0] = k-1;
    B[0][1] = m;
    B[0][2] = n;
}

/*
通过三元组打印矩阵
*/
void printTrimat(float B[][3])
{
    int k = 1;
    for (int i = 0; i < B[0][1];++i)
    {
        for (int j = 0; j < B[0][1];++j)
        {
            if((int)B[k][1]==i&&(int)B[k][2]==j)//这里一定要转换int数据类型
            {
                cout << B[k][0] << ',';
                ++k;
            }
            else
            {
                cout << '0,';
            }
        }
        cout << ';' << endl;
    }      
}

/*
十字链表创建稀疏矩阵
*/
int CreateCrossListMat(float A[][maxsize],int m,int n,int k,CrossList& M)
{
    if(M.rhead)
        free(M.rhead);
    if(M.chead)
        free(M.chead);
    M.m = m;
    M.n = n;
    M.k = k;
    if(!(M.chead=(OLNode*)malloc(sizeof(OLNode)*m)))//列节点
        return 0;
    if(!(M.rhead=(OLNode*)malloc(sizeof(OLNode)*n)))//行节点
        return 0;
    OLNode *temps[maxsize];
    for(int j=0;j<n;)
    {
        temps[j] = &(M.rhead[j]);//行节点
    }
    for (int i = 0; i < m;++i)
    {
        OLNode *r =&(M.chead[i]);//列节点
        for (int j = 0; j < n;++j)
        {
            if(A[i][j]!=0)
            {
                OLNode *p = (OLNode *)malloc(sizeof(OLNode));
                p->data = A[i][j];               
                p->i = i;
                p->j = j;
                r->right = p;
                r = p;
                temps[j]->down = p;
                temps[j] = p;
            }
        }
    }
    return 1;//创建成功
}