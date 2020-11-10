#include<iostream>
using namespace std;

void InsertSort(int R[], int n);//直接插入排序
void BubbleSort(int R[], int n);//冒泡排序
void QuickSort(int R[], int low, int high);//快速排序
void heapSort(int R[], int n);//堆排序
void mergeSort(int A[], int low, int high);//二路归并算法

int main ()
{

}

/*
直接插入排序
    每趟将一个待排序的关键字按照其值的大小插入到已经排好的部分有序序列的适当位置上
算法描述
    R[]是有序序列
    一开始插入一个数，当然是有序的；
    第二个数跟有序序列比较，找到一个插入的位置，
    循环#16过程
时间复杂度分析
    最坏情况是逆序的O(n^2)
    最好情况是顺序的,O(n)
    平均O(n^2)
空间复杂度分析
    辅助存储空间不随规模变化O(1)
*/
void InsertSort(int R[],int n)
{
    int i, j;
    int temp;
    for (i = 1; i < n;++i)
    {
        temp = R[i];//待插入关键字
        j = i - 1;
        //从待排关键字之前的关键字开始扫描，如果大于待排关键字就后移一位
        while(j>=0&&temp<R[j])
        {
            R[j + 1] = R[j];
            --j;
        }
        R[j + 1] = temp;//找到插入位置
    }
}

/*
起泡排序
    两个相邻的比较，如果前面的关键词比后面的关键字则交换，称为一趟排序
    第一次需要n-1次比较；第二次从

算法描述

时间复杂度分析
    O(n^2)
空间复杂度分析
    O(1)
*/
void BubbleSort(int R[],int n)
{
    int i, j, flag;
    int temp;
    for (i = n - 1; i >= 1;--i)
    {
        flag = 0;
        for (j = 1; j <= i;++j)
        {
            if(R[j-1]>R[j])
            {
                temp = R[j - 1];
                R[j - 1] = R[j];
                R[j] = temp;
                flag = 1;
            }
            if (flag == 0)//一趟排序证明没有交换，则为有序
                return;
        }
    }
}

/*
快速排序
算法描述

时间复杂度分析
    最好情况下O(nlog_2n),最坏情况下O(n^2)
空间复杂度分析
    O(nlog_2n)，递归进行的，需要栈的辅助
*/
void QuickSort(int R[],int low,int high)
{
    int temp;
    int i = low, j = high;
    if(low<high)
    {
        temp = R[low];
        //完成一趟排序，将数组小于temp的关键字放在左边，大于temp的关键字放在右边
        while(i<j)
        {
            while(j>i&&R[j]>=temp)//从右向左扫描，找到一个小于temp的关键字
            {
                --j;
            }
            if(i<j)
            {
                R[i] = R[j];//放在temp左边
                ++i;
            }
            while(i<j&&R[i]<temp)//从左往右扫描，找到一个大于temp的关键字
            {
                ++i;
            }
            if(i<j)
            {
                R[j] = R[i];//放在temp右边
                --j;
            }
        }
        R[i] = temp;
        QuickSort(R, low, i - 1);//递归的对temp左边的关键字进行排序
        QuickSort(R, i + 1, high);//递归的对temp右边的关键字进行排序
    }
}

/*
简单选择排序
算法描述
    从无序序列找到一个最小的关键字加入有序序列
时间复杂度
    O(n^2)
空间复杂度
    O(1)
*/
void SelectSort(int R[],int n)
{
    int i, j, k;
    int temp;
    for (i = 0; i < n;++i)
    {
        k = i;
        //算法关键，从无序序列挑选一个最小的关键字
        for (j = i + 1; j < n;++j)
        {
            if(R[k]>R[j])
                k = j;
        }
        //完成最小关键字与无序序列第一个关键字的交换
        temp = R[i];
        R[i] = R[k];
        R[k] = temp;
    }
}

/*
堆排序
    堆是一种数据结构，可以看成一个完全二叉树。父亲大孩子小（大顶堆）否则叫小顶堆

算法描述
时间复杂度
    Shift()的时间复杂度是O(log_2n)
    所以堆排序的时间复杂度是O(nlog_2n)
空间复杂度
    O(1)
*/
void Shift(int R[],int low,int high)
{
    int i = low, j = 2 * i+1;//j是i的左孩子结点
    int temp = R[i];
    while(j<=high)
    {
        if(j<high&&R[j]<R[j+1])//右孩子较大，则j指向右孩子
            ++j;
        if(temp<R[j])
        {
            R[i] = R[j];//将R[j]调整到双亲结点
            i = j;      //修改i和j的值
            j = 2 * i+2;
        }
        else
        {
            break;
        }
    }
    R[i] = temp;
}

void heapSort(int R[],int n)
{
    int i;
    int temp;
    for (i = n / 2; i >= 0;--i)//建立初始堆
    {
        Shift(R, i, n);
    }
    for (i = n; i >= 1;--i)
    {
        //换出关键字，将其放入最终位置
        temp = R[1];
        R[1] = R[i];
        R[i] = temp;
        Shift(R, 0, i - 1);
    }
}

/*二路归并排序
时间复杂度
    O(nlog_2n)
空间复杂度
    O(n)
*/
#define maxsize 10
void merge(int L[],int low,int mid,int high)
{
    int i=low,j=mid+1,k=0;
    int temp[maxsize];
    while(i<=mid&&j<=high)
    {
        if(L[i]<L[j])
        {
            temp[k] = L[i];
            ++i;
            ++k;
        }
        else
        {
            temp[k] = L[j];
            ++j;
            ++k;    
        }
    }
    while(i<=mid)
    {
        temp[k] = L[i];
        ++i;
        ++k;
    }
    while(j<=high)
    {
        temp[k] = L[j];
        ++j;
        ++k;
    }
    for (int i = 0; i < k;++i)
    {
        L[low + i] = temp[i];
    }
}
void mergeSort(int A[],int low,int high)
{
    if(low<high)
    {
        int mid = (low + high) / 2;
        mergeSort(A, low, mid);
        mergeSort(A, mid + 1, high);
        merge(A, low, mid, high);
    }
}