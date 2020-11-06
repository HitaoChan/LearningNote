#include<iostream>
#define MaxSize 10
using namespace std;

/*顺序栈定义*/
typedef struct SqStack
{
    int data[MaxSize];
    int top;//栈顶
}SqStack;

/*链栈定义*/
typedef struct LNode
{
    struct LNode *next;
    int data;
}LNode;

//顺序栈方法
void initStack(SqStack &st);//初始化顺序栈
int isEmpty(SqStack st);    //判断栈空
int push(SqStack &st, int x);//入栈
int pop(SqStack &st, int &x);//出栈

//链栈方法
void initStack(LNode *&lst);//初始化链栈
int isEmpty(LNode *lst);//判断链栈空
void push(LNode *&lst, int x);//链栈进栈
int pop(LNode *&lst, int &x);//链栈出栈

int main()
{
    return 0;
}

//初始化顺序栈
void initStack(SqStack &st)
{
    st.top = -1;
}

//判断栈空
int isEmpty(SqStack st)
{
    if(st.top==-1)
        return 1;//栈为空
    else
        return 0;
}

//入栈
int push(SqStack &st,int x)
{
    if(st.top==MaxSize-1)
        return 0;
    else 
    {
        st.top += 1;
        st.data[st.top] = x;
        return 1;//插入成功
    }
}

//出栈
int pop(SqStack &st,int &x)
{
    if(st.top==-1)
        return 0;
    else
    {
        x = st.data[st.top];//取出数值
        st.top -= 1;
        return 1;
    }
}

//初始化链栈
void initStack(LNode* &lst)
{
    lst = (LNode *)malloc(sizeof(LNode));
    lst->next = NULL;
}

//判断链栈空
int isEmpty(LNode *lst)
{
    if(lst->data==NULL)
        return 0;
    else
        return 1;
}

//链栈进栈
void push(LNode*& lst,int x)
{
    LNode *p;
    p = (LNode *)malloc(sizeof(LNode));
    //p->next=NULL;是一个创建结点的好习惯，避免出现指针异常
    p->data = x; 
    p->next = lst->next;
    lst->next = p;
}

//链栈出栈
int pop(LNode*& lst,int &x)
{
    if(lst->next==NULL)
        return 0;
    else
    {
        LNode *p = lst->next;
        x = p->data;
        lst->next = p->next;
        free(p);
        return 1;
    }
}