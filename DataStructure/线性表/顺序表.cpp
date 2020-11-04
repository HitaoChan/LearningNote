#include<iostream>
#define maxSize 100
using namespace std;



typedef struct
{
    int length;
    int data[maxSize];
} Sqlist;

void delete_(Sqlist &L, int i, int j);
void move(Sqlist &L);
void reverse(int a[], int i, int j);
void shift(int a[], int k, int n);

int main()
{

    Sqlist L;
    L.data[0] = 2;
    L.data[1] = 1;
    L.data[2] = 3;
    L.data[3] = 4;
    L.length = 4;

    for (int i = 0; i < L.length;i++)
    {
        cout << L.data[i] << endl;
    }


    for (int i = 0; i < L.length;i++)
    {
        cout << L.data[i] << endl;
    }

   /* int a[5], n = 5;
   for (int i = 0; i < n;i++)
   {
       a[i] = i + 1;
   }
   shift(a, 2, n);
   for (int i = 0; i < n;++i)
   {
       cout << a[i];
   } */
}

/*
删除顺序表中i和j下标的元素，包括i和j
*/
void delete_(Sqlist &L,int i,int j)
{
    cout << "delete函数" << endl;
    for (;j<L.length;j++)
    {
        L.data[i] = L.data[j];
        i++;
    }
    L.length = L.length - (j - i + 1);
}

/*
将小于表头元素移到表头前面，大于表头的元素移到表头后面
其实就是一个简单的排序，构造一个表头前面的元素比他小，后面的元素比他大
Sqlist会改变，使用引用类型
*/
void move(Sqlist &L)
{
    cout << "move函数" << endl;
    int temp,i,j;
    temp = L.data[0];//保存表头
    for (i = 0, j = L.length; i != j;i++,j--)
    {
        if(L.data[j]<temp)
            L.data[i] = L.data[j];
        if(L.data[i]>temp)
            L.data[j] = L.data[i];
    }
    L.data[i] = temp;
}

/*
将i和j下标内的元素互换
*/
void reverse(int a[],int i,int j)
{
    int temp;
    for (;i<j;--j,++i)
    {
        temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }
}

/*
将整个数组向左移动k个元素
算法描述：
    使用reverse将0和k-1逆置
    使用reverse将k和n-1逆置
    最后使用reverse将0可n-1逆置
复杂度分析：
    时间复杂度：O(n)
    空间复杂度:O(1)
*/
void shift(int a[],int k,int n)
{
    cout << "shift函数" << endl;
    reverse(a, 0, k - 1);
    reverse(a, k, n - 1);
    reverse(a, 0, n - 1);
}

