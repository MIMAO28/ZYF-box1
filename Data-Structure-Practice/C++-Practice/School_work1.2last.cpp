//School_work1.2
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>
#define MAXSIZE 100

typedef int SElem;
//存储数字的栈
typedef struct
{
    SElem *base;
    SElem *top;
    int stacksize;
}MyStack;

//初始化占
bool InitStack(MyStack &S)
{
    S.base = (SElem *)malloc(MAXSIZE*sizeof(SElem));
    S.top=S.base;
    S.stacksize = MAXSIZE;
    return true;
}//栈顶元素是*（top-1）

//入栈操作
bool Push(MyStack &S,SElem e)
{
    *S.top = e;
    S.top = S.top+1;
    return true;
}

//出栈操作
bool Pop(MyStack &S,SElem &e)
{
    if(S.top==S.base)
    {
        return false;
    }
    S.top=S.top-1;
    e = *S.top;
    return true;
}

//获取栈顶原石
bool GetTop(MyStack S,SElem &e)
{
    if(S.top==S.base)
    {
        return false;
    }
    e = *(S.top-1);
    return true;
}

//判断是不是空栈
bool StackEmpty(MyStack &S)
{
    return(S.top==S.base);
}

//释放分配内存
bool StackFree(MyStack &S)
{
    free(S.base);
    return true;
}

//取栈顶符号
char TopChar(MyStack &S)
{
    SElem e;
    GetTop(S,e);
    return e;
}
//中间状态打印函数
void PrintNum(MyStack &S)
{
    printf("Num=[");
    for (SElem *p = S.base; p < S.top; p++) printf("%d",*p);
    printf("]");
}

void PrintOp(MyStack &S)
{
    printf("Op=[");
    for (SElem *p = S.base; p < S.top; p++) printf("%c",*p);
    printf("]");
}
//================================================================

//判断运算符号
bool Is(char c)
{
    return (c=='+'||c=='-'||c=='*'||c=='/'||c=='('||c==')'||c=='#');
}

/*     θ2→   +    -    *    /    (    )    #
θ1= +        >    >    <    <    <    >    >
     -       >    >    <    <    <    >    >
     *       >    >    >    >    <    >    >
     /       >    >    >    >    <    >    >
     (       <    <    <    <    <    =
     )       >    >    >    >         >    >
     #       <    <    <    <    <         =
*/

//比较运算符号优先级
char Compare(char m,char n)
{
    switch(m)
    {
        case '+':case '-':
        {
            if(n=='+'||n=='-')return '>';
            if(n=='*'||n=='/')return '<';
            if(n=='(')return '<';
            return '>';
        }
        case '*':case '/':
        {
            if(n=='(')return '<';
            return '>';
        }
        case '(':
        {
            if(n==')')return '=';
            if(n=='#')return 'E';
            return '<';
        }
        case ')':
        {
            if(n=='(')return 'E';
            return '>';
        }
        case '#':
        {
            if(n=='#')return '=';
            if(n==')')return 'E';
            return '<';
        }
    }
    return '#';
}   


//计算函数
bool Canculate(int a,char op,int b,int *r)
{
    switch (op)
    {
        case '+':
        {*r =a+b;
        break;}
        case '-':
        {
            *r =a-b;
            break;
        }
        case '*':
        {
            *r =a*b;
            break;
        }
        case '/':
        {
            if(b==0)return false;  //除数为0，算不出来
            *r =a/b;
            break;
        }
        default:
        return false;
    }
    return true;
}

//计算表达式
bool Total(const char *exp,int *result)
{
    MyStack Num;
    MyStack Op;
    InitStack(Op);
    Push(Op,'#');
    InitStack(Num);

    int i=0;
    char ch=exp[i];
    int step=0;

    while(ch!='#'||TopChar(Op)!='#')
    {
        //中间状态打印：表头不换行，由各分支负责收尾换行
        printf("Step%d read '%c'  ", ++step, ch);
        PrintNum(Num);
        printf("  ");
        PrintOp(Op);
        printf("  ");
        if(ch==' '||ch=='\t')
        {
            printf("\n");
            ch=exp[++i];
            continue;
        }
        if(isdigit(ch))
        {
            int n = 0;
            while(isdigit(ch))
            {
                n=n*10+(ch-'0');
                ch=exp[++i];
            }
            Push(Num,n);
            printf("\n");
        }
        else if(Is(ch))
        {
            char re=Compare(TopChar(Op),ch);

            if(re=='<')
            {
                Push(Op,ch);//优先级高压入
                printf("push '%c' to Op\n", ch);  
                ch=exp[++i];
            }else if(re=='=')
            {
                SElem t;
                Pop(Op,t);//删掉#或者（）
                printf("pop '%c'\n", t); 
                ch=exp[++i];
            }else if(re=='>')
            {
                SElem op,a,b;
                int r;
                if(!Pop(Num,b)||!Pop(Num,a)||!Pop(Op,op))
                {
                    printf("Error: operand missing\n"); //运算符缺操作数，比如 1+
                    StackFree(Num);
                    StackFree(Op);
                    return false;
                }
                printf("Compare('%c','%c')='%c'\n", TopChar(Op), ch, re); 
                if(!Canculate(a,op,b,&r))
                {
                    printf("Error: divide by zero\n"); //除零
                    StackFree(Num);
                    StackFree(Op);
                    return false;
                }
                Push(Num,r);
                printf("pop '%c', canculate %d%c%d=%d, push to Num\n",(char)op, (int)a, (char)op, (int)b, r);     
            }else
            {
               printf("Error: illegal expression\n"); //括号不匹配、运算符位置不对
               StackFree(Num);
               StackFree(Op); 
               return false;
            }
        }
        else
        {
            printf("Error: illegal character '%c'\n", ch); //既不是数字也不是运算符
            StackFree(Num);
            StackFree(Op);
            return false;
        }
    }
    //清除空间
    Pop(Num,*result);
    StackFree(Num);
    StackFree(Op);
    return true;
}

//主程序
int main(void)
{
    char line[520];
    while(1)
    {
        printf("Please enter the expression:\n");
        if(fgets(line,sizeof(line),stdin)==NULL)break;

        int len=strlen(line);
        while (len > 0 && (line[len-1] == '\n' || line[len-1] == '\r')) 
        {
            len = len - 1;
        }
        if(len==0)break;
        line[len]='#';
        line[len+1]='\0';

        int result;
        if(Total(line,&result))
        {
            printf("result:%d\n",result);
        }
        else
        {
            printf("calculation failed\n"); //表达式非法或者除零
        }
    }
    return 0;
}