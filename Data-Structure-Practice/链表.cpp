//链表
#include<bits/stdc++.h>
using namespace std;

typedef int ElemType;
typedef int Status;
typedef struct LNode
{
    ElemType data;
    struct LNode *next;
}LNode,*LinkList;

Status InitList(LinkList &L);

Status InitList(LinkList &L)
{
    L = (LinkList)malloc(sizeof(LNode));
    if(!L)return 0;
    L->next=NULL;
    return 1;
}

//按位插入
Status ListInsert(LinkList L,int i,ElemType e)
{
    LinkList p=L;
    int j=0;
    while(p&&j<i-1)
    {
        p=p->next;
        j++;
    }
    if(!p||j>i-1)return 0;
    LinkList s=(LinkList)malloc(sizeof(LNode));
    s->data=e;
    s->next=p->next;
    p->next=s;
    return 1;
}

//按位删除
Status ListDelete(LinkList L,int i,ElemType &e)
{
    LinkList p=L;
    int j =0;
    while(p&&j<i-1)
    {
        p=p->next;
        j++;
    }
    if(!p&&j>i-1)
    {
        return 0;
    }
    LinkList s=p->next;
    p->next=s->next;
    e=s->data;
    free(s);
    return 1;
}

//打印
void printList(LinkList L)
{
    LinkList p=L->next;
    while(p)
    {
        printf("%d",p->data);
        if(p->next)
        {
            printf(" ");
        }
        p=p->next;
    }
}

//尾插链表
void Create_tail(LinkList &L,ElemType a[],int n)
{
    LinkList r=L;
    int i;
    for(i=0;i<n;i++)
    {
        LinkList p=(LinkList)malloc(sizeof(LNode));
        p->data=a[i];
        p->next=NULL;
        r->next=p;
        r=p;
    }
}

int main(void)
{
    LinkList L;
    ElemType a[5]={0,1,2,3,4};
    ElemType m;
    InitList(L);
    printList(L);
    printf("\n");


    Create_tail(L,a,5);
    printf("1:");
    printList(L);
    printf("\n");

    ListInsert(L,1,99);
    printf("2:");
    printList(L);
    printf("\n");


    ListInsert(L,7,88);
    printf("3:");
    printList(L);
    printf("\n");


    ListDelete(L,1,m);
    printf("4:");
    printf("%d ",m);
    printList(L);
    printf("\n");

    return 0;

}