#include<iostream>
using namespace std;

#define inf 1000
#define maxsize 10

//邻接矩阵数据结构定义
typedef struct VertexType
{
    int no;//编号
    char info;
}VertexType;//顶点类型

typedef struct MGraph
{
    int edge[maxsize][maxsize];//存两点之间的权值
    int n, e;//顶点数、边数
    VertexType vex[maxsize];
}MGraph;

//邻接表数据结构定义
typedef struct ArcNode
{
    int adjvex;//该边指向的结点的位置
    struct ArcNode *nextarc;//指向下一条边的指针
    int info;//该边的相关信息，一般不做要求可不写
}ArcNode;

typedef struct VNode
{
    ArcNode *firstarc;
    char data;//顶点信息
}VNode;

typedef struct AGraph
{
    VNode adjlist[maxsize];
    int n, e;//顶点数和边数
}AGraph;

//邻接表的数据结构的图的方法
void DFS(AGraph *G, int v);//深度优先遍历
void BFS(AGraph *G, int v, int visit[maxsize]);//广度优先遍历

//邻接矩阵的算法
void Prim(MGraph g, int v0, int &sum);//普利姆算法
void Kruskal(MGraph g, int &sum, Road road[]);//布鲁斯卡尔算法
void Dijkstra(MGraph g, int v, int dist[], int path[]);//迪杰斯特拉算法



int main()
{

}

/*
邻接表的图深度优先遍历算法
算法描述
    v是起点编号
    visit[]数组负责标记访问过的顶点
    由adjlist[].firstarc得到p边
    当p的顶点没有被访问过时，递归DFS
*/
int visit[maxsize];//需要初始化为0
void Visit(int v)//访问顶点v的操作
{

}
void DFS(AGraph *G,int v)
{
    ArcNode *p;
    visit[v]=1;
    Visit(v);
    p=G->adjlist[v].firstarc;//图的第一条边
    while(p!=NULL)
    {
        if(visit[p->adjvex]==0)
            DFS(G, p->adjvex);
        p = p->nextarc;
    }
}

/*
广度优先搜索遍历
算法描述
    类似二叉树层次遍历
    需要一个循环队列和一个visit数组

*/
void BFS(AGraph *G,int v, int visit[maxsize])
{
    ArcNode *p;
    int que[maxsize], front=0, rear = 0;
    int j;
    p = G->adjlist[v].firstarc;
    visit[v] = 1;
    Visit(v);
    rear = (rear + 1) % maxsize;
    que[rear] = v;//定点入队
    while(front!=rear)//队列不空时
    {
        front = (front + 1) % maxsize;//出队
        j = que[front];
        p = G->adjlist[j].firstarc;//得到j指向的第一条边p
        while(p!=NULL)
        {
            if(visit[p->adjvex]==0)//p边的顶点没访问过
            {
                Visit(p->adjvex);
                visit[p->adjvex] = 1;
                rear = (rear + 1) % maxsize;
                que[rear] = p->adjvex;//入队
            }
            p = p->nextarc;//下一条边
        }
    }
}

//非连通图的深度优先遍历
void dfs(AGraph *G)
{
    for (int i = 0; i < G->n;++i)
        if(visit[i]==0)
            DFS(G, i);
}

//非连通图的广度优先遍历
void bfs(AGraph *G)
{
    for (int i = 0; i < G->n;++i)
        if(visit[i]==0)
            BFS(G,i, visit);
}

/*
普利姆算法
算法描述
   需要两个数组,vset[] 和lowcost[]
   vset[i]=0代表i没有并到最小生成树；
   lowcost[]存放当前生成树到剩余顶点最短边的权值；
    从v0开始其他所有边当作侯选边，找到最小边，将其顶点加入生成树；
    循环#138这个过程，直到所有顶点加入到生成树(vset标志全为1)
时间复杂度
    O(n^2)
*/  
void Prim(MGraph g,int v0,int &sum)
{
    int lowcost[maxsize], vset[maxsize],v;
    int i, j, k, min;
    v = v0;
    for (i = 0; i < g.n;++i)//初始化两个数组
    {
        lowcost[i] = g.edge[v0][i];
        vset[i] = 0;
    }
    vset[v0] = 1;
    sum = 0;
    for (i = 0; i < g.n - 1;++i)
    {
        min = inf;
        //选出最小边
        for (j = 0; j < g.n;++j)
        {
            if(vset[j]==0&lowcost[j]<min)
            {
                min = lowcost[j];
                k = j;
            }
        }
        vset[k] = 1;//加入生成树
        v = k;
        sum += min;//加入总权值
        //刚加入的顶点v更新侯选边
        for (j = 0; j < g.n;++j)
        {
            if(vset[j]==0&&g.edge[v][j]<lowcost[j])
            {
                lowcost[j] = g.edge[v][j];
            }
        }
    }
}

