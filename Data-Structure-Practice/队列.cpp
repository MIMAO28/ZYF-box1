//Stack
#include<bits/stdc++.h>
using namespace std;
#define MAXSIZE 100
typedef int ElemType;
typedef int Status;
typedef struct
{
    ElemType data[MAXSIZE];
    int top;
}SqStack;

Status InitStack(SqStack &S)
{
    S.top=0;
    return 1;
}

//判空
Status StackEmpty(SqStack S)
{
    if(S.top==0)return 1;
    return 0;
}

//判满
Status StackFull(SqStack S)
{
    if(S.top>=MAXSIZE)return 1;
    return 0;
}

//求长度
int StackLength(SqStack S)
{
    return S.top;
}

//进栈
Status Push(SqStack  &S,ElemType e)
{
    if(StackFull(S))return 0;
    S.data[S.top]=e;
    S.top++;
    return 1;
}

//出栈
Status Pop(SqStack &S,ElemType &e)
{
    if(StackEmpty(S))return 0;
    S.top--;
    e=S.data[S.top];
    return 1;
}

//取栈顶
Status GetTop(SqStack S,ElemType &e)
{
    if(StackEmpty(S))return 0;
    e=S.data[S.top-1];
    return 1;
}

//打印
void printStack(SqStack S)
{
    int i;
    printf("栈底-》 ");
    for(int i=0;i<S.top;i++)
    {
        printf("%d ",S.data[i]);
    }
    printf("<-栈顶");
}

int main(void)
{
    SqStack S;
    ElemType m;
    int i;

    InitStack(S);
    printf("1 空栈? %d   长度 %d\n",StackEmpty(S),StackLength(S));

    for(i=1;i<=5;i++)
    {
        Push(S,i*10);
    }
    printf("2 进栈 10~50: ");
    printStack(S);

    GetTop(S,m);
    printf("3 栈顶(不出栈): %d   长度 %d\n",m,StackLength(S));

    Pop(S,m);
    printf("4 出栈: %d   ",m);
    printStack(S);

    printf("5 全部弹出: ");
    while(!StackEmpty(S))
    {
        Pop(S,m);
        printf("%d ",m);
    }
    printf("\n");

    printf("6 空栈再出栈(应失败): 返回 %d\n",Pop(S,m));
    printf("7 空栈取栈顶(应失败): 返回 %d\n",GetTop(S,m));

    /* 测栈满 */
    InitStack(S);
    for(i=0;i<MAXSIZE;i++)
    {
        Push(S,i);
    }
    printf("8 塞满后长度 %d   再进栈(应失败) 返回 %d\n",
           StackLength(S),Push(S,999));

    return 0;
}