#include<iostream>
using namespace std;

//二叉树定义
typedef struct BTNode
{
    int data;
    struct BTNode *left ,*right;
}BTNode;

//二叉树方法
void preorder(BTNode *p);//先序遍历
void inorder(BTNode *p);//中序遍历
void postorder(BTNode *p);//后序遍历
int getDepth(BTNode *p);//求深度
void search(BTNode *p, BTNode *&q, int key);//查找结点
void trave(BTNode *p, int k);//输出第k个结点的值
void level(BTNode *p);//层次遍历
int maxNode(BTNode *p);//求二叉树的宽度
void preorderNonrecursion(BTNode *p);//先序遍历非递归算法
void inorderNorecursion(BTNode *p);//非递归中序遍历
void postorderNorecursion(BTNode *p);//非递归后续遍历

//线索二叉树定义
typedef struct TBTNode
{
    char data;
    int ltag, rtag;//ltag=0表示的是左子树，ltag=1表示的是直接前趋；rtag=0表示的是右子树，rtag=1表示的是直接后继
    struct TBTNode *left, *right;
}TBTNode;
//线索二叉树方法
void InThread(TBTNode *p, TBTNode *&pre);//中序遍历
void creatInThread(TBTNode *p);//创造中序线索二叉树
TBTNode *First(TBTNode *p);//找到第一个结点
TBTNode *Next(TBTNode *p);//找到后继结点
void Inorder(TBTNode *p);//中序遍历
void preHead(TBTNode *p, TBTNode *&pre);//先序遍历

int main()
{
    BTNode *a,* b, *c, *d;
    a = (BTNode *)malloc(sizeof(BTNode));
    b = (BTNode *)malloc(sizeof(BTNode));
    c = (BTNode *)malloc(sizeof(BTNode));
    d = (BTNode *)malloc(sizeof(BTNode));
    a->left = a->right=NULL;
    b->left = b->right=NULL;
    c->left = c->right=NULL;
    d->left = d->right=NULL;
    a->data = 1;
    b->data = 2;
    c->data = 3;
    d->data = 4;
    a->left = b;
    b->left = c;
    a->right = d;
    //
    preorder(a);
}

//先序遍历
void preorder(BTNode* p)
{
    if(p!=NULL)
    {
        cout << p->data;
        preorder(p->left);
        preorder(p->right);
    }
}

//中序遍历
void inorder(BTNode *p)
{
    if(p!=NULL)
    {
        inorder(p->left);
        cout << p->data;
        inorder(p->right);
    }
}

//后续遍历
void postorder(BTNode *p)
{
    if(p!=NULL)
    {
        postorder(p->left);
        postorder(p->right);
        cout << p->data;
    }
}

/*
求二叉树的深度
*/
int getDepth(BTNode *p)
{
    int LD, RD;
    if(p==NULL)
    {
        return 0;
    }
    else
    {
        LD = getDepth(p->left);
        RD = getDepth(p->right);
        return (LD > RD ? LD : RD) + 1;
    }
}

/*
查找等于key值的结点是否存在
存在就将q指向该节点，否则q为空
这里采用先序遍历
*/
void search(BTNode *p,BTNode *&q,int key)
{
    if(p!=NULL)
    {
        if(p->data==NULL)
        {
            q = p;
        }
        else
        {
            search(p->left,q,key);
            search(p->right,q,key);
            /* if(q==NULL)
             search(p->right,q,key); 这是剪枝操作*/
        }
    }
}

/*
输出第k个结点的值（先序）
*/
void trave(BTNode *p,int k)
{
    int n = 0;
    if(p!=NULL)
    {
        ++n;
        if(n==k)
        {
            cout << p->data;
            return;
        }
        else
        {
            trave(p->left, k);
            trave(p->right, k);
        }
    }
}

/*层次遍历
算法描述：
    利用循环队列进行层次遍历
    将根结点入队；
    当队列不为空时，进行出队得到q；
    q的左右子树不为空，入队
*/
#define maxsize 10
void level(BTNode* p)
{
    int front, rear;
    BTNode *que[maxsize];
    front = rear = 0;//初始化队列
    BTNode *q;
    if(p!=NULL)
    {
        rear = (rear + 1) % maxsize;
        que[rear] = p;//入队
        while(rear!=front)//队列不为空时
        {
            front = (front + 1) % maxsize;
            q = que[front];
            cout << p->data;
            if(q->left!=NULL)
            {
                rear = (rear + 1) % maxsize;
                que[rear] = q->left;
            }
            if(q->right!=NULL)
            {
                rear = (rear + 1) % maxsize;
                que[rear] = q->right;
            }
        }
    }
}

/*
求二叉树的宽度
算法描述
    先层次遍历给每个结点标记层号
    统计每层号的结点数
    返回最大的结点数
*/
//队列元素
typedef struct St
{
    BTNode *p;
    int lno;//层次号
}St;

int maxNode(BTNode *p)
{
    int front, rear,Lno;
    St que[maxsize];
    front = rear = 0;
    BTNode *q;
    Lno = 0;//这是层次号
    if(p!=NULL)
    {
        ++rear;
        ++Lno;
        que[rear].p = p;
        que[rear].lno = Lno;
        while(front!=rear)
        {
            ++front;
            q = que[front].p;
            if(q->left!=NULL)
            {
                ++rear;
                ++Lno;
                que[rear].p = p->left;
                que[rear].lno = Lno;
            }
            if(q->right)
            {
                ++rear;
                ++Lno;
                que[rear].p = p->right;
                que[rear].lno = Lno;
            }
        }
        int max = 0,n;
        for (int i = 1;i<=Lno;++i)//遍历每一层
        {
            n = 0;
            for (int j = 0; j < rear;++j)//计算每层结点数
            {
                if (que[j].lno == i)
                    ++n;
            }               
            if(n>max)
                max = n;
        }
        return max;
    }
    else
    {
        return 0;
    } 
}