/*
克鲁斯卡尔算法
算法描述

*/
typedef struct Road
{
    int a, b;//一条边的两个顶点
    int w;//边的权值
}Road;
Road road[maxsize];
int v[maxsize];//并查集
/*在并查集中查找根结点的函数*/
int getRoot(int a)
{
    while(a!=v[a])
        a = v[a];
    return a;
}
/*
克鲁斯卡尔算法
算法描述

时间复杂度
    由排序算法决定（sort()）
*/
void sort(Road road[], int e);//对road数组中的E条边按其权值从小到大排序
void Kruskal(MGraph g,int &sum,Road road[])
{
    int N, E, a, b;
    N = g.n;
    E = g.e;
    sum = 0;
    int i;
    for (i = 0; i < N;++i)
        v[i] = i;//并查集初始化
    sort(road, E);//对边排序
    for (i = 0; i < E;++i)
    {
        a = getRoot(road[i].a);
        b = getRoot(road[i].b);
        if(a!=b)
        {
            v[a] = b;//并入生成树
            sum += road[i].w;//求总权值，这一句不固定
        }
    }
}


//
void printfPath(int path[],int a)
{
    int stack[maxsize];
    int top = -1;
    //叶子节点到根结点的顺序入栈
    while(path[a]!=-1)
    {
        stack[++top] = a;
        a = path[a];
    }
    stack[++top] = a;
    while(top!=-1)
        cout << stack[top--] << " ";
    cout << endl;
}

/*
迪杰斯特拉算法
算法描述
    某一顶点到其余各顶点的最短路径
    使用三个数组dist[]、path[]、set[]
    dist[vi]表示当前已找到的从v0到vid 最短路径长度，有则是权值否则是inf
    path[vi]中保存从v0到vi最短路径上vi的前一个顶点；如果v0到vi有边，则path[vi]=v0否则为-1
    set[]标记数组,set[vi]表示vi没有并到最短路径

时间复杂度
    O(n^2)
*/
void Dijkstra(MGraph g,int v,int dist[],int path[])
{
    int set[maxsize];
    int min, i, j, u;
    //各数组初始化
    for (i = 0; i < g.n;++i)
    {
        set[i] = 0;
        dist[i] = g.edge[v][i];
        if(g.edge[v][i]<inf)
        {
            path[i] = g.edge[v][i];
        }
        else
        {
            path[i] = -1;
        }
    }
    set[v] = 1;
    path[v] = -1;//开始的顶点没有上一个顶点
    //关键操作开始
    for (i = 0; i < g.n - 1;++i)
    {
        min = inf;
        for (j = 0; j < g.n;++j)
        {
            if(set[j]==0&&dist[j]<min)
            {
                u = j;
                min = dist[j];
            }
        }
        set[u] = 1;//u加入最小生成树
        for (j = 0; j < g.n;++j)
        {
            if(set[j]==0&&dist[u]+g.edge[u][j]<dist[j])//以u为中间点找到从剩余顶点找到最短路径
            {
                dist[j] = dist[u] + g.edge[u][j];
                path[j] = u;
            }
        }
    }
    //关键操作结束
    //path存储最短路径，dist存储最短路径长度
}

/*
弗洛伊德算法
    求任一对顶点间的最短路径
    Path用来记录当前两顶点间最短路径上要经过的中间顶点
    A用来记录当前已经求得的任意两个顶点最短路径的长度
时间复杂度
    O(n^3)
*/
void Floyd(MGraph *g,int Path[][maxsize],int A[][maxsize])
{
    int i, j, k;
    //初始化
    for (i = 0; i < g->n;)
    {
        for (j = 0; j < g->n;++j)
        {
            A[i][j] = g->edge[i][j];
            Path[i][j] = -1;
        }
    }
    //主要操作;以k为中间点
    for (k = 0; k < g->n;++k)
    {
        for (i = 0; i < g->n;++i)
        {
            for (j = 0; j < g->n;++j)
            {
                if(A[i][j]>A[i][k]+A[k][j])
                {
                    A[i][j] = A[i][k] + A[k][j];
                    Path[i][j] = k;
                }
            }
        }
    }
}