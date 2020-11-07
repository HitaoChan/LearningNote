#include<iostream>
#define maxSize 10
using namespace std;

/* //定长串结构
typedef struct Str
{
    char str[maxSize+1];//加一个给'\0'
    int length;
}Str;
*/

//可变长串结构
typedef struct Str
{
    char *ch=NULL;
    int length;
}Str;


//串的方法
int strAssign(Str &str, char *ch);//给串赋值
int strCompare(Str s1, Str s2);//串比较
int contact(Str &str, Str s1, Str s2);//串连接
int subString(Str &str, Str s, int pos, int n);//求子串
int clearString(Str &str);//清空串
void printStr(Str s);//打印串
int index(Str str, Str subStr);//简单模式匹配串
void getNext(Str substr, int next[]);//KMP算法的前置工作
int KMP(Str str, Str substr, int next[]);//KMP算法=简单模式匹配升级


int main()
{
    Str str,subStr;
    strAssign(str, (char*)"abasdadcd");
    strAssign(subStr,  (char*)"cd");
    int next[10];
    getNext(subStr, next);
    cout<<KMP(str, subStr,next);

    return 0;
}

//给串赋值
/*
bug:第二次调用strAssign方法时，free(str.ch)会出现cannot access memeory 0x8
debug:这是野指针的问题，数据结构设计的时候应该为他设置NULL指针。
*/
int strAssign(Str& str,char* ch)
{
     if(str.ch != NULL)
        free(str.ch); 
    int len = 0;
    char *c = ch;
    while(*c)//求串ch的长度
    {
        ++len;
        ++c;
    }
    if(len==0)
    {
        str.ch = NULL;
        str.length = 0;
        return 1;
    }
    else
    {
        str.ch = (char *)malloc(sizeof(Str) * (len + 1));//多要一个位置放'\0'
        if(str.ch==NULL)
            return 0;//赋值失败，空间没分配成功
        else
        {
            c = ch;
            for (int i = 0; i <= len;++i,++c)//可以将c串的最后一个'\0'复制到
            {
                str.ch[i]= *c;
            }
            str.length = len;
            return 1;
        }
    }
}

//取串长度
int strLength(Str str)
{
    return str.length;
}

//串比较操作
int strCompare(Str s1,Str s2)
{
    for (int i = 0; i < s1.length && i < s2.length;++i)
    {
        if(s1.ch[i]!=s2.ch[i])
            return s1.ch[i] - s2.ch[i];
    }
    return s1.length - s2.length;
}

//串连接操作
int contact(Str& str,Str s1,Str s2)
{
    if(str.ch)
    {
        free(str.ch);
        str.ch = NULL;
    }
    str.ch = (char *)malloc(sizeof(char) * (s1.length + s2.length + 1));//预留一个给'\0'
    if(str.ch==NULL)
        return 0;//分配失败
    int i = 0;
    while(i<s1.length)
    {
        str.ch[i] = s1.ch[i];
        ++i;
    }
    int j = 0;
    while(j<=s2.length)//要复制'\0'
    {
        str.ch[i + j] = s2.ch[j];
        ++j;
    }
    str.length = s1.length + s2.length;
    return 1;
}

/*求子串操作
从pos开始取n个字符作为字串*/
int subString(Str& str,Str s,int pos,int n)
{
    if(pos<0||pos>str.length||n>str.length-pos||n<0)
        return 0;
    str.ch = (char *)malloc(sizeof(char) * n);
    if(str.ch==NULL)
    {
        return 0;
    }
    int i = pos, j = 0;
    for (; j < n;++i,++j)
    {
        str.ch[j] = s.ch[i];
    }
    str.ch[j] = '\0';
    str.length = n;
    return 1;
}

//清空串
int clearString(Str& str)
{
    if(str.ch)
    {
        free(str.ch);
        str.ch = NULL;
    }
    str.length = 0;
    return 1;
}

//打印串
void printStr(Str s)
{
    cout << "print函数" << endl;
    int i = 0;
    while(s.ch[i])
    {
        cout << s.ch[i];
        ++i;
    }
}

/*
简单模式串匹配
算法描述：
    匹配成功，返回串在主串的位置
    匹配失败，返回一个可区别于主串中所有位置的标记
*/
int index(Str str,Str subStr)
{
    cout << "index函数" << endl;
    int i =0, j = 0, k = i;
    while(i<str.length&&j<subStr.length)
    {
        if(str.ch[i]==subStr.ch[j])
        {
            ++i;
            ++j;
        }
        else
        {
            i = k + 1;
            k += 1;
            j = 0;
        }
    }
    if(i>str.length)
        return -1;
    else
    {
        return k;
    }
}

/*
KMP算法的准备工作*/
void getNext(Str substr,int next[])
{
    int i = 0,j=-1;
    next[0] = -1;
    while(i<substr.length)
    {
        if(j==-1||substr.ch[i]==substr.ch[next[j]])
        {
            ++i;
            ++j;
            next[i] = j;
        }
        else
        {
            j=next[i];
        }
    }
}

/*
KMP算法
*/
int KMP(Str str,Str substr,int next[])
{
    int i =0, j =-1;
    while(i<str.length&&j<substr.length)
    {
        if(j==-1||str.ch[i]==substr.ch[j])
        {
            ++i;
            ++j;
        }
        else
        {
            j = next[j];
        }
    }
    if(j==substr.length)
    {
        return i - substr.length;//找到
    }
    else
        return -1;//未找到
}

//KMP算法改进的前置工作
/* void getNextval(Str substr,int nextval[])
{
    int i = 0,j=-1;
    int next[substr.length];
    nextval[0] = -1;
    while(i<substr.length)
    {
        if(j==-1||substr.ch[i]==substr.ch[next[j]])
        {
            ++i;
            ++j;
            next[i] = j;
        }
        else
        {
            j=next[i];
        }
    }
} */