/*
非递归实现先序遍历
算法描述
    用一个栈的数据结构
    根节点入栈
    栈不为空时，出栈得到q，q的右子树左子树入栈
*/
void preorderNonrecursion(BTNode *p)
{
    if(p!=NULL)
    {
        BTNode *Stack[maxsize],*q;
        int top = -1;
        ++top;
        Stack[top] = p;
        while(top!=-1)
        {
            q = Stack[top];
            cout << q->data;//输出结点的值也可以换为其他的函数
            --top;
            if(q->right!=NULL)
            {
                top++;
                Stack[top] = q->right;
            }
            if(q->left!=NULL)
            {
                top++;
                Stack[top] = q->left;
            }
        }
    }   
}

/*
非递归实现中序遍历
算法描述
    用一个栈
    根节点入栈，然后左子树入栈；
    出栈得到q，q的右子树入栈；
*/
void inorderNorecursion(BTNode *p)
{
    if(p!=NULL)
    {
        BTNode *Stack[maxsize], *q;
        int top = -1;//初始化栈
        BTNode *q=NULL;
        q = p;
        while(top!=-1||q!=NULL)
        {
            while(q!=NULL)
            {
                top++;
                Stack[top] = q;
                q = q->left;
            }
            if(top!=-1)
            {
                q = Stack[top];
                --top;
                cout << q->data;
                q = q->right;
            }
        }
    }    
}

/*
后序遍历非递归算法
算法描述
    用两个栈

*/
void postorderNorecursion(BTNode *p)
{
    if(p!=NULL)
    {
        //定义两个栈
        BTNode *Stack1[maxsize];
        BTNode *Stack2[maxsize];
        int top1 = -1,top2 = -1;
        BTNode *q = NULL;
        top1++;
        Stack1[top1] = p;
        while(top1!=-1)
        {
            q = Stack1[top1];
            --top1;
            top2++;
            Stack2[top2] = q;
            if(q->left!=NULL)//入栈顺序与先序的相反
            {
                top1++;
                Stack1[top1] = q->left;
            }
            if(q->right!=NULL)
            {
                top1++;
                Stack1[top1] = q->right;
            }
        }
        while(top2!=-1)
        {
            q = Stack2[top2];
            top2--;
            cout << q->data;
        }
    }
}

/*
中序遍历对二叉树线索化的递归算法
ltag=0表示的是左子树，ltag=1表示的是直接前趋；rtag=0表示的是右子树，rtag=1表示的是直接后继
算法描述

*/
void InThread(TBTNode *p,TBTNode *&pre)
{
    if(p!=NULL)
    {
        InThread(p->left, pre);//递归，左子树线索化
        if(p->left==NULL)
        {
            p->ltag = 1;
            p->left = pre;//建立结点的前趋线索
        }
        if(pre!=NULL&&pre->right==NULL)
        {
            pre->right = p;//建立前趋结点的后继线索
            pre->rtag = 1;
        }
        pre = p;
        InThread(p->right, pre);//递归，右子树线索化
    }
}

/*
通过中序遍历建立线索二叉树
*/
void creatInThread(TBTNode *p)
{
    TBTNode *pre = NULL;
    if(p!=NULL)
    {
        InThread(p, pre);
        pre->rtag = 1;//最后一个结点没有右子树也没有后继
        pre->right = NULL;
    }   
}

/*
找到第一个结点
算法描述
    中序遍历中最左下的结点就是第一个结点
*/
TBTNode *First(TBTNode *p)
{
    while(p->ltag==0)
        p = p->left;
    return p;
}

/*
找到后继结点
算法描述
    中序遍历中，后继是自己右子树的第一个结点
    或者是自己的根结点
*/
TBTNode *Next(TBTNode *p)
{
    if(p->rtag==0)//有右子树
        return First(p->right);
    else
    {
        return p->right;//直接返回后继
    }
}

/*
线索二叉树的中序遍历
*/
void Inorder(TBTNode *p)
{
    for (TBTNode *q = First(p);q!=NULL;q = Next(q))
    {
        cout << q->data;
    }
}

/*
线索二叉树先序遍历
算法描述

*/
void preHead(TBTNode *p,TBTNode *&pre)
{
    if(p!=NULL)
    {
        if(p->left==NULL)
        {
            p->ltag = 1;
            p->left = pre;
        }
        if(pre!=NULL&&pre->right==NULL)
        {
            pre->right = p;
            pre->rtag = 1;
        }
        pre = p;
        if(p->ltag==0)//递归有条件，有左子树才能递归
            preHead(p->left, pre);
        if(p->rtag==0)//递归有条件，有右子树才能递归
            preHead(p->right, pre);
    }
}

/*
前序线索二叉树执行前序遍历
算法描述

*/
void preorder(TBTNode *p)
{
    if(p!=NULL)
    {
        TBTNode *q=p;
        while(q!=NULL)
        {
            while(q->ltag==0)
            {
                cout << q->data;
                q = q->left;
            }
            cout << q->data;
            q = q->right;
        }
    }
}