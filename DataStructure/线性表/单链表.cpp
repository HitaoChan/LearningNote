#include<iostream>
using namespace std;
/*单链表*/
typedef struct LNode
{
    struct LNode* next;
    int data;

} LNode;

//函数声明
void printL(LNode *L);//输出链表
void delsll(LNode *L);//删除递增链表的重复元素
void delSmallest(LNode *L);//删除链表最小节点
void reverse(LNode *L);//将链表逆置
void tailIn(LNode *&L, int a[], int n);//尾插法
void headIn(LNode *&L, int a[], int n);//头插法
void splitOddEven(LNode *A, LNode *&B);//奇偶数的域分开
void rePrint(LNode *L);//逆序输出
int findElem(LNode *L, int k);//找到倒数第k个节点

int main()   
{
    int n = 5;
    int a[5];
    for (int i = 0; i < n;++i)
    {
        a[i] = i + 1;
    }
    LNode *L;
    tailIn(L, a, n);
    //rePrint(L);逆序输出，问题：头节点也会输出
    cout<<findElem(L, 1);
    //输出链表
    
    
}

/*
找到倒数第k个节点
算法描述：用两个指针p和q一个整型变量i，q往后找并且计数为i；
初始状态q为第一个节点，p为头节点，i=1；
i<k时q继续后移；
i>=k时，p也要往后移动了，等到q为空时，p指向的节点就是倒数第k个节点；
p=L时，说明没找到，否则就找到；
*/
int findElem(LNode *L, int k)
{
    LNode *p, *q;
    q = L->next;
    p = L;
    int i = 1;
    while(q!=NULL)
    {
        if(i<k)
            q = q->next;
        else
        {
            q = q->next;
            p = p->next;
        }
        ++i;
    }
    if(p==L)
        return 0;
    else 
    {
        cout << p->data;//找到倒数第k个节点
        return 1;
    }
}

/*
将链表逆序输出
运用到了递归（栈）的性质
bug:infinite  LOOP
debug:while改为if
*/
void rePrint(LNode* L)
{   
    if(L!=NULL)
    {      
        rePrint(L->next);
        cout << L->data;               
    }   
}

/*
输出链表
*/
void printL(LNode* L)
{
    cout << "printL函数" << endl;
    LNode *p = L->next;
    while(p!=NULL)
    {
        cout << p->data << endl;
        p = p->next;
    }
}

/*
一个递增的单链表
删除其中重复的元素，并且释放
*/
void delsll(LNode* L)
{
    LNode *p = L->next,*q;
    while(p!=NULL)
    {
        if(p->data=p->next->data)//找到重复节点
        {
            q = p->next;
            p->next = q->next;
            free(q);
        }
        else
        {
            p = p->next;
        }
    }
}

/*
删除单链表中最小的节点
*/
void delSmallest(LNode* L)
{
    LNode *pre=L,*p = L->next, *minp=p,*minpre;//minp保存最小值节点，minpre保留最小值节点前趋
    int temp;
    while(p!=NULL)//找到最小值节点
    {
        if(p->data<minp->data)
        {
            minp = p;
            minpre = pre;
        }
        p = p->next;
        pre = pre->next;
    }
    //删除最小值节点
    minpre->next = minp->next;
    free(minp);
}

/*
将一个单链表逆置
算法描述：使用一次头插法即可。
*/
void reverse(LNode* L)
{
    LNode *q, *p = L->next;//初始化
    L->next = NULL;
    while(p!=NULL)//将L单链表的节点依次插入到q之后
    {
        q = p->next;//保存q的后继
        p->next = L->next;
        L->next = p;
        p = q;//保存的后继成为p继续      
    }
}

/*
单链表的尾插法
每次插入都是插在链表的末尾，所以链表的顺序和数组的顺序一致
*/
void tailIn(LNode* &L,int a[],int n)
{
    cout << "tailIn函数" << endl;
    LNode *p,*q;//
    L = (LNode *)malloc(sizeof(LNode));//为L分配内存
    L->next = NULL;
    q = L;//q是链表的末尾节点
    for (int i = 0; i < n;++i)
    {
        p = (LNode *)malloc(sizeof(LNode));//为p分配内存
        p->data = a[i];
        //cout <<"data "<< p->data << endl;
        //cout <<"ai "<< a[i] << endl;
        q->next = p;//p节点插入到末尾节点后
        q = q->next;//后移成为末尾节点
    }
    q->next = NULL;//末尾节点没有后继
    //printL(L);
}

/*
单链表的头插法
每次插入都是插入链表的第一个，所以链表的顺序和数组的顺序相反
*/
void headIn(LNode* &L,int a[],int n)
{
    LNode *p;
    L = (LNode *)malloc(sizeof(LNode));
    L->next = NULL;
    for (int i = 0; i < n;++i)
    {
        p = (LNode*)malloc(sizeof(LNode));//为p分配内存
        p->data = a[i];
        p->next = L->next;//p插入为第一个节点
        L->next = p;//p是第一个节点
    }
}

/*
将一个单链表的data域为奇数的和偶数的分开为两个链表，并且抱持原来的相对顺序
抱持相对的顺序，需要使用尾插法构建偶数域的链表
*/
void splitOddEven(LNode* A,LNode* &B)
{
    cout << "Split函数" << endl;
    B = (LNode *)malloc(sizeof(LNode));//申请B节点的空间
    B->next = NULL;
    LNode *p, *q,*r;
    p = A;
    r = B;//r是B的尾节点
    while(p->next!=NULL)//单链表中要将节点转移，需要找到前趋节点，p就是前趋节点
    {
        if(p->next->data%2==0)//p的后继节点需要移到B链表
        {
            q = p->next;//要插入到B的节点q
            p->next = q->next;//将q从A中取走
            q->next = NULL;
            r->next = q;//插入到B的尾节点
            r = q;//r成为B的尾节点
            //cout << q->data << endl;
        }
        else
        {
             p = p->next;
        }              
    }
   
}


